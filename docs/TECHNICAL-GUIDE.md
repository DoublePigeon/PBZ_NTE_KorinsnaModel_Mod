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
`GetLeaderPoseComponent()` 在 5.7 里不是 BlueprintCallable，脚本**查不到**当前有没有被重新设上 leader，
所以清空**每个组件只做一次**（每轮都清会不停重置姿势，模型卡在第一帧），
另由 §6.17 的**姿势看门狗**在「游戏的身子动了、我们的没动」时补清一次。

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

# 换了绑定姿态 / 换了 .blend 之后：先重导 FBX，再跑 build_all（不带 -SkipAssets）
& I:\Blender\blender.exe -b --python blender\scripts\export_korinsna_apose.py -- `
    KorinsnaModel\npc_036_APOSE.blend blender\out\Korinsna_APose.fbx 1.0
# 看导出打印的 bounds：A-pose 是 x ±44.8/44.0、z 0.04..173.72（握拳版是 x ±42.8/42.4）
```

| 脚本 | 作用 |
| --- | --- |
| [blender/scripts/export_korinsna_apose.py](../blender/scripts/export_korinsna_apose.py) | 从 `npc_036_APOSE.blend` 导出 FBX；**两步烘焙绑定姿态**（见 §5.2） |
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
| [tools/check_forward_refs.py](../tools/check_forward_refs.py) | 检测「先调用后声明」的 `local function`（见 §6.20） |
| [tools/install_lua.ps1](../tools/install_lua.ps1) | 安装 Lua 半边的 **release / dev** 版本（只差日志与普查开关，见 §7.1） |
| [tools/make_release.ps1](../tools/make_release.ps1) | 把两个半边整理成可直接分发的 `Release\KorinsnaModel\` + `Release\KorinsnaRetarget\`（先跑三项检查，不打包压缩） |
| [tools/smoke_lua.py](../tools/smoke_lua.py) | 不启动游戏就跑一遍脚本：release / dev × 三种世界（空 / 有英雄 / 英雄晚到），断言无报错、release 不写日志 |
| [ue4ss/dev/config.dev.lua](../ue4ss/dev/config.dev.lua) | **仅 dev**：叠加在 `config.lua` 上的开关（`log_level=2` + 各普查打开） |
| [ue/scripts/dump_retarget_settings.py](../ue/scripts/dump_retarget_settings.py) | 只读：导出 retargeter 的 op 开关与每条链的旋转/位移模式（`extract/ue-retarget-settings.txt`） |
| [ue/scripts/dump_chain_bones.py](../ue/scripts/dump_chain_bones.py) | 只读：导出每条链实际包含的骨（`extract/ue-chain-bones.txt`），用来发现链里的扭转骨 |
| [ue/scripts/probe_chains.py](../ue/scripts/probe_chains.py) | 只读：两个 IK Rig 的链、retargeter 的映射、各 op 的链设置（查「链没映射」类崩溃） |
| [ue/scripts/probe_fingers.py](../ue/scripts/probe_fingers.py) | 只读：两套骨架的手指/手掌骨的父子关系（切手指链前必看） |

### 3.1 为什么必须「原生 5.7 cook + UAT staging」

- retoc 0.1.5 无法解析本作 UE 5.7 的 legacy 包（`failed to fill whole buffer`）。
- 用 UE 5.6 或 retoc 生成的 5.7 容器进游戏会在启动阶段崩溃。
- 可行路线：`-run=Cook -CookAll` → 裁剪 cooked 目录 → `RunUAT BuildCookRun -stage -pak -iostore`。
  该流程产出的容器 `mount_point` 是 `../../../ProjectPBZ/`，所以工程名必须叫 `ProjectPBZ`。

---

## 4. 重定向链的配置

**唯一的配置来源是 [ue/retarget_config.json](../ue/retarget_config.json)**：每条链的名字、源/目标起止骨、
是否参与重定向、FK 旋转/位移模式与权重、以及一条 `note` 说明为什么是这样。`build_retarget_assets.py`
只读这个文件，**不再按名字前缀猜**（以前用 `name.startswith("LeftSkirt")` 之类的字符串判断，
加一条链或改个名字就会静默出错）。

- 文件里登记了 58 条链，**当前启用 49 条**：Root、Spine、Neck、双锁骨、双臂 3 段 ×2、双腿 4 段 ×2、
  双手腕、手指 3 段 ×5 指 ×2 手。Head / 8 条裙摆链保持 `retarget: false`（原因见 §5.5、§5.7），
  它们仍写在文件里，作用是把「测出来的骨骼范围 + 为什么不用」记录下来。
- **链映射是显式的**：两条 IK Rig 用同一条链名，`set_source_chain(name, name)` 逐条映射，
  之后打印 `chains mapped explicitly: N of N`，再逐链核对 `get_source_chain` 是否为空。
  不要再用 `auto_map_chains(FUZZY, True)`：链名一变它就会按名字相似度乱配。
- **逐链对齐**：`auto_align_bones(该链的骨, CHAIN_TO_CHAIN, TARGET)` 一条链一次，日志会打印
  `align <链> N bone(s): ...`。不要用 `auto_align_all_bones`（原因见 §6.23）。
- 建 IK Rig 前必须 `KorinsnaEditorLibrary.sync_reference_pose(TARGET_MESH)`
  （内部是 `USkeleton::UpdateReferencePoseFromMesh`），并在之后**重新 set_skeletal_mesh**，
  因为 IK Rig 会缓存骨骼参考姿态。
- 只启用 `Pelvis Motion` / `FK Chains` / `Root Motion`；`Retarget IK Goals`、`Run IK Rig`、
  `Remap Curves` 必须关闭——没有 goal/solver 时打开它们会崩游戏（§6.12）。
- 三条硬规则（都踩过）：
  1. **链不能重叠**：同一根骨属于两条链时，`GetChainNameForBone()` 返回合成名（`A,B`），
     映射查不到 → 编辑器断言崩溃（§6.23）。
  2. **骨盆不能出现在任何链里**：`TranslationMode=None` 会把链首骨钉回参考姿态，骨盆因此不动（§6.24）。
  3. **扭转骨不能跳过**：UE 的链是「起点到终点的整条层级路径」，绕不开，只能切段（§5.6）。


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

`export_korinsna_apose.py` 从 `npc_036_APOSE.blend` 导出时必须做两步，只做一步就会出现
「手是张开的」「四肢偶发拉伸」：

> 早期为了「手指不参与重定向」曾改用 `npc_036_APOSE_clenched.blend`（握拳绑定姿态）；
> 手指改成逐关节重定向（§5.4）后已换回 `npc_036_APOSE.blend`。两步烘焙的做法不变。

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
| 0 | 连衣裙（含裙摆外层、靴饰） | `MI_ZeroHun_Cloth_04_b`（MAI_Cloth，纯底色） | `T_NPC_036_01_d`（`T_ZeroHun_Cloth_04_BC`） |
| 1 | 皮肤（腿、手）+ 腰带花饰 | `MI_ZeroHun_Cloth_02_b`（MAI_Cloth） | `T_NPC_036_02_d`（`T_ZeroHun_Cloth_02_BC`） |
| 2 | 前发 / 发饰 | `MI_ZeroHun_Cloth_03_b`（MAI_Equipment） | `T_NPC_036_hair_01_d` |
| 3 | 后长发 | `MI_ZeroHun_Cloth_01_b`（MAI_Equipment_Mask） | `T_NPC_036_hair_02_d` |
| 4 | 脸 | `MI_ZeroHun_Cap_01_b`（MAI_Equipment_Mask） | `T_NPC_036_face_d` |
| 5 | 眉毛 | `MI_ZeroHun_Head_Injured30`（MAI_Skin） | `T_NPC_036_face_d` |
| 6 | 眼睛 | `MI_ZeroHun_Eye_01`（MA_EyeRefractive） | `T_NPC_036_eyes_d` |
| 7 | 高光小件 | `MI_ZeroHun_Cloth_05_b`（MAI_Cloth） | 纯白（`T_ZeroHun_Cloth_05_BC`） |

头发和脸特意避开 `MAI_Cloth`（会叠加布料织纹细节法线）和 `MAI_Skin`（会叠加 SCMT 色图），
这两个只留给面积很小、看不出来的部件。

槽 0 / 槽 1 的实例是**可交换的**（两者都只有一个 albedo 贴图路径），要保证「一个槽一个独立贴图路径」。
真正决定颜色对不对的不是这两个实例的差别，而是**游戏会不会在运行时把槽 0 换掉**——见 §6.18。

编辑器里创建的占位 MI **不进包**（staging 时剔除）；一旦进包，游戏里人物会变成灰模/纯色。

### 5.4 手指：换了绑定姿态 + 逐关节切段后才成立

手指骨极小，几度参考姿态误差就足以看起来「过长/卷曲」，而 Korinsna 的手指比例与魂不同。
早期试过 3↔3 一一对应 + `Interpolated` + `auto_align_all_bones` + `sync_reference_pose()`
（参考 2B mod 的完整配方），游戏里仍然变形，所以当时**关掉手指、绑定姿态用握拳版**
（`npc_036_APOSE_clenched.blend`）。

四肢的「切段」方案（§5.6）验证成功之后手指也按同一套做，并且**绑定姿态换回 `npc_036_APOSE.blend`**
（手指略微张开，导出后 `bounds x` 从 ±42.8 变成 ±44.4）：

- 每根手指按关节切 3 段、每段一条单骨源链：
  `LeftIndex1` = `index_01_l → Bip001-L-Finger1`、`LeftIndex2` = `index_02_l → Bip001-L-Finger11`、
  `LeftIndex3` = `index_03_l → Bip001-L-Finger12`（拇指/中指/无名指/小指同理，左右共 30 条）。
  Korinsna 每根手指的骨名规律是 `<Finger><k>`、`<Finger><k>1`、`<Finger><k>2`
  （`Finger1 / Finger11 / Finger12`；拇指是 `Finger0 / Finger01 / Finger02`）。
- 源骨架的手掌多一层 `*_metacarpal_*`（`index_metacarpal_l` 等），目标没有对应骨，
  **不进任何链**，保持参考姿态。
- 手腕骨本身仍是独立的一条 `LeftHand` / `RightHand` 单骨链。

结果：手指跟随动画（握拳、张开、拿武器时贴合握把），指节无变形。若以后又想关掉，
把 `ue/retarget_config.json` 里那 30 条的 `retarget` 改回 `false` 重新 cook 即可
（绑定姿态是 A-pose，不会退回握拳）。

### 5.5 Head 链不参与重定向

Korinsna 的脸蒙在 `head_Bone001` / `head_Bone002` 上，枢轴与魂的单根 `Head` 不同，
跟着转会把脸拽变形。去掉 Head 链后头只靠 Neck 链跟随——这是有意接受的取舍。

### 5.6 扭转骨：不能跳过，只能切段

`Bone-*-Twist` / `-Twist1` 共 16 根，每根都有数百的蒙皮权重。它们**就在层级路径上**
（手臂：`UpperArm → Bone-UpperArm-Twist → Bone-UpperArm-Twist1 → Forearm → Bone-ForeArm-Twist →
Bone-ForeArm-Twist1 → Hand`，7 根；腿 8 根），而 UE 的链就是「起点到终点的整条路径」，
**没法把中间的骨排除掉**。

于是 `Interpolated` 模式会按骨的序号比例去插值：目标 `Forearm` 在 3/6 处刚好等于源 `lowerarm`（肘是对的），
但两根 `Twist` 在 1/6、2/6 处会把**肘的弯曲**分摊掉三分之一、三分之二 →
整条手臂被慢慢掰弯成**拱形**（这也是 IK_check 第 3 项真正的原因）。

历史教训：曾把手/腿链拆成逐骨 1:1 链，让扭转骨完全不参与重定向，结果形变明显变差
（扭转骨承载的皮肤不再跟随关节）。**逐骨链是错的，切段是对的。**

现在的做法（见 `ue/retarget_config.json`）：每条肢体切成**首尾相接、互不重叠**的段，
每段结束在「关节前的最后一根扭转骨」上、起始在真正的关节骨上，每段的源链写成**单骨链**：

| 段 | 源链（单骨） | 目标链 |
|---|---|---|
| LeftArmUpper | `upperarm_l..upperarm_l` | `Bip001-L-UpperArm..Bone-L-UpperArm-Twist1` |
| LeftArmLower | `lowerarm_l..lowerarm_l` | `Bip001-L-Forearm..Bone-L-ForeArm-Twist1` |
| LeftHand | `hand_l..hand_l` | `Bip001-L-Hand` |
| LeftThigh / LeftCalf / LeftFoot / LeftToe | 同理 | `..Thigh-Twist1` / `..Calf-Twist1` / `Foot` / `Toe0` |

单骨源链在 `GetTransformAtChainParam()` 里直接返回那一根骨（`Params.Num()==1` 的分支），
于是该段内所有骨（含扭转骨）**刚性复制同一个关节的旋转**：扭转骨仍在重定向里、仍跟随关节，
但不再分摊关节的弯曲 → 拱形消失，皮肤不被拧成糖果纸。

> 必须「相邻不重叠」而不是「按关节各一条链」：两条链共用一根骨会让 `GetChainNameForBone()`
> 返回合成名并断言崩溃，见 §6.23。

**手指用同一套办法**（§5.4）：每根手指 3 节各自成段，源链是单骨链，于是每节指骨刚性复制魂对应那一节。

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

#### 5.8.1 收起（挂在背后）的武器：搬到 Korinsna 的脊柱上

**现象**：掏出武器时位置正确，但**收刀之后武器乱飘**。

**排查**（`report_weapon_chain` 打印每次挂接链变化 + Root 到它自称 socket 的距离）：

```
weapon chain: Hun_DoubleBlade_R  Weapon Mesh <- Root/Pt_DoubleBlade_R_Back_Socket <- CharacterMesh0 ... | root gap to socket 0.0 cm
```

Root **精确**回到了游戏自己的背后 socket（gap 0.0cm）。所以不是绑定错位，而是**那个 socket 长在隐藏的
魂的身体上**：魂肩宽、袍厚，这个点在可琳思娜身上落在身体外面 —— 和当初腰后短刀穿裙子是同一类问题
（§5.10）。

**修法**（`anchor_sheathed_weapon`，`config.sheathed_*`）：非手部挂点的武器不再留在魂的 socket 上，
改为搬到**我们自己的躯干**：

1. `K2_AttachToComponent(carrier, Bip001-Spine, KeepWorld×3)`；
2. 平移 `我们的脊柱 − 魂的 spine_03`，保留游戏给的世界旋转；
3. 再沿裙子**背面方向**外推 `sheathed_push_cm`（2cm，与腰后短刀同一套方向推导）。

**为什么是脊柱而不是骨盆**：先试过 `Bip001-Pelvis`（和腰后短刀一致），实机看起来武器**跟着屁股动**——
髋部在走路时摆幅远大于胸腔，背上的武器跟着晃很怪。重定向链是 `pelvis→spine_05` ↔
`Bip001-Pelvis→Bip001-Spine1`，所以可琳思娜的中间脊柱 `Bip001-Spine` 对应魂的 `spine_03`。

**注意**：`Hun_Knife` / `Hun_Knife_Scabbard`（§5.10 的 `back_items`）**保持骨盆锚定不变**，
它们本来就该在腰臀附近。

#### 5.8.2 姿势看门狗重建之后，武器要「退回 socket 再重挂」

看门狗（§6.17）重建重定向图时，手骨可能还是**参考姿势**；武器那时仍挂在我们手骨上，
它的相对变换就按错误的手骨算了出来 → 恢复后**刀刃朝向是歪的**，切一次武器才正常
（切换会走一次完整锚定）。

修法：

- `rearm_pose()` 置 `state.weapon_reanchor`；
- `anchor_held_weapons` 在**姿势真的动起来之后**（我们的手部向量变化 >0.5cm）才把武器
  `K2_AttachToComponent(source, 原 socket, SnapToTarget×3)` 退回游戏 socket，
  下一轮由正常流程在正确姿势下重算偏移；
- 同时加安全线 `anchor_max_gap_cm`（100cm）：双手间距超过一米**不可能是真实姿势**，
  这时本轮不锚定（否则会把坏偏移烘进武器；实测那样会出现 `hand gap 182.7 cm` 的锚定）。

日志里能看到 `weapon: X returned to '<socket>' for a fresh anchor` 与随后的
`weapon: X on <socket> -> Bip001-R-Hand | hand gap …`。

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

**只处理主角自己的组件**：这个函数一度遍历整个关卡的骨骼网格，把 NPC 和铃铛一起踢出 base pass
（§6.15）。判据是 owner 是否为当前主角 Actor（`belongs_to_actor`）。

### 5.12 骨盆只由 Pelvis Motion op 驱动，不能放进任何链

UE 的默认模板里，骨盆**不属于任何链**：`GetChainNameForBone()` 对骨盆有特例，直接返回
`"Retarget Pelvis"`。当时我们把 `Spine` 链写成 `pelvis..spine_05`，于是骨盆成了链的首骨，
而 FK 链 op 的 `TranslationMode=None` 走这一支：

```cpp
case EFKChainTranslationMode::None:
    OutPosition = ParentGlobalTransform.TransformPosition(InitialLocalOffset);  // 链首父级为空
