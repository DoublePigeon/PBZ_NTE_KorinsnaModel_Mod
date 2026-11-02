# 技术指导：Korinsna 主角替换 Mod 的实现路径、要点与踩坑记录

本文记录这个 mod **当前正在使用**的做法、每条做法背后的原因、以及踩过的坑和对应修法。
凡是「为什么不能那样写」的部分，都是实际验证过失败后才改过来的，改动前请先读对应章节。

---

## 1. 总体架构

**不修改 Korinsna 的骨骼，也不往游戏骨架上重新蒙皮。** 模型保留自己的 `Bip001` 骨架（369 骨），
动画在运行时由 IK Retargeter 从原主角的实时姿势重定向过来。

```
CharacterMesh0                       原「魂」的身体网格（Hun_Body_Simple，274 骨）
  │  原版动画照常播放，只是不可见     姿势来源
  │  attach parent
  ▼
meshhead                             原本是空的 Hun_Head_New 部件，现在装着 Korinsna 整只网格
  └─ 网格的 PostProcessAnimBlueprint = ABP_Korinsna_Retarget
        └─ AnimGraph: Retarget Pose From Mesh ──→ Output Pose
              └─ RTG_HunToKorinsna (IK Retargeter)
                    ├─ IKR_Hun       (源 IK Rig，游戏骨名)
                    └─ IKR_Korinsna  (目标 IK Rig，Bip001 骨名)
```

原版外观由**三层资产覆盖**清掉，Korinsna 的网格放在一个游戏必定加载的部件路径上，引擎自己会把
`PostProcessAnimBlueprint` 跑起来，UE4SS 脚本只做少量收尾。

| 层 | 覆盖对象 | 换成什么 | 为什么必须这样 |
| --- | --- | --- | --- |
| ① 骨骼部件网格 | `SkinParts/Hun_*`（19 个：Hat / Hair / Scarf / UpCloth / DownCloth / Cape …） | 极小三角形的空白网格（保留游戏骨架） | 这些是独立组件，空白化后不产生像素，但组件 / 骨架 / socket 都还在 |
| ② **Chaos Cloth** | `SkinParts/Cloth/CA_Hun_*`（7 个） | **空 `UChaosClothAsset`** | 长袍 / 上装 / 长发**不是骨骼网格**，是独立渲染的布料资产，这是「外观怎么都清不掉」的真正原因 |
| ③ 可见载体 | `SkinParts/Hun_Head_New` | Korinsna 网格 + `PostProcessAnimBlueprint` | 网格的 post-process ABP 是**硬引用**，加载网格就会把 ABP、IK Retargeter、两个 IK Rig 一起拉进内存 |
| — 不动 | `Hun_Skin_Skeleton`、`PA_Hun` | 保持原版 | 覆盖骨架会直接崩溃（见 §6.12） |

`Hun_Body_Simple` **不做资产替换**，改为运行时隐藏（原因见 §6.11）。

---

## 2. 让运行时脚本能够「找到并跑起来」的几个前提

### 2.1 网格必须占用一个「游戏本来就会去加载」的包路径

打包后的游戏里 UE4SS 只有 `LoadAsset` 可用，它走资产注册表，而注册表是 cook 时生成的，
**永远不知道 mod 容器里的新包**，所以 `LoadAsset("/Game/Korinsna/SK_Korinsna")` 返回 nil；
`LoadObject` / `StaticLoadObject` 在 Lua 里没有暴露。

可行做法：把网格放在游戏自己会请求的路径上（`build_carrier_mesh.py` 把它导入成
`SkinParts/Hun_Head_New`），游戏加载该部件时顺带把网格、骨架、材质、ABP 全部加载进来。
Lua 侧随后只要 `StaticFindObject("/Game/Korinsna/ABP_Korinsna_Retarget.ABP_Korinsna_Retarget_C")`
就能拿到一个活着的类。

### 2.2 AnimBP 靠 `PostProcessAnimBlueprint` 进内存

`USkeletalMesh::PostProcessAnimBlueprint` 是运行时 UPROPERTY，是网格的硬引用，加载顺序自动成立。
`USkeletalMeshComponent::InitAnim()` 会为它创建 `PostProcessAnimInstance`，**不需要脚本介入**。

