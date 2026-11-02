# 绑骨说明（如何手工精修）

本仓库的自动重定向绑骨脚本能出可用的结果，但 Korinsna 的原始骨架（368 骨，`Bip001-*` 命名）
与游戏骨架（274 骨，UE 命名 + `VB` 虚拟骨）并不一一对应，细节（手指、衣摆、装饰）如果按自动权重
出现穿插或塌陷，按下面的流程手工修。

## 1. 自动流程做了什么

`blender/scripts/match_game_skeleton.py`（当前使用的入口）
- 打开手工绑好骨的 `blender/out/Korinsna_Rigged_source.blend`（基于游戏 `Hun_Skin.pskx` 的骨架）；
- 把根关节 `root` 删掉、子骨骼提升为顶层，并把 armature 物体改名成 `Root`
  ── 因为 Blender 一定会把 armature 物体导出成一个 FBX 节点，正好用它承担游戏第 0 根骨；
- 修正大小写不一致的骨骼名：`head`→`Head`、`weapon_r`→`WEAPON_R`、`interaction`→`Interaction`；
- 网格、权重、骨骼变换**完全不改**（外观与手工版本一致），然后导出 FBX。

`blender/scripts/build_target_skeleton.py`（早期的骨架重建，保留作参考）
- 读取 `extract/dump/refbones.txt` 重建 274 骨骨架，并对骨骼旋转做 Blender↔UE 的 handedness 镜像修正。

`blender/scripts/rig_korinsna.py`（早期从零绑骨，保留作参考）
- 名字映射、按身高缩放、烘焙变换、权重重定向、限制 8 影响，导出 FBX。

`blender/scripts/render_slot_colors.py`
- 给每个材质槽刷一个纯色并渲染正/背面，用来确认「哪个槽是身体的哪个部位」。
  渲染结果不随仓库分发（截图已在 `.gitignore` 中屏蔽），需要时本地跑一次脚本即可。

`tools/make_neutral_textures.py`
- 生成 `T_Korinsna_ARM`（AO=1/Roughness=1/Metallic=0）、`T_Korinsna_N`（平法线）、
  `T_Korinsna_White`、`T_Korinsna_Black`，统一 **256×256** 以便作为虚拟纹理使用。

`blender/scripts/make_blank_part.py`
- 生成零面积三角形网格 `BlankPart.fbx`，用于覆盖原有部件。

## 2. 手工精修步骤

1. 用 Blender 打开 `blender/out/Korinsna_Rigged.blend`（已完成映射的工程文件）。
2. 修正权重：
   - 选中网格 → `Weight Paint` 模式；
   - 重点区域：手指（`thumb_* / index_* / middle_* / ring_* / pinky_*`）、
     裙摆（`bns_skirt*` 链）、头发（`Head` + `hair_*`，如果目标骨架有对应骨）。
3. 需要在游戏里对齐姿势时，先用目标骨架的静止姿势（Rest Pose）校形，不要用 Pose 模式调。
4. 导出：
   ```powershell
   # 保持与自动流程一致的导出设置（单位 cm、缩放 1.0、烘焙变换、只导 UV0）
   & I:\Blender\blender.exe -b blender\out\Korinsna_Rigged.blend --python blender\scripts\export_only.py
   ```
   （`export_only.py` 就是 `rig_korinsna.py` 末尾的导出段落，可单独拆出来用。）
5. 重新导入 → 打包：
   ```powershell
   & tools\build_all.ps1
   ```

## 3. 常见问题

| 现象 | 原因 / 处理 |
| --- | --- |
| 模型在游戏里巨大或极小 | FBX 单位不对。必须 `scene.unit_settings.scale_length = 0.01` |
| 完全没动画（保持默认姿势） | 网格第 0 根骨不是 `Root`，或骨骼名大小写不一致。见 `match_game_skeleton.py` |
| 角色朝向偏 90° / 陷进地面 | 网格和骨架不在同一空间；不要移动 armature 物体（手工版本的位置是对的） |
| **脸很黑 / 衣服发灰发脏 / 有奇怪的网格纹** | 覆盖的贴图没开 **Virtual Texture Streaming**。主角材质所有贴图通道都是 VT 采样，普通贴图会静默退回占位图。同时确认大小（≥128，本项目用 256）与 sRGB/压缩设置正确 |
| 头发看起来像布 | 头发槽被指到了 `MAI_Cloth`（带布料织纹细节法线），改指 `MAI_Equipment` 系列 |
| 觉得「原主角的衣服还在」 | 先做验证：运行时隐藏 `CharacterMesh0`，若角色整体消失（只剩武器）说明画面上全是我们自己的网格；服装部件本身已全部空白化 |
| 换骨架后游戏 0xc0000005 崩溃 | 覆盖了 `Hun_Skin_Skeleton`。绝对不要打包自己的骨架 |
| 武器/个别顶点拉成长条 | 武器挂在游戏 socket 上且比例差异大，需要单独覆盖成空白网格 |

## 4. 材质槽与 UV 的对应

模型 8 个材质槽顺序来自 `npc_036.blend` 的材质槽顺序：

```
0 MI_NPC_036_01        1 MI_NPC_036_02
2 MI_NPC_036_hair_01   3 MI_NPC_036_hair_02
4 MI_NPC_036_face      5 MI_NPC_036_eyebrow
6 MI_NPC_036_eye       7 MI_NPC_036_gaoguang
```

所有贴图都映射在 **UV0**（0..1 范围）。若某个槽在游戏里颜色不对，
只需改 `ue/scripts/build_mod_assets.py` 的 `TEXTURES` 表（哪张贴图喂到哪个游戏贴图包）。