```

即**每次求值都把骨盆摆回重定向姿态（参考姿态）的位置**，把 Pelvis Motion op 刚算出来的位移抹掉。
现象：站立看不出来（参考姿态就是站着），蹲下/坐下/躺下时游戏本体骨盆下降 50-60cm，我们的骨盆一动不动
→ 整个人**浮在空中**（实测见 §8.9：`ours pelvis` 整场都是 -1189.4，`src` 从 -1180 掉到 -1240）。

修法：`Spine` 链从 `spine_01`（目标 `Bip001-Spine`）开始，骨盆交给 Pelvis Motion op。
`ue/retarget_config.json` 里 `Spine` 的 `note` 记录了这一点。

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
| **传送 / 换图时偶发崩溃** | 换图时主角 Actor 被销毁重建，脚本仍持有旧 Actor 的组件（尤其 `state.body`），`setup()` 因此跳过初始化分支，直接对**已销毁的组件**调 `SetLeaderPoseComponent` 等 → 访问违规 | 用 `state.actor_name` 字符串做身份，Actor 变化时 `reset_actor_state()` 丢弃全部旧引用；`valid()` 改成「读不到有效性就当无效」；非玩家 Pawn 的主角副本忽略。见 §6.16 |
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

- **运行时 DMI 改参数**：`CreateDynamicMaterialInstance` 的 3 参数版在 Lua 里调不动；
  单参数的 `CreateAndSetMaterialInstanceDynamic(index)` 能「成功」，但生成的是**别的材质**的实例
  （日志里连衣裙槽拿到 `MID_MI_ZeroHun_Head_Injured30_xxx`），`Get/SetScalarParameterValue`
  也读不回来。想改参数只能在资产层换实例，或者用 §6.18 的 `SetMaterial` 换**整个实例**。
- **自建 MIC（以占位 MI 为父级）**：游戏里变成**纯色无贴图**。借壳对「网格槽」有效，
  对「材质实例的父级」无效。
- **Mesh 的 LOD / 顶点色参与遮罩**：Korinsna 没有对应的顶点色，所以 `MAI_Cloth` 的织纹细节会显得
  像「布纹很脏」，头发和脸因此改用不带织纹的材质族。

### 6.15 其他角色变黑 / 缺肢体，铃铛（存档点）模型与材质消失

**根因：`quiet_blank_parts` 与 `hide_scabbards` 在扫全关卡。**

这两个函数原本用 `FindAllOf("SkeletalMeshComponent")` 遍历**世界里所有**骨骼网格组件：

- `quiet_blank_parts` 对「不是承载网格、不是原身体、不是武器」的每个组件都调
  `SetRenderInMainPass(false)` + `SetCastShadow(false)`。NPC、场景铃铛
  （`StoneCrane_Bell_Skin`、`WoodenFrameBellWithCloth` 等存档点）**也是骨骼网格**，
  于是整关卡的非主角骨骼网格全部退出 base pass：轻则黑剪影 / 缺肢体，重则整个模型不见。
- `hide_scabbards` 同理：按 mesh 名里有没有 `scab` 直接隐藏，NPC 的刀鞘一起陪葬。

**修法：** 两处都只处理**主角自己的组件**——
`belongs_to_actor(组件, state.actor_name)`（owner 就是主角 Actor）或 `attached_to_hero(组件)`
（挂接链最终落到主角的身体 / 承载组件上）。组件列表**每个主角只收集一次**
（`state.quiet_parts`，每 20 次扫描刷新一次），之后每轮只对缓存里的组件重设标志
（游戏的衣柜系统会改回来）。

### 6.16 传送 / 换图时崩溃

**根因：换图时主角 Actor 被销毁重建，脚本里的组件引用全部失效。**

日志证据：两次崩溃（`crash_2026_11_02_23_24_29` / `23_44_49`）都发生在
「新地图里的 `BP_Renewal_Hun_C` 刚被创建」的那一秒，且都停在
`source: VisibilityBasedAnimTickOption = 0` 之后、`hide: carrier=` 之前——也就是进了 `setup()`
却**没进首次初始化分支**（因为 `state.body` 还指着上一个 Actor 的 meshhead），随后
`drive_carrier(target)` 对**正在被销毁的组件**调引擎函数 → 0xc0000005。

**修法：**

1. 用 `state.actor_name`（字符串）当身份。`consider()` 发现新组件属于**另一个** Actor 时先
   `reset_actor_state()`：source / carrier / body / 对齐状态 / 缓存 / 材质守卫…全部丢弃；
2. `setup()` 开头加「陈旧状态闸门」：Actor 不 valid，或 source/carrier 的 owner 不再是
   `state.actor_name` → 只重置、不碰组件；
3. `valid()` 改成严格版：**读不到 `IsValid()` 就当作无效**（原来「读不到就当有效」正是崩溃的直接原因）；
4. 过场 / 预览会额外生成「主角副本」，用 `PlayerController:K2_GetPawn()` 认出真正的玩家 Pawn，
   副本一律忽略（否则会把状态切到副本上）。

### 6.17 交互动画之后模型变默认姿势（现在 0.5 秒内恢复）

**根因：游戏重新给部件组件设了 leader pose。** 交互 / 过场会让游戏重建主角部件，
`meshhead` 重新以 `CharacterMesh0` 为 leader pose 源；跟随者组件**不评估自己的动画**，
post-process 重定向图也就不跑，网格回落到**参考姿势**（看着就是「默认姿势」）。
手动清一次就好，但「每轮都清」会让姿势卡在第一帧——所以必须**只在它真的被设上时清**。

**修法：直接读那个指针。** `LeaderPoseComponent` 是 `USkinnedMeshComponent` 上的
`UPROPERTY(BlueprintReadOnly)`，UE4SS 会把 `TWeakObjectPtr` 解析成对象，所以每轮只要一次属性读：

```lua
local leader = component.LeaderPoseComponent   -- nil = 自己在跑动画
if leader ~= nil then
    component:SetLeaderPoseComponent(nil, true, true)   -- 只在被设上时清，不会卡帧