反过来：如果给主 anim instance 设成同一个类，引擎会把这个 post 实例清掉
（`NewMeshInstanceClass == AnimClass` 分支），所以脚本刻意**不碰**主 anim class。

### 2.3 真正卡住动画的是 leader pose

主角的所有部件网格都以 `CharacterMesh0` 为 **leader pose** 源。跟随者组件**完全不评估自己的动画**
（`ShouldTickPose()` 为 false），只按骨名拷 leader 的骨骼变换；两套骨架骨名对不上，于是永远停在
绑定姿势——表现为「没有动画」。

`SetLeaderPoseComponent(nil, true, true)` 清掉跟随关系后，post 实例才会被评估。
`GetLeaderPoseComponent()` 在 5.7 里不是 BlueprintCallable，所以脚本每轮无条件调用一次清空
（没有 leader 时是空操作）。

### 2.4 不要自建组件

`UActorComponent::RegisterComponent()` 不是 UFUNCTION（UE4SS 调用会报
`attempt to call a TrivialObject value`）。`StaticConstructObject` 造出来的组件永远未注册：
`InitAnim()` 直接 return，没有 anim instance、没有姿势、渲染是黑的。
`AddComponentByClass` 带 `ScriptNoExport` 且需要 `FTransform` 参数。
→ 直接复用游戏已经摆好、已注册、已经在跑我们 ABP 的 `meshhead`。

---

## 3. 构建管线

```powershell
# 一次性：从零生成骨架/蒙皮 FBX（需要 Blender）
& I:\Blender\blender.exe -b --python blender\scripts\build_target_skeleton.py
& I:\Blender\blender.exe -b --python blender\scripts\make_blank_part.py
& I:\Blender\blender.exe -b --python blender\scripts\rig_korinsna.py

# 资产导入 -> 原生 5.7 cook -> IoStore 打包 -> 安装到 ~mods
& tools\build_all.ps1

# 只重新打包（资产与 cook 结果已存在）
& tools\build_all.ps1 -SkipAssets -SkipCook
```

| 脚本 | 作用 |
| --- | --- |
| [blender/scripts/export_korinsna_apose.py](../blender/scripts/export_korinsna_apose.py) | 导出 APOSE/握拳 FBX；**两步烘焙绑定姿态**（见 §5.2） |
| [ue/scripts/import_korinsna_sk.py](../ue/scripts/import_korinsna_sk.py) | 导入 `SK_Korinsna` + 独立骨架 |
| [ue/scripts/build_mod_assets.py](../ue/scripts/build_mod_assets.py) | 覆盖游戏贴图（必须 VT）+ 8 个材质槽占位 |
| [ue/scripts/import_hun_preview.py](../ue/scripts/import_hun_preview.py) | 游戏骨架预览网格（仅编辑器） |
| [ue/scripts/build_retarget_assets.py](../ue/scripts/build_retarget_assets.py) | `IKR_Hun` / `IKR_Korinsna` / `RTG_HunToKorinsna` / `ABP_Korinsna_Retarget` |
| [ue/scripts/build_carrier_mesh.py](../ue/scripts/build_carrier_mesh.py) | 网格以 `SkinParts/Hun_Head_New` 打包并挂 post-process ABP |
| [ue/scripts/import_blank_parts.py](../ue/scripts/import_blank_parts.py) | 19 个部件网格 → 空白网格 |
| [ue/scripts/blank_cloth_assets.py](../ue/scripts/blank_cloth_assets.py) | 7 个 `CA_Hun_*` → 空 ChaosClothAsset |
| [ue/scripts/check_retarget_chain.py](../ue/scripts/check_retarget_chain.py) | 离线校验 AnimGraph 节点、骨架一致性、`FIKRetargetProcessor` 能否初始化 |
| [ue/ProjectPBZ/Source/ProjectPBZ/KorinsnaEditorLibrary.cpp](../ue/ProjectPBZ/Source/ProjectPBZ/KorinsnaEditorLibrary.cpp) | 建 ABP（`FGraphNodeCreator` 只能在 C++ 里建图节点）、`SyncReferencePose` |
| [tools/build_all.ps1](../tools/build_all.ps1) / [stage_iostore.ps1](../tools/stage_iostore.ps1) / [install_mod.ps1](../tools/install_mod.ps1) | 总装 / 裁剪+staging / 安装 |
| [tools/make_neutral_textures.py](../tools/make_neutral_textures.py) | 生成中性辅助贴图（注意 §6.8 的通道顺序坑） |
| [tools/luacheck.py](../tools/luacheck.py) | Lua 静态语法检查（lupa） |

