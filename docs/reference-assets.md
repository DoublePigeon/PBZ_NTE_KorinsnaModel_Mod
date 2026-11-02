# 游戏资产参考（从本作 dump 得到）

游戏：Phantom Blade Zero，UE 5.7.4，`/Game` 挂载在 `ProjectPBZ/Content`。
数据来源：UE4SS 3.0.1 Beta 反射 dump（`extract/dump/`）。

## 主角蓝图与组件

| 项目 | 路径 |
| --- | --- |
| 主角蓝图 | `/Game/.../BP_Renewal_Hun_C`（运行时类 `BP_Renewal_Hun_C`） |
| 身体组件 | `CharacterMesh0`（`SkeletalMeshComponent`） |
| 身体网格 | `/HuaShira/Characters/Hero/Hero_Hun/SkinParts/Hun_Body_Simple` |
| 骨架 | `/HuaShira/Characters/Hero/Hero_Hun/Hun_Skin_Skeleton`（274 骨，含 `VB *` 虚拟骨） |
| 物理资产 | `/HuaShira/Characters/Hero/Hero_Hun/PA_Hun` |

## 主角的其他部件（本 Mod 已用空白网格覆盖）

`/HuaShira/Characters/Hero/Hero_Hun/SkinParts/Hun_Head_New`（890 骨）、
`Hun_BrowLashCard`、`Hun_Scarf`、`Hun_Hair_Band`、`Hun_Hair`、`Hun_Hat`、
`/HuaShira/Characters/Hero/Hero_Hun/Hats/Hun_Hat_00`

## 身体网格的 8 个材质槽

槽位由网格自身的材质数组决定（蓝图不会强行改写槽位数量），
游戏会在运行时为每个槽创建 `MID_<材质名>` 动态实例。

| 槽 | 游戏材质实例 | 父材质链 | 本 Mod 覆盖的贴图 |
| --- | --- | --- | --- |
| 0 | `Hun_New_V2b/Material/MI_ZeroHun_Cloth_01_b` | MAI_Equipment_Mask → MAI_Equipment → MAI_Character → MA_Character | `T_ZeroHun_Cloth_01_BC`←01_d、`_ARM`、`_N` |
| 1 | `.../MI_ZeroHun_Cloth_02_b` | MAI_Cloth → MAI_Character | `T_ZeroHun_Cloth_02_BC`←02_d、`_ARM`、`_N` |
| 2 | `.../MI_ZeroHun_Cloth_03_b` | MAI_Equipment → MAI_Character | `T_ZeroHun_Cloth_03_BC`←hair_01_d、`_ARM`、`_N` |
| 3 | `.../MI_ZeroHun_Cloth_04_b` | MAI_Cloth → MAI_Character | `T_ZeroHun_Cloth_04_BC`←hair_02_d、`_ARM`、`_N` |
| 4 | `.../MI_ZeroHun_Cloth_05_b` | MAI_Cloth → MAI_Character | `T_ZeroHun_Cloth_05_BC`←face_d、`_ARM`、`_N` |
| 5 | `.../MI_ZeroHun_Cap_01_b` | MAI_Equipment_Mask → … | `T_ZeroHun_Cap_V02_BC`←face_d、`_N` |
| 6 | `Hun_Status/MI_ZeroHun_Head_Injured30` | MAI_Skin → MAI_Character | `HeadMerged/T_ZeroHun_Head_D`←face_d、`HeadMerged/T_ZeroHun_Head_N` |
| 7 | `Hun_New_V2/Material/MI_ZeroHun_Eye_01` | MA_EyeRefractive_02 | `T_ZeroHun_Eye_D`←eyes_d（该包在 `/Game/Test/...` 下，当前打包脚本会裁掉，未生效） |

贴图根目录：`/Game/PBZContent/Characters/Hero/Hun_New_V2b/Textures`

## 材质参数（重要）

- 服装/装备类材质实例覆盖的参数名：**`Albedo`**、**`Normal`**、**`Mix`**（ARM，A=遮罩）。
- 皮肤类（MAI_Skin）覆盖的参数名：`BaseColor`、`Normal`、`SCMT_Map`、`SkinNormal_MICRO`、`Dirt_MaskMap`。
- 母材质默认值是占位图：`GreyPlaceholder_VT` / `GreyPlaceholder` / `Placeholder_Normal_VT` / `Placeholder_Mask_VT`。
- **`Albedo` 以虚拟纹理方式采样**：覆盖贴图必须开启 `Virtual Texture Streaming`，否则采样到 `GreyPlaceholder`（灰白）。
- `Mix` 的 Alpha 参与遮罩，UV 不匹配时会导致整块几何被裁掉（模型“只剩头发”就是这个原因）。

## 包格式要点

- 游戏是 IoStore + Oodle + AES，容器 `mount_point: ../../../ProjectPBZ/`。
- 容器名必须与 pak 同名：`<Name>.pak` + `<Name>.utoc` + `<Name>.ucas`，放在 `ProjectPBZ/Content/Paks/~mods/`。
- 同名同路径的包以 `~mods` 内的容器为准（本 Mod 正是靠这一点覆盖网格与贴图）。