end
```

这就是「必须撤销的那件事」本身，因此：

- **0.5 秒内恢复**（旧实现靠骨位移统计，要 12 轮 ≈ 2 秒才敢确认）；
- **没有阈值、没有滑动窗口、没有误判**——不需要区分「角色转身」和「姿势冻结」；
- 每轮只有一次属性读，比旧实现每轮 4 次 `GetSocketLocation` + 向量数学更便宜。

`watch_pose` 现在按顺序检查三件事：

| 顺序 | 信号 | 处理 |
| --- | --- | --- |
| 1 | `LeaderPoseComponent` 非空 | 立刻清（无冷却：清的是「已经坏掉」的状态） |
| 2 | `GetPostProcessInstance()` 为 nil（重定向图被拆掉） | toggle `DisablePostProcessBlueprint` 重建，带 `pose_heal_cooldown`(6 轮) 冷却；连续两次失败才升级到 `MarkRenderStateDirty` + `SetBoundsScale` |
| 3 | `pose_bone_fallback`（开了才跑） | 旧的骨位移窗口，兜底「两个状态都正常但姿势确实不动」的情况。实机确认这条**才是实际生效的那个**：日志里丢姿势那次没有 leader pose、post-process 实例也在，只有骨位移能看出来 |

两个保护：

- 第 2 项连续 5 次都拿不到实例后**放弃**（这个 build 不暴露该 getter 时不至于每 3 秒重建一次）；
- 属性读失败（反射里没有这个属性）时**关掉第 1 项并只记一条日志**，不用每轮刷屏。

重建 / 清 leader pose 之后要让武器重新锚定（§5.8.2）：现在用「等 `pose_weapon_wait`(2) 轮」
代替「等骨骼重新动起来」，因为修复本身已经是一个已知事件，不需要再观测。

> 保留的历史教训（最初四轮迭代怎么把骨位移方案调出来的）见 git 历史与旧版文档；
> 结论是：**能从状态里读出来的事，不要靠观测推断。**
> 调试开关：`report_pose_window`（每 5 轮打印窗口计数，看第 3 项是否真的在兜底）。

### 6.18 衣服颜色发白 / 像褪色（真正的元凶：游戏换掉了槽 0 的材质）

**现象**：红裙子在游戏里是一块米白色布料，但同一个材质里的蝴蝶结、宝石、发饰颜色都正常。

**根因**：日志里的一行

```
material[0] MID_MI_ZeroHun_Head_Injured30_2147474746
```

——槽 0 的材质是一个**父级为 `Hun_Status/MI_ZeroHun_Head_Injured30` 的动态实例**，
这个实例**不是脚本创建的**。原因是我们的模型占用了「头部部件」`SkinParts/Hun_Head_New` 这个资产，
而游戏的**受伤 / 状态系统**会把头部部件的第 0 号材质槽换成受伤皮肤材质（`Hun_Status` 目录下的
`MI_ZeroHun_Head_Injured*`、`Head_health`）。于是连衣裙槽套上了偏白的皮肤着色器：
底色被皮肤 SSS / SCMT 洗白，而其它槽（发 / 脸 / 眼 / 高光）没被动过，所以那些小件颜色正常。

> 排查过程中走过两条错路，记下来避免重犯：
> - 以为是「布料叠加层」`BaseColor Intensity`（`Cloth_02_b` = 0.5、`Cloth_05_b` = 1.0）
>   把饱和度冲淡了，换了三次槽 0 的材质实例、重新 cook 两次，游戏里看不出任何差别——
>   **因为每次都被游戏换回受伤材质**；
> - 以为贴图和 UV 不匹配，用 Blender 按 UV 采样 + 平面渲染对比过 `T_NPC_036_01_d` / `_02_d`，
>   结果证明原映射是对的（红裙 + 皮肤都对）。判断「贴图/UV 有没有错」用这个方法很快。

**修法：材质守卫（`guard_materials`，每轮扫描）**

```lua
material_guard = {
    [0] = "/Game/PBZContent/Characters/Hero/Hun_New_V2b/Material/MI_ZeroHun_Cloth_04_b.MI_ZeroHun_Cloth_04_b",
},
```

- 用 `StaticFindObject` 拿到目标材质实例（它一定已被网格引用、必在内存里），缓存；
- 每轮 `GetMaterial(0)` 比较对象名，不一致就 `SetMaterial(0, 目标)`，并写日志；
- 实测游戏只在初始化时换一次，守卫命中一次之后就不再触发（日志里只有 1 行 `material: slot 0 was ...`）。

要点：

- `UMeshComponent::SetMaterial(int32, UMaterialInterface*)` 是 BlueprintCallable，**能换整个实例**；
  「改参数」不行（见 §6.14），「换实例」可以。
- 守卫的目标实例必须与资产里给该槽的实例一致，否则采到的 albedo 会变成**另一个槽的贴图**
  （每个实例只有一个 albedo 路径）。
- 以后如果发现别的槽也被换掉（例如重伤时），往 `material_guard` 里加一条即可。

### 6.19 过场 / 预览里的原主角（衣服、靴子、乃至「蓬松丝线」）

**现象**：过场动画里出现**两个模型**——可琳思娜 + 原主角（含靴子）；有时还能看到一团蓬松丝线/头发。

**根因（分两层）**：

1. **过场用的是主角的副本 Actor**，不是玩家自己：日志里是 `BP_Seq_Hun_C` / `BP_Seq_Hun_Climax_C`，
   菜单外观预览是 `BP_PreviewAppearance_Hun_C`。这些副本带着**同一批部件资产**，而其中
   `Hun_Body_Simple` 是本 mod 唯一**没有在资产层替换**的网格（它是重定向的姿势来源，只能运行时隐藏，
   见 §5.11 / §6.11）。玩家自己的那份被隐藏了，副本没有 → 原版衣服回来了。
   那团「丝线」就是这份原主角模型的残留，不是 Chaos Cloth（四个 `CA_Hun_*` 组件当时已经全部命中隐藏）。
2. **脚本一度把过场副本当成了玩家**：日志
   `hero body: ... BP_Seq_Hun_Climax_C_1.CharacterMesh0` —— 在**序章地图**里玩家是幼年主角
   `BP_Renewal_Hun_Young_C`，玩家自己的 Actor 上没有我们的承载网格，于是脚本采纳了过场副本；
   之后「副本清理」又因为「它是玩家」而跳过它，正好绕过要清理的对象。

**修法**（`sweep_other_heroes` + `sweep` 家族函数）：

- **采纳规则**：只排除名字含 `BP_Seq_` / `Preview` 的 Actor；已有 Actor 有效时不会被新 Actor 抢走
  （除非新的是玩家 Pawn）。
- **清理范围**：凡 owner 名字含 `Hun`、不含 `Young`、且不是玩家 Pawn 的 Actor，其**除承载网格
  `Hun_Head_New` 与武器之外的所有组件**都隐藏（骨骼网格 / 静态网格 / `ChaosClothComponent` /
  `GroomComponent` / `Budgeted`）。命中过的类名 + 资源名会写进日志一次。
- **副本的身体要保活**：`AlwaysTickPoseAndRefreshBones` + 关 URO 后再隐藏，否则副本里的
  Korinsna 网格（它是 leader pose 跟随者）没有姿势可重定向；并给副本的承载网格清一次 leader pose。
- **幼年主角**（`Hun_Young_*`）全程不碰——我们还没替换那个模型。
- 清理**不依赖 retarget 是否建立**（在 `scan()` 里每轮调用）：序章里脚本本身不接管，
  但那里的成年副本一样要清。

**性能坑（重要）**：第一版把这些扫描放在**每 0.5 秒**跑，遍历 5 类组件（真实关卡上千个
StaticMesh），加上打开着 `report_weapon_chain`（每变化一次就拼整条挂接链字符串）——结果
**明显一顿一顿掉帧**。现在：

- 组件列表**事件驱动重建**：`NotifyOnNewObject` 发现英雄副本的新组件 → 置 `copy_dirty`；
  另外 `copy_rescan_scans`(60 轮 ≈ 30 秒) 兜底；
- 每轮只对**缓存里的那几十个组件**重新套隐藏（必需，衣柜/序列系统会重新打开它们）；
- 排查用的 `report_weapon_chain` / `report_materials` 默认关闭。

### 6.20 「先调用后声明」：Lua `local function` 只能从定义行起可见

这次实机排查踩到一个纯 Lua 的坑，代价很大：`is_hero_copy` 定义在 `hero_owned` 之后，
却被更早的 `hide_copy_bodies` 调用。`local function` 的可见性**从定义行开始**，于是那次调用
解析成了全局 `is_hero_copy`（nil），日志是

```
scan error: main.lua:1749: attempt to call a nil value (global 'is_hero_copy')
```

——**整个清理流程根本没跑**，表现出来却是「过场里两个模型还在」，很容易被误判成逻辑问题。
更糟的是我第一次修的时候只把两个函数互换，仍然让 `hide_copy_bodies` 早于 `player_pawn_name`。

因此新增静态检查 [tools/check_forward_refs.py](../tools/check_forward_refs.py)：
收集所有 `local function` / `local x =` 的行号，再标出**早于声明行的同名调用**。
每次改完 Lua 都要跑：

```powershell
python tools\luacheck.py          # 语法
python tools\check_forward_refs.py  # 先调用后声明
```

### 6.21 过场里衣服又褪色了（副本的材质槽没人守）

**现象**：正常游玩时裙子是红的，但**一进过场**就变回褪色的样子。

**根因**：§6.18 的材质守卫只作用在**玩家自己**的承载组件上（`guard_materials(target)`）。
过场副本身上也有一份同名网格（`Hun_Head_New`，资产覆盖的必然结果），游戏的受伤 / 状态系统同样会把它的
槽 0 换成 `Hun_Status/MI_ZeroHun_Head_Injured*`，而副本从来没被守过。

日志证据（`copy material:` 前缀是本轮新加的）：

```
copy material: slot 0 was MID_MI_ZeroHun_Head_Injured30_2147468964 -> restored MI_ZeroHun_Cloth_04_b (ok)
copy material: slot 0 was <none> -> restored MI_ZeroHun_Cloth_04_b (ok)
```

（`<none>` 的行说明副本的槽 0 甚至是空的——不守的话那块布料直接不显示。）

**修法**：`apply_copy_hiding` 里对每个副本承载网格调同一个 `guard_materials(obj, "copy material")`，
`guard_materials` 增加了一个 `label` 参数用于区分日志来源。

### 6.22 过场里偶发崩溃（缓存里握着已经销毁的组件）

**现象**：过场动画过程中偶尔崩溃，崩点不固定。

**证据**：dump 里崩溃类型是 `0xc0000005`，故障地址 `PBZ.exe+0x144d2d0` —— **与 §6.16 修掉的「传送崩溃」
完全相同**（`tools/dump_crash.py` 一行就能确认）。§6.16 那次的原因是「对已经销毁的组件调引擎函数」，
这次是同一类问题的另一条路径。

**根因**：§6.19 的副本清理为了避掉帧把组件列表**缓存**了下来（`state.copy_list` 最多 72 项、
`state.cloth_list`、`state.copy_carriers`、`state.quiet_parts`），缓存的是 **UObject 引用**。
过场里副本 Actor 被不停创建/销毁，其中一个被销毁之后，下一轮扫描仍会拿着旧引用调
`SetVisibility` / `SetCastShadow` / 反射写——解引用已释放内存 → 崩在游戏自己的代码里。

**修法：缓存只存对象名，用前重新解析**

```lua
local function resolve_component(key)   -- 名字 -> 活对象；解析不到就返回 nil
    local found = try("StaticFindObject", function() return StaticFindObject(key) end)
    found = usable(found)
    if found == nil or full_name(found) ~= key then return nil end
    return found