### 3.1 为什么必须「原生 5.7 cook + UAT staging」

- retoc 0.1.5 无法解析本作 UE 5.7 的 legacy 包（`failed to fill whole buffer`）。
- 用 UE 5.6 或 retoc 生成的 5.7 容器进游戏会在启动阶段崩溃。
- 可行路线：`-run=Cook -CookAll` → 裁剪 cooked 目录 → `RunUAT BuildCookRun -stage -pak -iostore`。
  该流程产出的容器 `mount_point` 是 `../../../ProjectPBZ/`，所以工程名必须叫 `ProjectPBZ`。

---

## 4. 重定向链的配置

- 手写映射，`CHAINS` 表里共 28 条，**当前只启用 9 条**（`build_retarget_assets.py`）：
  Root、Spine、Neck、双锁骨、双臂、双腿。手指 / Head / 8 条裙摆链全部关闭（原因见 §5.4~§5.6）。
- **建完链必须调用 `auto_align_all_bones(TARGET)`**。没有它，每根骨的旋转偏移是拿两套不同的参考姿态
  算出来的 → 手指卷曲、四肢偶发拉伸。
- 建 IK Rig 前必须 `KorinsnaEditorLibrary.sync_reference_pose(TARGET_MESH)`
  （内部是 `USkeleton::UpdateReferencePoseFromMesh`），并在之后**重新 set_skeletal_mesh**，
  因为 IK Rig 会缓存骨骼参考姿态。
- 只启用 `Pelvis Motion` / `FK Chains` / `Root Motion`；`Retarget IK Goals`、`Run IK Rig`、
  `Remap Curves` 必须关闭——没有 goal/solver 时打开它们会崩游戏。
- 手臂/腿用**整条连续链**（`UpperArm→Hand`、`Thigh→Toe`），由 FK op 的 `Interpolated`
  旋转模式把关节旋转分摊给中间的扭转骨（见 §5.6）。

---

## 5. 关键做法（附「为什么」）

### 5.1 贴图必须全部是虚拟纹理（VT

主角主材质（`MA_Character` / `MAI_*`）**每一个**贴图参数都用虚拟纹理采样
（母材质默认值就是 `GreyPlaceholder_VT` / `Placeholder_Normal_VT` / `Placeholder_Mask_VT`）。
把普通贴图绑到 VT 采样器上不会报错，但会退回占位图 → 「脸黑、衣服发灰、布纹很脏」。

所以每张覆盖贴图都要：

```python
tex.set_editor_property("srgb", True)                        # 颜色；法线/遮罩为 False
tex.set_editor_property("compression_settings", ...)         # TC_DEFAULT / TC_NORMALMAP
tex.set_editor_property("virtual_texture_streaming", True)   # 关键
```

中性辅助图必须是 **≥128px**（VT 最小 tile），现在统一 256×256。

### 5.2 绑定姿态必须同时烘进「顶点」和「骨骼」（两步）

`export_korinsna_apose.py` 从 `npc_036_APOSE_clenched.blend` 导出时必须做两步，只做一步就会出现
「手是张开的」「四肢偶发拉伸」：

1. **把姿势烘进网格顶点**：rest 姿势还是原始 A-pose 时 `modifier_apply` 骨架修改器
   （网格带形态键，需先 `shape_key_clear()`；morph target 反正不入包）。
2. **把同一姿势变成骨架 rest pose**：`pose.armature_apply()`。

只做第 2 步时骨骼处于新姿势但顶点还是旧形状 → 网格绑在一套对不上的骨架上，引擎渲染的是
**未摆姿势的轮廓**，任何动画都从错误的绑定开始解算，于是出现难以解释的拉伸。
判断是否做对：导出后 `bounds x` 会从 ±51.6 收到 ±42.8（手臂真的被摆进去了）。

