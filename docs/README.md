# 影之刃零（Phantom Blade Zero）主角替换 Mod —— Korinsna

把主角「魂」的模型替换为可琳思娜(来自异环)。

> 效果截图不随仓库分发（含游戏画面与模型渲染，已在 `.gitignore` 中屏蔽）。
> 想看效果请本地运行游戏，或自行生成到 `docs/img/`。

## 这个 mod 是什么

- **不修改 Korinsna 的骨骼**：模型保留自己的 `Bip001` 骨架（369 骨），不做重新蒙皮。
- 动画在运行时由 **IK Retargeter + PostProcess AnimBlueprint** 从原主角的实时姿势重定向过来，
  **UE4SS** 脚本负责让它跑起来、并把原版外观收干净。
- 材质**完全复用游戏自己的材质实例**，只替换它们引用的贴图，因此光照、阴影、遮罩行为与原角色一致。
- 原版外观（身体、斗笠、围巾、长袍、长发、披风）在**资产层**清除，不依赖运行时隐藏。

> 早期版本走的是「把 Korinsna 重新蒙皮到游戏骨架」的路线，模型会被拉伸，已废弃。

## 当前状态

| 项目 | 状态 |
| --- | --- |
| 模型 / 朝向 / 站立高度 | ✅ |
| 全身动画（重定向） | ✅ |
| 骨折不拉伸、四肢形变 | ✅ |
| 手指 | ✅ 动态（逐关节重定向，A-pose 绑定姿态） |
| 裙摆 | ✅ 物理（KawaiiPhysics，球体碰撞，不限角） |
| 头发物理 | ✅ 物理（KawaiiPhysics，4 条链，限角 50°） |
| 材质 / 受光 / 阴影 | ✅ |
| 原版外观清除 | ✅ 全身（含长袍与长发），含过场副本与 Chaos 布料 |
| 手持武器跟随并握在手里 | ✅ 单手 / 双持；御剑（痴者残剑/醉剑）保留游戏挂点以保住飞行（见 §13.1） |
| 双手武器双手握持 | ⚠️ 一手握着、另一头不贴身（原因已查明，见 §13.2） |
| 腰后短刀与刀鞘 | ✅ 锚定在背部 |
| 运行时开销 | ✅ 事件驱动缓存：生成即分类，全关卡扫描只剩换图/英雄接管各一次（技术指导 §12） |

## 需求

- 游戏本体（UE 5.7）：*Phantom Blade Zero*
- [UE4SS](https://github.com/UE4SS-RE/RE-UE4SS)：运行时重定向与外观处理都依赖它

重新构建还需要 UE 5.7 与 Blender（`I:\Blender\blender.exe`）。

## 安装

**先关闭游戏。**

`Release\` 已经是整理好的分发包（`tools\make_release.ps1` 生成）：

```
Release\KorinsnaModel\       ->  <游戏目录>\ProjectPBZ\Content\Paks\~mods\
Release\KorinsnaRetarget\    ->  <游戏目录>\platform\steam\ue4ss\Mods\
```

1. 把 `Release\KorinsnaModel\` 里的三个文件复制到 `<游戏目录>\ProjectPBZ\Content\Paks\~mods\`
   （目录不存在就自己建）：

   - `ProjectPBZ-Korinsna-Windows_P.pak`
   - `ProjectPBZ-Korinsna-Windows_P.utoc`
   - `ProjectPBZ-Korinsna-Windows_P.ucas`

2. 把 `Release\KorinsnaRetarget\` 整个文件夹复制到
   `<游戏目录>\platform\steam\ue4ss\Mods\KorinsnaRetarget\`，
   并在 `platform\steam\ue4ss\Mods\mods.json` 里启用它。

   `tools\install_mod.ps1` 会自动完成上面两步（含 `mods.json`）。

   只想更新 Lua 半边（不需要重新 cook）时用 `tools\install_lua.ps1`：
   默认装 **release**（只在出问题时写日志，游玩用）；`-Profile dev` 装 **dev**（全量日志 + 普查，排障用）。
   两个版本行为一致，见 TECHNICAL-GUIDE §7.1。

3. 启动游戏，进入存档即可看到替换后的主角。

> 三个容器文件必须同名同目录，缺一不可。`.pak` 只有 339 字节，它是让引擎挂载同名 IoStore 容器的
> 占位文件，内容都在 `.utoc` / `.ucas` 里。

## 卸载

删除 `~mods` 下的那三个文件，并删除 `platform\steam\ue4ss\Mods\KorinsnaRetarget\`
（以及 `mods.json` 中对应条目），即完全恢复原版主角。

## 重新构建

```powershell
# 资产导入 -> 原生 5.7 cook -> IoStore 打包 -> 安装到 ~mods
& tools\build_all.ps1

# 只重新打包（资产与 cook 结果已存在）
& tools\build_all.ps1 -SkipAssets -SkipCook
```

产物：`dist/Korinsna/ProjectPBZ-Korinsna-Windows_P.{pak,utoc,ucas}`，脚本最后会复制到游戏的 `~mods`。
游戏正在运行时复制会因文件占用失败，请先关掉游戏。

## 仓库里有什么

本仓库只包含**代码与文档**（约 0.7 MB / 95 个文件）：

- ✅ `ue4ss/` 的 Lua 运行时 mod、`ue/scripts/` 与 `blender/scripts/` 的构建脚本、`tools/` 的管线脚本、
  `ue/ProjectPBZ` 的 `Source` / `Config` / `.uproject` / `.uplugin`、`docs/*.md`、以及体积小的研发 dump
- ❌ 角色模型与贴图、游戏原模型（`*.psk` / `*.pskx`）、参考模组（`REFERENCE/`）、第三方压缩包、
  游戏映射文件（`*.usmap`）、所有截图、`ue/ProjectPBZ/Content/`（脚本生成，含角色网格）、
  `dist/`、`blender/out/`、UE 的 `Intermediate` / `Saved` / `Binaries` / `DerivedDataCache`

理由是这些资产**没有二次分发权利**，或者**可以用脚本重建**。完整规则见 [.gitignore](../.gitignore)。

> 因此**克隆后无法直接构建**：需要自备角色模型与游戏本体资源，再按上面的步骤跑一遍脚本。

## 文档

- [TECHNICAL-GUIDE.md](TECHNICAL-GUIDE.md) —— **技术指导**：实现路径、每条做法背后的原因、
  踩过的坑与修法、运行期开关、调试方法、已知不足
- [rig-notes.md](rig-notes.md) —— 骨架与绑定相关记录
- [reference-assets.md](reference-assets.md) —— 参考资产与贴图来源

## 目录结构

```
blender/scripts/   APOSE 导出与骨架重建脚本
blender/out/       生成的 FBX / Blend
ue/ProjectPBZ/     用于导入 + 打包的 UE 5.7 工程（含 editor-only 模块）
ue/scripts/        资产导入、重定向资产构建、校验脚本
ue4ss/             KorinsnaRetarget 运行时 mod（Lua）
tools/             build_all.ps1 / stage_iostore.ps1 / install_mod.ps1 / luacheck.py 等
docs/              文档与截图
dist/Korinsna/     最终可安装的容器
extract/           构建日志与从游戏 dump 出来的研发资料
```

## 致谢

- 参考实现 **[PBZ 2B Mod](https://github.com/hcxmmx/PhantomBladeZero-2B-Mod)**：重定向资产的组织方式、`sync_reference_pose`、
  「不参与重定向的骨骼不会被搞坏」等思路均来自它
- 可琳思娜模型与姿势：Arcpav & 异环