end
```

- 所有跨扫描缓存（副本部件、副本承载网格、Chaos Cloth、主角空白部件）都改成**名字**；
  每轮 touch 前 `resolve_component`，解析不到就跳过并把列表标脏（下轮重建）。
- **为什么这样是安全的**：扫描跑在游戏线程上，同一轮内对象不会被销毁，所以
  「解析成功 → 立刻调用」之间不存在竞态；危险只存在于**跨轮**持有的旧引用。
- 顺带去掉副本上的反射写入 `bCastHiddenShadow`（`Reflection():ImportText()` 是这类崩溃最危险的调用，
  而阴影已由每次的 `SetCastShadow(false)` 覆盖）。
- 副本列表重建（全关卡扫描）加最小间隔 `copy_rescan_min_scans`（4 轮 ≈ 2 秒）：
  过场里组件是连续生成的，否则「有新组件就重建」等于每轮全扫一次。

**教训**：UE4SS 的 Lua 包装**不会**让 UObject 保活，也不保证读写已释放内存时表现为安全失败——
`valid()`（内部是 `IsValid()`）对悬垂指针同样不可靠。凡是跨扫描保存的东西，存名字。

### 6.23 建链时的编辑器断言崩溃（`IKRetargeterPoseGenerator.cpp:118`）

```
Assertion failed: ChainToMatch != NAME_None
Bone should never be retargeted and not in a mapped chain.
```

这是**建资产时**的崩溃（编辑器直接退出，cook 也就没了），不是游戏崩溃。触发条件有两条，都属于
「链的拓扑不合法」：

1. **两条链共用一根骨**。`FIKRetargetProcessor::GetChainNameForBone()` 对属于多条链的骨返回一个
   **合成名**（把各链名拼起来），映射表里当然没有 → `GetFirstChainMappedToChain()` 返回 `None` → 断言。
   这就是「按关节把手臂拆成 `UpperArm..Forearm` + `Forearm..Hand`」失败的原因：肘关节那根骨被两条链共用。
   解法见 §5.6：切段时**首尾相接但不共用骨**（上一段结束在关节前的最后一根扭转骨上）。
2. **链上的骨不属于任何已映射的链**，同时被当成「应当重定向」——用 `auto_map_chains(FUZZY, True)`
   乱配之后很容易出现。

排查手法（`build_retarget_assets.py` 里已经内置，别再改回去）：
- `log()` **逐行写文件**：断言会杀掉进程，缓冲的日志会全丢（第一次排查就是因为这个只拿到上一次运行的旧结果）。
- 建链后打印每条链的骨（`bone_parents` + `chain_path` 走一遍层级）。
- 映射后逐条 `get_source_chain(name)` 核对，并在对齐前打印每个 op 的 `chains_to_retarget`。
- **不用 `auto_align_all_bones`**：它会遍历「它认为可重定向」的全部骨，撞上未映射的就断言；
  改成 `auto_align_bones(本链的骨, CHAIN_TO_CHAIN, TARGET)` 一条链一次，既能定位问题也不会被无辜的骨带崩。

### 6.24 坐下 / 躺下 / 被击倒时整个人浮空

根因和修法见 §5.12：骨盆被写进 `Spine` 链，FK 链 op 的 `TranslationMode=None` 每帧把它摆回参考姿态，
Pelvis Motion 算出的位移被覆盖 → 骨盆高度恒定，只有四肢在动。

诊断靠 `config.report_ground_every`（§8.9）：站立正常只是一个巧合（参考姿态本来就是站姿），
真正要看的是**游戏本体骨盆和我们的骨盆的 Z 差**在蹲下时是否跟着变。

---

### 6.25 偶发卡顿：每轮三次全关卡搜索

**现象**：正常跑图时每隔一两秒卡一下，过场和读图时更明显。

**根因一：每轮扫描里的三次全关卡搜索。** `anchor_held_weapons`、`hide_scabbards`、`anchor_back_items`
各自调用一次 `FindAllOf("SkeletalMeshComponent")`：这个调用会遍历**整个 UObject 数组**
（本作实测 15 万+ 对象）并为每个命中创建 Lua 包装。每 0.5 秒三次 ≈ **每秒 90 万次对象访问**。

**根因二：日志。** 每行日志都是一次「打开文件 + 写 + 关闭」加一次控制台打印，读图/过场时
`new component:` 这类行成千上万。

**修法**：

| 位置 | 原来 | 现在 |
| --- | --- | --- |
| 武器 / 刀鞘 / 腰后刀 | 每轮**各**一次全关卡搜索（3 次） | 每轮**一次**搜索，结果按名字缓存，三个 job 都读缓存（`refresh_targets`） |
| 阴影清理 | 每轮 19 次 `StaticFindObject` | 每 2 轮一次（`quiet_parts_every`） |
| 日志 | 每行都写 | release 只写「出问题」的行（`log_level=1`），dev 才全写（`log_level=2`） |
| 监听器 | 每次回调都可能写一行 | 回调只做两跳 `ExecuteInGameThread` 后转交 `inspect_new`，诊断行都在 level 2 |

**关于 `NotifyOnNewObject`（监听器）：2026-11 已改为「只监听稀有类」，见 §12。**
旧结论是「监听器必须保留在引擎网格基类上」，因为当时轮询找不到英雄。后来的排查证明那是个
**枚举 bug**（`K2_GetComponentsByClass` 返回的 TArray 元素是空包装，§12.7），而不是「轮询不可行」：
把监听器从 `SkeletalMeshComponent`/`StaticMeshComponent` 上摘掉、换成「缓存 pawn + 按 owner 定向枚举
+ 子树遍历」之后，英雄接管、武器跟随全部正常，而战斗时那一秒级的卡顿消失了。
现在只监听 `ChaosClothComponent` / `GroomComponent` 这两个稀有类，作为「过场副本出现了」的信号。

### 6.25.1 「用组件树替代全关卡搜索」这条路走不通（已回退）

想法很自然：我们要动的武器**本来就挂在英雄身上**（锚定条件就是 `GetAttachParent() == state.source`），
而挂在英雄组件上的东西一定在英雄 Actor 的子树里，那么一次
`GetChildrenComponents(includeAllDescendants=true)` 就能替代全关卡搜索，还能顺带拿到英雄的全部部件。

实机结果是**有害的**：

```
FAILED GetRootComponent: attempt to call a TrivialObject value (method 'GetRootComponent')
shadow: 0 part meshes on the hero
```

**这个 build 里 `AActor:GetRootComponent` 不能从 Lua 调用**（返回的是 UE4SS 的 `TrivialObject`，
不是可调用的 UFunction）。于是「英雄组件树」永远是空的，而依赖它的两处都静默失效：

- `hero_part_components` → 0 个部件 → **空白部件没有被移出阴影/主通道** → 角色脚下的地形开始
  **闪黑**（就是 §6.5.11 那个老问题的翻版，这次表现为地面上的黑斑一闪一闪）；
- 副本清扫若也改成「遍历副本 Actor 的组件树」，过场里**原版衣服会整片回来**（因为它同样拿不到 root）。

教训：**在这个 build 里，凡是「从 Actor 拿根组件再往下走」的 API 都不能用**；
枚举组件要用 `K2_GetComponentsByClass`（能用），或者直接用 `FindAllOf`。
现在的实现回到「每轮一次 `FindAllOf` + 按名字缓存」，比原来的三次省 2/3，但没有换掉可靠的 API。

> 判断这类问题的方法：日志里出现 `attempt to call a TrivialObject value` 就是「这个函数在本 build 里
> 不存在」。`try` 会记一行，而依赖它的逻辑会**静默**退化成空集合——所以任何「把搜索换成遍历」的优化，
> 都要在 dev 日志里确认产出数量（`targets: N weapon(s)` / `shadow: N part meshes`）不是 0。

---

### 6.26 轮询发现英雄的 bug：`state.tick` 只在 `setup()` 末尾自增

把监听器换成「每 N 轮轮询一次玩家 Pawn」时，所有节奏（发现、重扫、冷却）都用 `state.tick` 表示，
而 `state.tick` 是在 `setup()` 的**最后一个语句**里自增的。问题是 `setup()` 在没有英雄时会
**提前 return**——于是 `state.tick` 永远停在 0：

```
第 1 轮: tick=0，discover_tick=nil → 允许发现 → 关卡还没加载完，什么也没找到 → discover_tick=0
第 2 轮: tick 还是 0 → 0-0 < 4 → 跳过；以后每一轮都一样
```

表现就是**整局 mod 完全没生效**：原版衣服还在、可琳思娜不动、武器挂在魂身上。教训：

- **计数器的自增不要放在「可能提前 return」的函数里**。现在在 `scan()` 的第一行自增。
- 所有周期判断都依赖它，所以这类 bug 会一次性让「所有以轮为单位的机制」失效。
- `tools/smoke_lua.py` 的 `late` 世界专门复现它：先跑几轮空世界，再注入英雄，断言之后能找到。
  把自增移回 `setup()` 末尾，这个用例立刻失败（已验证）。

---

## 7. 运行期脚本（`ue4ss/KorinsnaRetarget`）

### 7.1 三个版本：release / dev / perf

脚本只有一份代码，安装时用不同的 overlay 切换日志与诊断：

| 版本 | 安装命令 | 差异 | 用途 |
| --- | --- | --- | --- |
| **release**（默认） | `tools\install_lua.ps1` | `log_level=1`：**只在出问题时写日志**（健康的整局会话不会产生日志文件） | 游玩 |
| **dev** | `tools\install_lua.ps1 -Profile dev` | 额外装 `config.dev.lua`：`log_level=2` 全量日志 + 各类只读普查（`report_*`） | 排障 / 开发 |
| **perf** | `tools\install_lua.ps1 -Profile perf` | 行为同 release，只额外打开 `profile_scans`（`profile:` 行按 level 1 写，所以静默配置下也能看到） | **测卡顿** |

**行为完全一致**：两者都注册同一组监听器、都用同一套锚定与看门狗逻辑，差别只有日志和普查开关。
所以 dev 里看到的现象就是 release 里会发生的事（dev 的 `target_rescan_scans` / `copy_rescan_scans` /
`discover_every` 也被刻意设成与 release 相同的值，否则会出现「dev 流畅、release 卡」的错觉）。

> **测卡顿必须用 perf 档，不能用 dev**：dev 自己会写大量日志，测到的是日志器而不是 mod。
> 2026-11 那次「卡成 PPT」的排查就是先在 dev 里看着「scan 只有 2 ms」而找不到原因（§12.1）。

`install_lua.ps1` 会先清空目标目录再拷，所以各版本不会混在一起（`config.dev.lua` 只有 dev/perf 才有）；
它也顺手维护 `mods.json`，并清掉上一次的日志（`-KeepLog` 可保留）。

### 7.2 每轮扫描都做什么（性能预算）

`scan()`（每 0.5 秒）→ `drain_garments()`（布料通知，稀有）→ `discover_hero()`（只在英雄/载体不全时真的查）
→ `setup()` → `sweep_other_heroes()`。完整架构与取舍见 **§12**。

| 动作 | 次数 | 说明 |
| --- | --- | --- |
| 武器 / 刀鞘 / 背挂发现 | 2 次 `GetChildrenComponents` | **局部**遍历英雄源组件 + 载体的子树，`classify_target` 逐个判 |
| 全关卡搜索（兜底审计） | 每 120 轮 1 次 | `refresh_targets()`，约 40 ms；换图/接管时 `reset_targets()` 强制一次 |
| 英雄发现（轮询） | 每 4 轮 1 次（仅在源/载体不全时） | `FindAllOf` + `owner == pawn`；接管完整后降到 60 轮审计 |
| 缓存解析 | 约 6 次 `StaticFindObject` | 3 件武器 / 鞘 / 刀，名字查表 |
| 姿势看门狗 | 1–2 次属性读 + 4 次骨读 | `LeaderPoseComponent`、`GetPostProcessInstance`、骨位移兜底 |
| `refresh_from_actor` | **0 次全关卡** | 改用缓存的 pawn + 定向枚举（`K2_GetComponentsByClass` 在本 build 不可用，§12.7） |
| 材质守卫 / 阴影 / 角色对齐 | 各 1 次 | 全是 O(1) |
| 副本清扫 | 每个副本 actor 一次全关卡重建 | 由布料通知触发，按 actor 去重（§13.3） |
| 日志 | release **不写** | 只有引擎调用失败 / scan 报错才写一行 |

`main.lua` 的结构：`boot()` → 每 `rescan_interval`（0.5s）跑一次 `scan()`/`setup()`
（dev 版本另外挂 `NotifyOnNewObject`）。所有开关在 `config.lua`（文件优先于脚本内默认值）。

| 开关 | 默认 | 作用 |
| --- | --- | --- |
| `carrier_mesh_name` | `Hun_Head_New` | 承载网格的部件名 |
| `anim_class_path` | `ABP_Korinsna_Retarget_C` | 重定向 AnimBP 的类路径 |
| `hide_source_visibility` | `true` | 隐藏原身体（姿势照常 tick） |
| `force_anim_refresh` | `true` | 强制 `AlwaysTickPoseAndRefreshBones` + 关 URO |
| `hide_scabbards` | `true` | 隐藏会乱飞的刀鞘（`back_items` 除外） |
| `quiet_blank_parts` / `quiet_parts_every` | `true` / `2` | 空白部件移出阴影/主通道（**只处理主角自己的组件**，见 §6.15），每 2 轮重申一次 |
| `carrier_cast_shadow` | `false` | 承载网格不投影（避免黑斑） |
| `attach_weapons` | `true` | 把手持武器 Actor 对齐到我们的手骨（§5.8） |
| `grip_distance` | `{ r=6.0, l=6.0 }` | 握点距手骨的距离（cm），0 = 保持游戏值 |
| `sheathed_anchor` / `sheathed_source_bone` / `sheathed_push_cm` | `Bip001-Spine` / `spine_03` / `2.0` | 收起的武器搬到我们的脊柱并外推（§5.8.1） |
| `anchor_max_gap_cm` | `100` | 双手间距超过此值时不做武器锚定（姿势明显是参考姿势，§5.8.2） |
| `back_items` / `back_item_push_cm` | `Hun_Knife` + 刀鞘 / `2.0` | 腰后短刀锚到骨盆并外推（§5.10） |
| `hide_copy_bodies` / `hide_copy_body_meshes` | `true` / `{ "Hun_Body_Simple" }` | 隐藏过场 / 预览副本上的原版身体（§6.19） |
| `hide_hero_cloth` | `true` | 隐藏英雄的 Chaos Cloth 服装组件（§6.19） |
| `hide_copy_outfit` | `true` | 副本上除承载网格与武器外全部隐藏（§6.19） |
| `copy_rescan_scans` / `copy_rescan_min_scans` | `60` / `4` | 副本组件列表的全关卡重建周期与最小间隔；新副本由布料通知按 actor 提前触发一次（§13.3） |
| `target_rescan_scans` | `120` | 武器 / 刀鞘 / 腰后刀的**兜底审计**周期；平时靠英雄子树局部遍历发现（§12.6） |
| `discover_every` / `discover_audit_scans` | `4` / `60` | 英雄「源+载体」不全时的轮询间隔 / 完整后的审计间隔（轮询是唯一发现路径，§12.5） |
| `pose_watchdog` | `true` | 姿势卡住（游戏重设 leader pose）时立刻清掉并重建，见 §6.17 |
| `pose_bone_fallback` | `true` | 骨位移窗口兜底（慢速路径，§6.17） |
| `pose_step_move_cm` / `pose_step_stuck_cm` | `0.5` / `0.3` | 每轮分类阈值（仅兜底路径使用） |
| `pose_slip_window` / `pose_stuck_marks` | `12` / `4` | 滑动窗口与判决门槛（慢速路径，约 2 秒） |
| `pose_big_jump_cm` | `20.0` | 单轮快判：原身体动了超过这个距离而我们完全没动 → 直接判定（实测一拍 98.8 cm，0.5 秒内恢复） |
| `pose_heal_cooldown` | `6` | 两次重建之间的最小扫描间隔 |
| `pose_weapon_wait` | `2` | 重建后等几轮再重新锚定武器（§5.8.2） |
| `log_level` | `1` | 0 静默 / 1 只写出问题的行（release）/ 2 全量（dev 用 2） |
| `report_pose_window` | `false` | 打印看门狗自身视角的计数（排障，§8.6） |
| `material_guard` | `[0] = ".../MI_ZeroHun_Cloth_04_b"` | 被游戏换掉的材质槽，每轮把目标实例换回去，见 §6.18 |
| `report_materials` | `false` | 打印 8 个槽实际使用的材质实例名（排障，见 §6.18） |
| `rescan_interval` | `0.5` | 扫描周期（秒） |
| `probe_only` | `false` | 只观察、不改动 |
| `report_weapon_geometry` / `report_weapon_chain` | `false` | 武器几何普查 / 挂接链变化记录（排障，**开销大**） |
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

### 8.4 判断「材质是不是被游戏换掉了」

打开 `report_materials`，会打印 8 个槽实际使用的实例：

```
material[0] MI_ZeroHun_Cloth_04_b
material[0] was MID_MI_ZeroHun_Head_Injured30_2147474746 -> restored ...
```

- 槽里出现 `MID_...` 且父级不是我们指定的实例 → 游戏在运行时换了材质（§6.18）；
- `material: slot N was ... -> restored ...` 是守卫生效的那一行，正常情况下**只会出现一次**。

### 8.5 判断「贴图和 UV 对不对」（不用进游戏）

Blender 里按多边形 UV 采样 tga，或者直接给每个材质槽套一个「贴图 → Emission」的平面材质渲染一张，
和参考图对照即可。这条比在游戏里反复换材质快得多，也是这次排除「褪色是贴图/UV 问题」的方法（§6.18）。

### 8.6 判断「姿势看门狗为什么不动」

打开 `report_pose_window`，每 5 轮打印看门狗自己的视角：

```
pose window: 4/12 stalled (this scan=true) | src (-10.6, 36.7, 4.9) move 63.58 | ours (10.2, 38.2, 5.6) move 0.00
pose: stalled (source moved 63.58, ours moved 0.00) - re-arming the retarget #1 [escalated]
```

读法：

- `move` 是**组件空间**的每轮位移；若 `ours` 的某个分量长期恒定、其余分量大幅摆动，说明
  测量空间选错了（世界坐标会把转身当成动，§6.17）。
- `no read-out` 表示这一轮骨骼读取失败（`GetBoneTransform` 偶发返回零值），它不参与判定。
- 判决是滑动窗口里的次数，所以单看某一轮 `stalled=false` 不代表没问题。

### 8.7 判断「这个副本该不该清」

打开日志看 `copy part:` / `cloth:` 行：

```
copy part: SkeletalMeshComponent          Hun_Body_Climax            (CharacterMesh0)
cloth: hiding CA_Hun_Skirt_Climax owner=BP_Renewal_Hun_Climax_C_...
```

- 出现 `state: not adopting ... (sequence/preview actor)` 说明脚本正确拒绝了过场副本；
- 若某个副本的部件**没有**出现在 `copy part:` 列表里，说明它没被判定为副本（检查 owner 名是否含
  `Hun`、是否被当成了玩家 Pawn）。

### 8.8 判断「崩溃是不是我们引起的」

```powershell
python tools\dump_crash.py "K:\SteamLibrary\steamapps\common\PBZ\platform\steam\ue4ss\crash_*.dmp"
# code=0xc0000005 addr=0x14144d2d0 -> PBZ.exe+0x144d2d0
```

- 故障地址 **`PBZ.exe+0x144d2d0`** 是本 mod 已知的「对已销毁 UObject 调引擎函数」签名
  （§6.16 的传送崩溃、§6.22 的过场崩溃都是它）。看到它先查：有没有跨扫描缓存的组件引用、
  有没有在 `ExecuteInGameThread` 之外碰引擎对象。
- 时间对不上（崩溃前后日志里脚本没有动作）时，先怀疑游戏自身：临时把 `ue4ss/Mods/mods.json`
  里 `KorinsnaRetarget` 关掉，复现一遍再判断。
- 崩溃前后**脚本最后一行**很有用：日志是逐行追加的，最后一行就是崩溃瞬间脚本正在做的事。

### 8.9 判断「浮空是骨盆没动，还是本体本来就高」

`ue4ss/KorinsnaRetarget/config.lua` 里打开：

```lua
report_ground_every = 2,   -- 每 2 次扫描（约 1 秒）打一行
```

每行形如：

```
ground: pelvis src -1240.1 ours -1189.4 (+50.7) | foot src -1282.7 ours -1219.9 (+62.8) | actor -1188.2 | ball_l/Bip001-L-Toe0
```

- **`ours pelvis` 在一整场里是个常数** → 骨盆根本没被重定向（§5.12 / §6.24），不是比例问题；
- **两边都跟着姿势变、只是差一个常量 Δ** → 那是比例/参考姿态的常量偏移，用 Pelvis Motion 的
  `TranslationOffsetGlobal.Z` 或 `BlendToSourceTranslation` 补偿；
- `foot` 那一列只是参考：`ball_l` 和 `Bip001-L-Toe0` 相对鞋底的高度不同，Δ 有十来厘米是正常的，
  **不要**用脚骨 Z 去做对齐补偿。

`foot` 后面的 `ball_l/Bip001-L-Toe0` 是实际取到的骨名（左右取到哪根就写哪根）。

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
| 手指动画 | 已做：A-pose 绑定姿态 + 逐关节切段（§5.4），指节干净 | 若某些手势出现指节穿插，改 `ue/retarget_config.json` 里对应那一节的旋转权重/关闭该节 |
| 头部 | 只用 Neck 链跟随，脸不参与 | 给 `head_Bone001/002` 单独建链 + 逐骨偏移 |
| 裙摆 | 已做：KawaiiPhysics 物理（§11），球体碰撞 + 不限角 | 穿模（蹲下最明显）来自「5 段骨 + 网格体积」，要更贴合需在 ABP 里做骨骼细分（本 fork 未验证） |
| 扭转骨轴向限制 | 切段后每段刚性复制同一关节（§5.6），没有「只绕骨轴」的限制 | 若仍出现糖果纸扭曲，在 ABP 里加约束节点 |
| 衣服质感 | 中性 ARM：全粗糙、非金属 | 想要一点高光时把 `_ARM` 的 G 改成 180（参考 2B mod 的值） |
| 皮肤颜色 | 可琳思娜的腿/手本来就接近白色，槽 1 借的 `Cloth_02_b` 会再混一点布料噪点 | 想更干净时把槽 1 也换成纯底色实例（要同时换它唯一的 albedo 贴图路径） |
| 游戏换材质 | 只守住槽 0（受伤头材质），玩家与过场副本都守（§6.18 / §6.21） | 若别的槽也被换掉，往 `material_guard` 里加条目 |
| 跨扫描缓存 | 只存对象名，用前 `StaticFindObject` 重新解析（§6.22） | 若有新的缓存需求，沿用这个模式，不要保存 UObject 引用 |
| 运行期开销 | 事件驱动缓存（§12）：监听回调只入队，全关卡扫描只剩换图/接管各一次 + 10s 一次的武器兜底 + 布料两类 | 若还有周期性卡顿，用 dev 的 `profile:` 行区分「脚本慢」和「引擎卡」 |
| 姿势恢复 | 直接读 `LeaderPoseComponent`，下一轮即恢复（§6.17） | 若某天该属性读不到，`pose_bone_fallback` 仍会兜底（慢 ~2 秒） |
| 武器握点 | 单手/双持按手骨距离常数吸附；`*_child` 挂点的御剑完全交给游戏（§14.1） | 双手武器（斩马刀）左手不在杆上，原因已查明（§14.2），修法方向也写明 |
| 收起的武器 | 挂到 `Bip001-Spine` + 沿背面外推 2cm（§5.8.1） | 若某类大武器在背上穿模，可按武器类型给不同的锚骨/外推 |
| 姿势丢失 | 看门狗 2 秒内重建（§6.17） | 若能找到游戏重设 leader pose 的那个调用点，可在源头阻止而不是事后重建 |
| 过场副本 | 运行时隐藏副本身上除我们网格与武器外的一切（§6.19） | 更彻底的做法是在资产层把 `Hun_Body_Simple` 也替换成空白网格（会丢失重定向源，需另找姿势来源） |
| 披风/长发物理 | 头发已做 KawaiiPhysics（4 条链，§11）；披风仍未处理 | 披风若也要物理，按 §11.1 加一条 chain 即可，但要先确认它挂在哪根骨下 |
| 阴影 | 承载网格不投影（避免黑斑） | 修好 retargeted mesh 的深度 pass 后可以打开 |

## 11. 头发与裙摆物理（KawaiiPhysics，本轮）

### 11.1 管线

| 环节 | 位置 |
| --- | --- |
| 唯一数据源 | `ue/kawaii_config.json`（`chains` / `profiles` / `limits`） |
| 烘焙者 | `ue/ProjectPBZ/Source/ProjectPBZ/KorinsnaEditorLibrary.cpp` → `ConfigureKawaiiNode()` |
| 触发 | `ue/scripts/build_retarget_assets.py`（构建 ABP 时按配置写节点） |
| 产物 | `ABP_Korinsna_Retarget` 里 5 个 Kawaii 节点（1 条裙摆链 + 4 条头发链），谱系 `Retarget → Kawaii… → Root` |
| 校验 | 构建日志里的 `kawaii[i] root=… spheres=… exclude=… capsules=… alpha=…` |

改参数只需要改 JSON 再跑一次
`UnrealEditor-Cmd.exe <uproject> -ExecutePythonScript=…\build_retarget_assets.py`，
**不需要**重新导入模型，也不需要重跑 Blender。

### 11.2 这个 fork 的六个硬约束（全部实测）

1. **链的根骨是运动学骨**（`bSkipSimulate = true`）：它只跟着动画走，永远不被物理推动。
   所以根骨必须选「要模拟的第一根骨的公共父骨」，再用 `ExcludeBones` 把它真正的孩子链剪出来。
   把根骨写成 `*_skirt_1` 时，第 1 根骨永远不会动 —— 这是最早「裙子没有物理感」的根因；
   改成 `Bip001-Pelvis` / `head_Bone002/003` + exclude 之后节点数从 29 降到 5，行为才正确。
2. **没有速度上限字段**：速度衰减只有 `Velocity *= (1 - Damping)`。想「限制速度」只能提 Damping。
3. **`Stiffness` 是往动画姿态拉的比例**（`Location += (pose - Location) * (1-(1-Stiffness)^Exponent)`）：
   - 太高（0.96）→ 布料被「焊」在贴腿的动画姿态上 → 碰撞顶开后立刻拉回 → **必然穿模**
   - 太低（0.05）→ 移动时形状塌掉，裙子/头发会并成一片又窄又薄的片
   - 最终取 **0.30**
4. **碰撞判定是 `距离 < 球半径 + 骨骼半径`**，所以 `profiles.*.settings.radius` 是一个免费的「间隙余量」，
   比放大球更安全（放大球会让左右大腿的球在中心线重叠）。
5. **球体在游戏里有效，胶囊在游戏里无效**（见 11.4）。
6. **`WorldDampingLocation/Rotation` 默认 0.8**，设成 1.0 是极值。

### 11.3 最终参数

| profile | damping | stiffness | limit_angle | radius | 碰撞体 |
| --- | --- | --- | --- | --- | --- |
| `skirt` | 0.55 | 0.30 | 0（不限角） | 2.5 | 18 个球：臀 2 + 大腿 5×2 + 小腿 3×2 |
| `hair_long` / `hair_short` | 0.60 | 0.30 | 50° | 0.6 | 5 个球：`head_low/mid/top` + `neck` + `chest` |

`world_damping_location = world_damping_rotation = 1.0`，`planar_constraint = none`。

- **裙摆不限角**：一旦有角限，被碰撞顶开的位移会被硬拉回，穿模变成常态。
- **头发限 50°**：头发质量轻，不限角会甩到脸上；50° 足够摆动但不会翻起来。
- **裙摆 `radius = 2.5`**：`Stiffness 0.3` 每帧把裙子往贴腿的姿态拉 30%，稳定后裙子会停在腿里；
  加 1.9cm 的骨骼半径余量把平衡点推到网格外面，且不改变球布局。
- **大腿球半径 9.5 不能加到 10.5**：球心在 `x = ±9.6`，半径 10.5 时左右球在中心线**重叠**，
  正前方的裙片同时落在两个球里，每帧被互相弹开 → 裙子塌陷 + 抽动。
- **头发必须有碰撞体**：没有时头发会穿进头/颈/胸。

### 11.4 胶囊体在游戏里不生效（重要）

`CapsuleLimits` 的数据能被烘焙、也能被游戏加载，但**游戏里不产生碰撞**：

- 运行时回读（dev 版 `report_physics_nodes`）确认：`capsules=5`，
  驱动骨 `Bip001-L-Thigh / R-Thigh / L-Calf / R-Calf / Bip001-Pelvis` 全部绑定成功，
  `len = 39.70 / 42.43`、`r = 9.5 / 7.5 / 11.0`，实时胶囊中心 `at=(9.6, 0.6, 74.9)` 等与理论完全一致。
- 编辑器预览里同样的胶囊能顶住裙子，**游戏里完全不顶**。
- 结论：这个旧 fork 的胶囊求解在运行时没被调用。用「沿腿加密的球」代替胶囊。

### 11.5 已否决的两条路线

| 路线 | 否决依据 |
| --- | --- |
| 用自带新版 KawaiiPhysics 覆盖游戏旧版（`docs/Kawaii_Check.md` 的方案） | 游戏是 **monolithic 构建**：`PBZ.exe` 导入表只有 56 个系统 DLL、导出表只有 523 个 Wwise/AntiLag 符号，游戏目录没有 `Core.dll/Engine.dll/AnimGraphRuntime.dll`；我们自己的 Game target 也把插件模块静态链接进 exe（无 DLL 产出）。UE4SS 是注入 hook，不能加载 UE 插件模块。 |
| RigidBody + PhysicsAsset（`docs/Rigidbody.md`） | 手写 `FConstraintInstance` 缺 `Pos1/PriAxis1/Pos2…` → 231 个模拟体自由下落。改用 `FPhysicsAssetUtils::CreateFromSkeletalMesh` 生成后才正常（369 体/368 约束/`ComponentSpace`/重力 −980），但实测裙摆穿模、头发乱飘、抽动依旧，且没有 Kawaii 的「按姿态回弹」手感。配置保留在 `ue/rigidbody_config.json`，`build_retarget_assets.py` 的 `PHYSICS_CONFIG` 可切回。 |

### 11.6 调参/排障手段（仅 dev）

| 手段 | 用法 |
| --- | --- |
| `F1`–`F6` | 阻尼/刚度阶梯（含「物理关闭」），用于二分定位 |
| `F7`–`F9` | `PlanarConstraint` X/Y/Z |
| `F10` | 逐帧采样（游戏线程），记录裙摆/头发骨骼与碰撞体的实时位置 |
| `report_physics_nodes` | 一次性回读节点参数、球/胶囊数量与绑定情况 |
| `profile: scan took …` | 脚本自身耗时 |

## 12. 运行期性能：卡顿的四个真实成因与最终架构

这一节记录的是一次完整的排查：症状是「每隔一段时间卡成 PPT，十几秒到一分多钟，打怪时更容易」。
过程里有三次错误归因，结论都来自**对照实验和 quantized 到毫秒的探针**，不是猜测。
按量级从大到小排列，四条机制最后都修掉了。

### 12.1 方法论：先做对照，再读探针

| 步骤 | 做法 | 得到的结论 |
| --- | --- | --- |
| 1 | 给 `scan()` 计时，并把「两次 scan 的间隔 vs 预期间隔」分开记录（`profile:` 行，见 12.6） | 我们的扫描只有 2–7 ms，而空档长达 1 s |
| 2 | 现象是「画面卡、声音正常」 | 游戏**线程**被占，不是 GPU/加载 |
| 3 | `mods.json` 里关掉 Lua 模组（pak 保留） | **游戏立刻流畅** → 卡顿确实来自 Lua |
| 4 | 再移走 pak（纯原版） | 纯原版也流畅，排除资产/引擎设置 |

关键教训：**`profile: scan took` 只统计 `scan()` 内部**。写在 `scan()` 之外的东西（对象监听回调、
`ExecuteInGameThread` 队列、日志的同步文件 I/O）在探针里**完全不可见** —— 第一轮排查就是被这一点
误导，盯着「scan 只有 2 ms」而找不到原因。

### 12.2 机制一（最大）：`NotifyOnNewObject` 挂在引擎基类上

**曾经的做法**：注册

```lua
NotifyOnNewObject("/Script/Engine.SkeletalMeshComponent", on_new_object)
NotifyOnNewObject("/Script/Engine.StaticMeshComponent", on_new_object)
```

**它原本的作用**：让「英雄的部件出现了」变成事件驱动。历史上纯轮询版本确实找不到英雄（原因见 12.5 的
`K2_GetComponentsByClass` 坑），所以监听器被当成必需品，甚至写过「去掉它就整个坏掉」的注释。

**实际代价**：这两个类是**整个世界的基类**。实测一场战斗里 `dropped` 计数累计到约 14800，说明短时间
内有上万次通知；`NotifyOnNewObject` 按 `IsA` 匹配子类（`SplineMeshComponent`、`InstancedStaticMeshComponent`、
`SkeletalMeshComponentBudgeted` 全部命中），UE4SS 每次都要构造一个 Lua userdata 并调用进 Lua。
**回调体再轻也没用** —— 成本在分发本身。累计起来就是那一个个约 1 秒的空档。

**修法**：引擎网格类**不再监听**。见 12.3。

### 12.3 机制二：`StaticFindObject` 命中不存在名字时的慢路径

**曾经的做法**：`resolve_component(key)` 用 `StaticFindObject(key)` 把缓存的名字重新解析成对象（因为
缓存的 UObject 引用会变成悬垂指针，§6.22）。

**它原本的作用**：安全地使用跨帧缓存 —— 名字是字符串，先解析再触碰，避免在已释放对象上调用引擎函数。

**实际代价**：名字**已经不存在**时，`StaticFindObject` 走全局查找的慢路径（实测约 10 ms/次）。
一旦有一条「owner 读不到」的延迟列表（战斗时会被无限追加），每轮重试 32 个就是 300 ms，
连续几轮就是十几秒。探针里的典型证据：

```
profile: scan took 323.0ms (tick 51 | ... drain 323.0 ...)   ← 但这一轮 drained 0
```

**修法**：延迟列表限量 32 条、**每条只重试一次**、且只收「网格名含 `Hun` 或组件名以 `mesh`/`Character`
开头」的对象。真判不出来的交给周期扫描。同时把**热路径**上的 `try()`（失败会同步写日志文件）
换成 `soft()`。

### 12.4 机制三：日志是「每条一次同步文件写」

`try(label, fn)` 失败会调 `trace_problem` → `io.open` + 写入 + `io.close`。它原本的作用是**让失败可见**
（「一个被吞掉的错误是这个 mod 最难调的原因」）。

问题在于它不区分「我们关心的对象」和「关卡里别人的对象」：挂在基类上的 `try` 一旦对别人的组件失败，
就会在游戏线程上做几百次文件打开。修法与 12.3 相同：热路径改 `soft`，真正的失败用一次性 trace 记录。

### 12.5 机制四：队列里堆积的 UObject 引用 → Lua GC 停顿

有一版实现把通知对象放进队列、按「数量」批量处理，其中「英雄未接管时每轮 4000 个」。两个后果：

1. **单帧尖峰**：4000 个分类在一个 game-thread 回调里跑完（每个几十次反射调用）。
2. **GC 停顿**（更隐蔽）：`dropped 7010` 说明队列长期顶在上限，几千个 UObject userdata 成为 GC 的
   巨大根集合。证据是「耗时与数量无关」：

```
profile: scan took 1125.0ms (tick 98, drained 80 ...)
profile: scan took 1102.0ms (tick 100, drained 32 ...)
```

处理 80 个和 32 个耗时几乎一样 → 成本不在分类，而在回收阶段。

**结论**：数量上限解决不了问题，**时间预算 + 小上限**才解决。最终连队列一起删掉了（12.6）。

### 12.6 最终架构

| 关注对象 | 机制 | 触发/节奏 |
| --- | --- | --- |
| 英雄本体（重定向源 + 载体） | **定向轮询**：缓存 pawn 对象（`valid()` 校验，失效才重新枚举），只枚举 `owner == pawn` 的骨骼网格组件，同时喂给 `consider()` | 未接管/缺载体时 4 tick（2 s）；接管完整后 60 tick（30 s）审计 |
| 武器 / 刀鞘 / 背挂 | **定向子树遍历**：`children_of(源组件)` + `children_of(载体)` → `classify_target()` | 每 scan（0.5 s） |
| 布料 / Groom（原主角衣服本体） | **监听器**，但只注册这两个稀有类；回调只入 64 条小队 | 生成即触发 |
| 过场副本 | 布料通知 → 读出 `owner` → 若是 hero copy → **每个 actor 触发一次**全关卡重建（`copy_scanned` 去重），之后按名字逐帧重新隐藏 | 每个副本一次 |
| 英雄部件阴影 | 直接读 `state.hidden_list`（隐藏列表本身就是那批部件） | 每 2 scan |
| 兜底 | `refresh_targets()` 全关卡审计 | 每 120 tick（60 s） |
| 深兜底 | `collect_copy_components` / `collect_hero_garments` | 列表不存在时（换图/首次接管） |

**测量结果**：普通游玩 `scan took` 稳定在 2–7 ms；过场里最多一次 76–284 ms（每个副本一次的重建）。

### 12.7 三个必须记住的引擎/UE4SS 坑

1. **`K2_GetComponentsByClass` 返回的 TArray 元素是空包装**，逐个索引只会拿到 `null`。
   按 actor 找组件必须用 `FindAllOf(短类名)` + `GetOwner()` 比对。
   这个坑曾经让「纯轮询」版本永远找不到英雄，从而被误判成「轮询不可行、必须用监听器」。
2. **`GetChildrenComponents(true, out)` 的 out 参数是真 Lua 表**，可以直接读 —— 所以
   `children_of()` 可用，而 1 里的那个不可用。两者差别只在这条注释里，很容易混淆。
3. **`GetAllSocketNames()` 的元素是 `RemoteUnrealParam`**，必须 `raw:get():ToString()`。

另外：`FindAllOf` 一次全关卡遍历约 **40 ms**（>150k 对象），所以任何「每 N 秒扫一遍」的方案都要按
40 ms 计价；`GetChildrenComponents` 是局部操作，可以每帧跑。

### 12.8 定位工具

`perf` 档（`tools\install_lua.ps1 -Profile perf`）＝ **release 行为 + 只写 `profile:` 行**。
用 dev 档测卡顿是错的：dev 自己会写大量日志，测到的是日志器而不是 mod。

```
profile: scan took 23.4ms (tick 812 | setup 3.0 sweep 18.0 other 2.4)
                                             ← 我们自己慢，且能看出是哪一段