> 细节：`modifier_apply` 前要把 `modifier.name` 先存成 `str()`，否则修改器被移除后引用悬空，
> Python 侧会抛 `UnicodeDecodeError`。

### 5.3 材质：复用游戏材质实例，只换贴图（借壳）

游戏没有提供给自定义材质的着色器，所以**不新建材质**，而是让网格的 8 个槽直接指向游戏自己的
材质实例，再把那些实例引用的贴图包覆盖掉。这样着色模型、阴影、SSS、Masked、双面等标志全部继承。

8 个槽（用每槽纯色渲染确认的语义）：

| 槽 | 部位 | 游戏材质实例 | 喂的贴图 |
| --- | --- | --- | --- |
| 0 | 连衣裙（含裙摆外层、靴饰） | `MI_ZeroHun_Cloth_02_b`（MAI_Cloth） | `T_NPC_036_01_d` |
| 1 | 皮肤（腿、手）+ 腰带花饰 | `MI_ZeroHun_Cloth_04_b`（MAI_Cloth） | `T_NPC_036_02_d` |
| 2 | 前发 / 发饰 | `MI_ZeroHun_Cloth_03_b`（MAI_Equipment） | `T_NPC_036_hair_01_d` |
| 3 | 后长发 | `MI_ZeroHun_Cloth_01_b`（MAI_Equipment_Mask） | `T_NPC_036_hair_02_d` |
| 4 | 脸 | `MI_ZeroHun_Cap_01_b`（MAI_Equipment_Mask） | `T_NPC_036_face_d` |
| 5 | 眉毛 | `MI_ZeroHun_Head_Injured30`（MAI_Skin） | `T_NPC_036_face_d` |
| 6 | 眼睛 | `MI_ZeroHun_Eye_01`（MA_EyeRefractive） | `T_NPC_036_eyes_d` |
| 7 | 高光小件 | `MI_ZeroHun_Cloth_05_b`（MAI_Cloth） | 纯白 |

头发和脸特意避开 `MAI_Cloth`（会叠加布料织纹细节法线）和 `MAI_Skin`（会叠加 SCMT 色图），
这两个只留给面积很小、看不出来的部件。

编辑器里创建的占位 MI **不进包**（staging 时剔除）；一旦进包，游戏里人物会变成灰模/纯色。

### 5.4 手指不参与重定向

手指骨极小，几度参考姿态误差就足以看起来「过长/卷曲」，而 Korinsna 的手指比例与魂不同。
试过 3↔3 一一对应 + `Interpolated` + `auto_align_all_bones` + `sync_reference_pose()`
（参考 2B mod 的完整配方），游戏里仍然变形。

最终方案：**不重定向手指**，绑定姿态取自 `npc_036_APOSE_clenched.blend`（握拳），
于是游戏中手指保持握拳。

> 这是「不参与重定向的骨骼不可能被重定向搞坏」原则的应用，参考 2B mod 对 22 根面部骨也是这么做的。
> 想要手指动画，正确路线是「逐骨 retarget-pose 偏移 + ABP 里的手部 IK」，而不是把链简单加回来。

### 5.5 Head 链不参与重定向

Korinsna 的脸蒙在 `head_Bone001` / `head_Bone002` 上，枢轴与魂的单根 `Head` 不同，
跟着转会把脸拽变形。去掉 Head 链后头只靠 Neck 链跟随——这是有意接受的取舍。

### 5.6 扭转骨必须留在链里

`Bone-*-Twist` / `-Twist1` 共 16 根，每根都有数百的蒙皮权重。曾把手/腿链拆成逐骨 1:1 链，
让扭转骨完全不参与重定向，结果**形变明显变差**：扭转骨承载的皮肤不再跟随关节扭转，
四肢看起来被拉长。

现在用整条链 + FK op 的 `Interpolated` 旋转模式把关节旋转分摊到扭转骨。
IK Retargeter 的旋转模式是**链级**设置，**没有逐骨轴向限制**；要做「只绕骨轴旋转」必须在 ABP 里加
约束节点，暂未实现。

### 5.7 裙摆不参与重定向

8 条裙摆链是按**几何位置**（`tools/skirt_chain_map.py`）手动映射到魂的长袍链的，动作一大就会把
裙子甩进腿里。现在关闭，裙骨停在绑定姿态——形状固定，但不会乱穿模。

### 5.8 武器：重挂武器 **Actor 的 Root**，不要动网格子组件

实测结论（用 `report_weapon_geometry` 在 7 个时间点采样）：

| 武器 | 挂接方式 |
| --- | --- |
| 背后的刀 / 刀鞘（`Hun_Knife` 等主角自身部件） | 挂在 `CharacterMesh0` 的**背部 socket**（`Pt_Knife_Back_Socket` 等） |
| **手持武器 Actor**（`BP_Weapon_*` / `BP_BrutalAxe_C` …） | 武器 **Actor 的 Root 组件**挂在 `CharacterMesh0` 的**手部挂点 socket** 上：`WEAPON_R`、`weapon_l`；收刀时改挂 `Pt_*_Back_Socket` |

要点：

- 这是**一次性挂接**，不是每帧写入。证据：武器到魂手骨的距离恒为 9.5~10.4cm（跨 7 次采样、
  幅度极大的不同动作），而到 Korinsna 手骨的距离在 7.4~52.4cm 之间乱跳——位置完全由父级决定。
- 「武器乱飘」的原因是**重挂了错误的层级**：当时改的是武器 Actor 内部的**网格子组件**，
  Root 还留在魂的 socket 上，两个父级叠加。
- 左右手按 **socket 名**判断，不能按武器网格名：`HookMan_Hook_L` 实际握在右手（挂在 `WEAPON_R`）。

实现（`anchor_held_weapons`，`config.attach_weapons`）：

1. 找到挂在 `CharacterMesh0` 手部 socket（名含 `weapon`/`hand` 且不含 `back`）上的武器 **Actor Root**；
2. `K2_AttachToComponent(carrier, Bip001-R/L-Hand, KeepWorld×3)`；
3. **只做平移**：世界坐标加上 `我们的手 − 魂的手`（`K2_SetWorldLocation`）；
4. 再按 `grip_distance` 把握点距离从游戏的 9.5cm 缩到我们拳头自己的握点距离。

第 3 步只需平移，是实测结论：重定向后我们手骨与魂手骨的**世界旋转差是恒定值**
（左 `-20.2/97.3/-4.5`，右 `8.3/-83.0/5.0`，7 次采样误差 <0.1°）——两套骨架手骨轴约定不同，
而这个差异已经被绑定姿态吸收（拳头在手骨下是正的）。所以视觉上正确 = **保留武器世界旋转、
只按两手位置差平移**；平移后武器相对我们手骨的变换恒定，**不需要每帧修正**。

第 4 步的数据依据：我们手骨长度只有 4.36cm、近节指骨距手骨 6.0~6.5cm，而魂的握点在手骨外
9.5cm——正好落在「第一指节外表面」。`grip_distance = { r = 6.0, l = 6.0 }` 是实机调出来的值。

### 5.9 为什么不用手部 IK

IK 的隐含前提是「我们的手能够到魂的手」。实测两手间距正常姿势 11~12cm，极限姿势达 **40cm**
（`geo[t+20] apart R=39.1`、`t+80 R=48.8`）：Korinsna 手臂比魂短，IK 只能靠拉伸够到，会把手臂扯坏。
正确方向是反过来——让武器来适应我们的手。

### 5.10 腰后短刀（原版自身部件）

`Hun_Knife` + `Hun_Knife_Scabbard` 挂在 `CharacterMesh0` 的 `Pt_Knife_Back_Socket` 上。
换了可见身体后它仍在魂的腰后：Korinsna 体型更窄、裙子是刚体，于是刀穿在裙子里只露出刀尖。

`anchor_back_items`（`config.back_items` / `back_item_push_cm`）：

1. 连同身体一起搬过来：按**骨盆对骨盆**平移，保留游戏给的世界旋转；
2. 再沿**裙子背面方向**外推 `back_item_push_cm`（实机调到 2.0cm）；
3. 挂到 `Bip001-Pelvis`，之后随身体动。