profile: 640ms stall before tick 813 (previous scan took 3.1ms)
                                             ← 上一轮我们只花了 3ms：卡在 scan 之外
```

第二行出现且 `scan took` 很小，就往「scan 之外」找：对象监听回调、`ExecuteInGameThread` 队列、
日志文件写。这一条是这次排查的分水岭。


## 13. 部件隐藏与「动画必须仍然正确」：当前全部做法

这个 mod 的视觉正确性靠三件事同时成立：**看见可琳思娜**、**看不见魂的部件**、**可琳思娜一直在被动画驱动**。
三者互相牵制 —— 隐藏手段选错会直接把动画搞坏，所以这里把当前所有做法和背后的原因列全。

### 13.1 三条隐藏路径，各有适用对象

| 对象 | 做法 | 为什么不能用别的 |
| --- | --- | --- |
| 魂的身体/斗笠/围巾/长发/披风 | **资产层清除**（`ue/scripts/build_mod_assets.py` 把网格做成退化三角形） | 运行时 `SetVisibility` 每帧都要重新压一次（服装系统会复活它们），而资产层是永久的 |
| 魂的身体组件（重定向源） | **运行时隐藏**：`SetVisibility(false,false)` + `SetHiddenInGame` + `SetCastShadow(false)` + `bCastHiddenShadow=False` | 它是唯一的姿势来源，**不能**在资产层清掉，只能"隐藏但继续计算" |
| 过场副本的部件 | **运行时隐藏**（`state.copy_list`，逐帧重新压） | 副本是游戏新 spawn 的 actor，资产层替换管不到它们的组合；且它们**必须保持动画**给重定向用 |
| 魂的衣服本体（Chaos 布料 / Groom） | **运行时隐藏**（`state.cloth_list`） | 它们不是骨骼网格组件，资产层清不掉；也不能靠骨骼网格的开关带走 |

### 13.2 隐藏之后动画为什么还在：两个必要条件

1. **`VisibilityBasedAnimTickOption = AlwaysTickPoseAndRefreshBones`** ＋
   `bEnableUpdateRateOptimizations = False`（`force_anim_refresh`）。
   隐藏的组件不再被渲染，引擎默认会降频甚至停止刷新骨骼 → retarget 复制到旧姿态 → 停在 A-pose。
   这两项必须用 `ImportText` 写，**不能**直接写 Lua 值（UE4SS 会按 4 字节写 1 字节枚举，破坏相邻字段，§6.13）。
2. **leader pose 必须清掉**（`drive_carrier`，每 scan）。
   游戏在交互动画/过场后会重新执行 `SetLeaderPoseComponent`，让我们的载体变成"跟随者"，而跟随者
   从不评估自己的动画 → 立刻变参考姿势。所以每 0.5 s 检查一次并清除，而不是等出事再修。

### 13.3 过场副本：找到它们的三条路径（按代价排序）

| 路径 | 触发 | 代价 | 用途 |
| --- | --- | --- | --- |
| 布料/Groom 通知 → 读 `owner` | 副本自带布料组件被创建 | 几次反射调用 | **主路径**：识别出副本 actor，并把它的布料本身隐藏掉 |
| `children_of(actor_root_of(garment))` | 同上 | 局部遍历 | 尝试直接拿该 actor 的其它部件。实测**返回 0**（副本部件不在布料组件的子树里），所以只作为快路径 |
| `collect_copy_components()` 全关卡重建 | 快路径失败时，每个副本 actor **一次**（`copy_scanned[actor]` 去重） | 2 趟全关卡（约 80–200 ms） | 兜底；也用于换图/首次接管 |

要点：**去重键是副本 actor 名**，不是 tick。一个副本会报十几次布料组件，如果按 tick 节流就会反复重建，
表现为「每隔几秒卡一小下」；按 actor 去重就只付一次。

### 13.4 隐藏的正确性细节（都是踩过的坑）

- **绝不隐藏 `Hun_Head_New` 上的载体**：那是可琳思娜自己。`apply_copy_hiding` 里 `entry.mesh ~= carrier_mesh_name`
  是硬保护，`remember_hidden` 里还有一道 `key == carrier_name` 的拒绝。
- **缓存只存名字，用前重新解析**（`resolve_component`），并且**再比对 `owner`**：引擎会复用对象名，
  名字相同不代表还是那个对象（§6.22）。
- **死引用就地摘除**，不要置 `copy_dirty` 触发重扫 —— 一次重扫是几趟全关卡，而摘除是 O(1)。
- **只碰英雄自己的组件**：早期版本把所有骨骼网格踢出 base pass，导致 NPC 与铃铛变黑/丢材质（§6.24）。
  现在所有遍历都先做 `owner` 判定。
- **不要给魂自己的身体 `bPropagateToChildren`**：我们的载体挂在它下面，传播会把载体一起隐藏。
- **`SetVisibility` 之外还要 `SetRenderInMainPass(false)` + `SetCastShadow(false)`**：
  退化三角形虽然不可见，但阴影 pass 会因此出现闪烁黑斑（§6.24）。

### 13.5 动画正确性的自检（不用进游戏就能看）

| 检查 | 期望 |
| --- | --- |
| dev 日志 `carrier: leader pose cleared (nil)` | 每次都出现 |
| dev 日志 `source: always-relevant` | 出现一次（`force_anim_refresh` 成功） |
| dev 日志 `set_property: VisibilityBasedAnimTickOption = AlwaysTickPoseAndRefreshBones` | 出现，且**不能**有 `set_property FAILED` |
| dev 日志 `copy: made <comp> evaluate the retarget` | 每个副本一次 |
| dev 日志 `copy part: N component(s) … , M carrier(s)` | `N > 0`、`M ≥ 1`；长期 `N = 0` 说明快路径与重建都没生效 |
| `watch_pose` 的 `pose_window` 统计 | `stuck` 计数不应持续增长 |


## 14. 武器挂点：御剑与双手武器的实测结论

### 14.1 御剑（痴者残剑 / 痴者醉剑）：**保留游戏挂点**

- 痴者残剑：actor `BP_Weapon_Hun_ChiZheCanJian_C`，网格 `Hun_CanJian`，游戏挂点是
  **`weapon_r_child`**（一个可被动画驱动的骨骼，不是普通手部 socket）。
- 实测：把它吸附到 `Bip001-R-Hand` 后，整场它的 root 一直离手 15–43cm，**再也不会飞出去**。
- 只做握把修正也不行：游戏**每帧重写**它的相对变换（飞行动画就是这样做的），
  我们写的位置下一帧就被覆盖 → 手上位置照样偏。
- 因此：**挂点是 `*_child` 的武器完全不碰**，交给游戏。代价是它在手上时比理想位置偏上 3~4cm
  （它挂在 Hun 更大一号的手上）。这是**刻意取舍**：飞行是玩法，偏移是外观。
- 实现：`anchor_held_weapons()` 里 `driver_mount` 分支（socket 名含 `_child`）。
- 注意：我们的骨架是 `Bip001-*`，**没有** `weapon_r_child` 这根骨，不能把武器改挂到自己的同名骨上。

### 14.2 双手武器（斩马刀）：**未修，已查明原因**

- 武器网格上**没有**第二握点 socket。`Hun_WangMingZhanMaDao` 的全部 socket：
  `TrailStart, BladeBloodStart, Sound_Weapon, BlueEyeSocket, HoldDeflect, Deflect_Middle,
  RootNode, WangMingZhanMaDao_Root, WangMingZhanMaDao`。
- 双手握是 Hun 自己的 ABP 里用**左手 IK** 实现的，不是靠挂点。
- 实测（手到武器长轴的侧向距离）：

  | 采样 | 右手 lateral | 左手 lateral | 左手 along |
  | --- | --- | --- | --- |
  | Hun 原姿势（双手握） | 15.3cm | **8.2cm** | −66.3cm |
  | 搬到可琳思娜手上后 | 2.7cm | **6.5~19.8cm** | −54.4cm |

  （对照：单手刀 `Hun_MaleThug_Elite_Blade` 的 Hun 左手 lateral 为 47cm，所以这个判据能区分单手/双手姿势。）
- 试过两条路，都**已回退**：
  1. 绕握把把刀杆轴转到穿过左手 → 因为刀杆轴原方向与「握把→左手」相反，最小角度解之前那次直接**把武器转反了**；
  2. 用「手骨方向 × 握距」做确定性握把放置 → 反向导致**单手剑位置错乱、御剑只留在手上**。
- 后续若要修，正确的方向是「只在判定为双手姿势时、且只对右手挂点的武器，做一次最小旋转」，
  并且**必须在最小角度解上做符号判定**（比较与当前朝向的点积），回退验证要覆盖单手剑与御剑。

### 14.3 通用坑

- `GetAllSocketNames()` 返回 `TArray<FName>`，元素是 `RemoteUnrealParam`，
  必须 `raw:get():ToString()`；直接 `tostring(raw)` 得到的是 `RemoteUnrealParam: 0x…` 或
  `FNameUserdata: 0x…`。
- 判定「现在是不是拿在手里」不能只看距离：御剑的失败案例里，武器一直在离手 15–43cm 的范围内。
- 武器的 pivot 通常就是手感锚点，但痴者残剑这种**相对变换被游戏逐帧改写**的武器，
  用「世界空间偏移」做的任何修正都会被覆盖。

## 15. 本轮新增常见问题

| 现象 | 原因 / 处理 |
| --- | --- |
| 改了 `kawaii_config.json` 没变化 | 只改 JSON 不会生效，要重跑 `build_retarget_assets.py` 再 cook（`tools\build_all.ps1`） |
| 裙子被顶成气球、走路像有隐形圆环 | 球半径或 `settings.radius` 给太大；先降半径，再考虑加球 |
| 移动时裙子/头发并成一片又窄又薄的片 | `stiffness` 太低导致形状维持不住；0.30 是本项目取到的平衡点 |
| 静止就穿模、越站越陷 | `stiffness` 偏高把布料从碰撞结果里拉回；降刚度或加 `settings.radius` 余量 |
| 裙子抽搐 | ① 物理没被完全移除（先用 `F6`/`enabled:false` 二分）② damping 太低 ③ 左右大腿球在中心线重叠 |
| 头发穿脸/穿胸 | 头发 profile 没有碰撞球；加 `head_low/mid/top + neck + chest` |
| 御剑不飞了 | 有人把它吸附到手骨上了；见 §14.1，`*_child` 挂点必须留给游戏 |
| 过场里原主角衣服又出现 | 检查 `cloth:` 日志：Chaos 布料/Groom 收不到生成通知，必须靠 `collect_hero_garments` 的两类扫描 |
| 过场后 A-pose | 游戏重新 `SetLeaderPoseComponent`；`drive_carrier` 每 0.5s 兜一次，`watch_pose` 负责检测 |
| Lua 改完没生效 | UE4SS 只在**启动时**加载脚本；装错 profile（`install_lua.ps1 -Profile dev/release`）也不会生效 |
| release 版日志是空的 | 设计如此：release 只在出问题时写日志（`log_level = 1`） |