「背面方向」不是猜的：用**后裙摆骨**（`b_skirt_1..5`）相对骨盆的水平偏移作为方向——
这是模型自己保证的「远离正面」方向。刀鞘原本被 `hide_scabbards` 隐藏，现在 `back_items` 里的网格
会被豁免并重新显示（`show_part`），因为只看到裸刀不对。

### 5.11 空白部件必须移出阴影/主通道

19 个空白部件是「亚厘米级退化三角形」，它们自己不可见，但阴影 pass 处理接近零面积的几何是
经典的**黑点闪烁**来源。现在对它们 `SetCastShadow(false)` + `SetRenderInMainPass(false)`
（`quiet_blank_parts`），闪烁彻底消失。

---

## 6. Bug 手册（现象 → 根因 → 修法）

### 6.1 没有动画 / 一直是默认姿势

**leader pose 跟随者不评估自己的动画。** 见 §2.3：每轮调用 `SetLeaderPoseComponent(nil, true, true)`。

### 6.2 脸发黑、衣服发灰发脏

**普通贴图绑到 VT 采样器 → 退回占位图。** 见 §5.1：所有覆盖贴图必须 `virtual_texture_streaming=True`。

### 6.3 四肢偶发拉伸、手是张开的

**绑定姿态只烘了骨骼没烘顶点。** 见 §5.2：`modifier_apply` → `armature_apply` 两步。

### 6.4 手指卷曲 / 过长

手指参与重定向就会这样。见 §5.4：不重定向手指，绑定姿态用握拳。

### 6.5 裙摆穿进腿里

裙链的几何映射在运动中不成立。见 §5.7：关闭裙链。

### 6.6 角色周围黑色斑点闪烁

空白部件的退化三角形进了阴影通道。见 §5.11。

### 6.7 武器不在手里 / 换了武器还会乱飘

见 §5.8：重挂 **Actor Root**（不是网格子组件），只平移，再按 `grip_distance` 收敛握点距离。

历史上失败过两次，务必注意：

- **重挂网格子组件** → Root 仍在魂的 socket 上，两个父级叠加 → 刀乱飘；
- **用武器网格名判左右** → `HookMan_Hook_L` 被挂到左手 → 双刀挤在一只手里。

### 6.8 衣服不受光、一直是暗的（法线通道写反）

`tools/make_neutral_textures.py` 的 `write_tga` 收的是 **B,G,R,A** 顺序（TGA 存储顺序），
但调用时按 RGB 传参：

- `T_Korinsna_N` 传 `(128,128,255)` → 实际写入 **R=255, G=128, B=128**

平坦切线空间法线必须是 **R=128, G=128, B=255**。结果所有采样 `_N` 的材质（布料、头发、脸）法线都朝
**侧向 90°**，N·L≈0 → 整片衣服不受光。对照参考 2B mod 的法线均值 `(124,128,246)` 可验证。

修法：`write_tga` 改为接收 RGB、内部转成 B,G,R 写入，四个中性图重新生成
（`T_Korinsna_ARM` 当时碰巧是对的 `(255,255,0)`，只有 `_N` 有问题）。

> `_ARM` = R:AO 1.0 / G:Roughness 1.0 / B:Metallic 0.0。参考 2B mod 用 G=180（粗糙度 0.7），
> 觉得太哑光就改成 180。

### 6.9 腰后短刀穿在裙子里

见 §5.10。

### 6.10 原版长袍 / 披肩 / 头发清不掉

**它们不是骨骼网格，是 Chaos Cloth 资产。** 必须把 7 个 `CA_Hun_*` 换成空 `UChaosClothAsset`；
只隐藏骨骼网格永远看不到效果。

### 6.11 隐藏外观时的两个反直觉点

- `SetVisibility(false, true)` 会把隐藏**传播给子组件**，而 Korinsna 的承载组件正挂在身体组件下面
  → 「所有模型都消失」。第二个参数**必须是 `false`**。
- 斗笠/围巾/发带/刀这些部件是 `SkeletalMeshComponentBudgeted`，`SetRenderInMainPass(false)`
  **对它们不生效**，而且会被游戏的外观系统改回来 → 每轮扫描都要重新应用一遍。

### 6.12 崩溃类

| 现象 | 根因 | 处理 |
| --- | --- | --- |
| 启动即 0xc0000005 | 覆盖了 `Hun_Skin_Skeleton`（即使骨骼同名同数量） | `stage_iostore.ps1` 的 drop 列表默认剔除 |
| 一次性隐藏整套外观时崩溃 | 大量组件在同一帧被改状态 | 收集列表后**每次扫描只隐藏一个**，并逐个打日志 |
| 打开 IK 相关 op 就崩 | 没有 goal/solver 却启用 `Retarget IK Goals` / `Run IK Rig` | 保持关闭 |
| 反射写 1 字节枚举后崩溃 | UE4SS 用 4 字节 int 写进 1 字节字段，破坏相邻内存 | 只用原生 setter；必须写枚举时用 `Reflection():GetProperty()` + `ImportText` |

### 6.13 UE4SS / Lua 侧的坑

| 现象 | 处理 |
| --- | --- |
| `math.atan2` / `math.degrees` 不存在（Lua 5.4） | 自己实现（`math.atan(y, x)`） |
| `ExecuteWithDelay` 不存在（静默无效） | 改用周期扫描分阶段执行 |
| 回调里抛 Lua 错误会**永久停掉** `LoopInGameThreadWithDelay` | 整个回调包 pcall 并写日志 |
| `FindAllOf("/Script/Engine.SkeletalMeshComponent")` 返回空 | 用**短类名** `"SkeletalMeshComponent"` |
| `K2_GetComponentsByClass` 的 `TArray` 取出来是空包装 | 改用 `FindAllOf` + `GetOwner()` 过滤 |
| `StaticFindObject` 找不到时返回「真值包装」 | 调 `GetFullName()` 验证 |
| `AActor:GetRootComponent()` 不可调用 | 沿挂接链向上走，直到 owner 变化（`actor_root_of`） |
| `CreateDynamicMaterialInstance` 不可调用 | 动态材质路线全部作废，改用「借壳 + 覆盖贴图」 |
| `GetRelativeLocation` / `GetMasterPoseComponent` / `IsRegistered` 不可调用 | 需要时用 `K2_*` 版本或换思路 |
| `pcall` 静默吞错导致无从调试 | 统一用 `try(label, fn)`，把标签和错误写进日志 |

### 6.14 材质相关的失败尝试（不要再走）

- **运行时 DMI 改 `OpacityMask`**：`CreateDynamicMaterialInstance` 在 Lua 里不可调用（日志上千次失败）。
- **自建 MIC（以占位 MI 为父级）**：游戏里变成**纯色无贴图**。借壳对「网格槽」有效，
  对「材质实例的父级」无效。
- **Mesh 的 LOD / 顶点色参与遮罩**：Korinsna 没有对应的顶点色，所以 `MAI_Cloth` 的织纹细节会显得
  像「布纹很脏」，头发和脸因此改用不带织纹的材质族。

---

## 7. 运行期脚本（`ue4ss/KorinsnaRetarget`）

`main.lua` 的结构：`boot()` → `NotifyOnNewObject` 监听新组件 → 每 `rescan_interval`（0.5s）跑一次
`scan()`/`setup()`。所有开关在 `config.lua`（文件优先于脚本内默认值）。

| 开关 | 默认 | 作用 |
| --- | --- | --- |
| `carrier_mesh_name` | `Hun_Head_New` | 承载网格的部件名 |
| `anim_class_path` | `ABP_Korinsna_Retarget_C` | 重定向 AnimBP 的类路径 |
| `hide_source_visibility` | `true` | 隐藏原身体（姿势照常 tick） |
| `force_anim_refresh` | `true` | 强制 `AlwaysTickPoseAndRefreshBones` + 关 URO |
| `hide_scabbards` | `true` | 隐藏会乱飞的刀鞘（`back_items` 除外） |
| `quiet_blank_parts` | `true` | 空白部件移出阴影/主通道 |
| `carrier_cast_shadow` | `false` | 承载网格不投影（避免黑斑） |
| `attach_weapons` | `true` | 把手持武器 Actor 对齐到我们的手骨 |
| `grip_distance` | `{ r=6.0, l=6.0 }` | 握点距手骨的距离（cm），0 = 保持游戏值 |
| `back_items` / `back_item_push_cm` | `Hun_Knife` + 刀鞘 / `2.0` | 腰后短刀锚到骨盆并外推 |
| `rescan_interval` | `0.5` | 扫描周期（秒） |
| `probe_only` | `false` | 只观察、不改动 |
| `report_weapon_geometry` | `false` | 武器/手骨几何普查（排障用） |
| `dump_census` / `hide_only_source` / `create_own_component` | `false` | 排障用实验路径 |

---

## 8. 调试方法

日志：`K:\SteamLibrary\steamapps\common\PBZ\platform\steam\ue4ss\Mods\KorinsnaRetarget\KorinsnaRetarget.log`
（每次启动前删掉旧文件，日志是逐行追加的，崩溃也不会丢最后一行）。

### 8.1 判断「重定向到底在不在跑」

```
motion: source pelvis->hand (23.9, -25.8, -9.4) | ours pelvis->hand (15.9, -20.4, -4.2)
```

左右两个向量都在变 → 在跑；右边恒为 `(0,0,0)` → 组件没有评估（未注册 / 没有 anim instance /
仍然是 leader pose 跟随者）。用「骨盆到手」的**组件空间**差，所以角色走动不影响判断。

### 8.2 判断「武器到底挂在谁身上」

打开 `report_weapon_geometry`，会打印两套手骨的世界坐标与间距、每件武器的完整挂接链
（`Weapon Mesh <- Root/<socket> <- CharacterMesh0`）、武器到两只手的距离。
判据：`toGameR` 恒定、`toOurR` 乱跳 = 武器挂在魂的手上。

### 8.3 判断「组件是谁、有没有被隐藏」

日志里的 `all:` / `tree` 行会列出每个骨骼网格组件的网格名、可见性、owner 和坐标，
可以直接看出残留部件属于谁。组件身份一律用**完整对象名**比对，不要用网格资源名
（构造中的组件经常读回 nil，会把自己的网格误判成原版部件）。

---

## 9. 附录：已废弃的「重新蒙皮到游戏骨架」路线

早期版本把 Korinsna 重新蒙皮到游戏骨架 `Hun_Skin_Skeleton` 上，模型普遍被拉伸，已彻底废弃。
但那条路线上的两个结论对未来仍有参考价值（脚本保留在 `blender/scripts/match_game_skeleton.py`）：

1. **第 0 根骨必须叫 `Root`，且变换与游戏一致。** Blender 一定会把 armature 物体本身导出成一个
   FBX 节点，UE 会把它当作第 0 根骨；而游戏骨架的根骨叫 `root`（小写），于是出现
   「armature 节点 + root」两层，动画里针对 `Root` 的轨道找不到骨骼 → 整个动画不生效。
2. **骨骼名大小写必须完全一致**（`head` → `Head`、`weapon_r` → `WEAPON_R`），
   并把 UV1~UV3 全部填成 UV0 的副本——宿主材质会按不同 UV 通道采样，
   UV 不统一会让脸/头发采到图集的随机位置（也是「脏」的一个来源）。

## 10. 已知不足与后续方向
| 项目 | 现状 | 后续思路 |
| --- | --- | --- |
| 手指动画 | 不做，绑定姿态是握拳 | 逐骨 retarget-pose 偏移 + ABP 手部 IK |
| 头部 | 只用 Neck 链跟随，脸不参与 | 给 `head_Bone001/002` 单独建链 + 逐骨偏移 |
| 裙摆 | 刚体（不参与重定向） | 换成 Chaos Cloth，或用正确的骨骼映射重新做链 |
| 扭转骨轴向限制 | 未实现（IK Retargeter 只有链级模式） | 在 ABP 里加约束节点，只保留绕骨轴的旋转 |
| 衣服质感 | 中性 ARM：全粗糙、非金属 | 想要一点高光时把 `_ARM` 的 G 改成 180（参考 2B mod 的值） |
| 武器握点 | 手骨距离按左手/右手各一个常数 | 按武器类型细分（斧/刀/钩的握点不同） |
| 披风/长发物理 | 已清空（外观隐藏的代价） | 若要恢复，需要在 Korinsna 自己骨架上重建布料资产 |
| 阴影 | 承载网格不投影（避免黑斑） | 修好 retargeted mesh 的深度 pass 后可以打开 |
