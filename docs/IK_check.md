1. 核心修复：修改位移重定向模式（Translation Retargeting）

这是导致肢体“像拱门一样弯曲”最常见的原因。如果原角色的手臂长，你的Mod角色手臂短，系统默认会强行把你的角色手臂拉长到原角色的位置，导致骨骼弯曲。

    操作方法：

        打开你的目标角色的骨骼文件（Skeleton）或者在 IK Retargeter 中操作。

        在 IK Retargeter 的 Chain Mapping（链映射） 面板中，选中出问题的骨骼链（比如手臂 LeftArm、大腿 LeftLeg）。

        查看右侧的细节面板（Details），找到 Translation Mode（位移模式）。

        将手臂、腿部、脊椎等所有肢体骨骼链的 Translation Mode 从 Animation（动画） 改为 Skeleton（骨骼） 甚至 None。

        注意：只有 Root（根骨骼） 和 Pelvis（骨盆/髋骨） 应该保持为 Globally Scaled 或 Animation，这样角色才能在空间中移动。其他所有关节都应该用 Skeleton 以保持你Mod角色自身的比例。

2. 关键修复：完美对齐初始姿势（Retarget Pose）

UE5的重定向极度依赖两个模型在重定向器中的初始姿势完全一致。如果原游戏角色是 T-Pose，而你的Mod角色是 A-Pose（或者手臂下垂的角度差了哪怕10度），播放动画时就会出现严重的翻折或拱形弯曲。

    操作方法：

        在 IK Retargeter 窗口中，确保源角色（Source）和目标角色（Target）并排显示。

        点击上方工具栏的 Edit Retarget Pose（编辑重定向姿势）。

        旋转你 Mod 角色的大腿、肩膀、手臂、手腕骨骼，让它的姿势尽可能 1:1 完美重合源角色的姿势。

        特别注意**肩膀（Clavicle）和大腿根部（Thigh/Pelvis连接处）**的角度，这两个地方差一点，末端（手脚）就会偏移很多，导致IK强行拉扯形成拱形。

3. 检查骨骼链（Bone Chains）是否包含多余骨骼

有时候肢体动作怪异，是因为在创建 IK Rig 时，链条里包含了不该包含的骨骼。

    排查 Twist Bones（扭转骨骼）：

        很多UE5游戏角色有辅助扭转的骨骼（如 upperarm_twist 或 thigh_twist）。

        如果你在创建手臂或腿部的 Chain（链）时，不小心把 Twist 骨骼包含在了起始骨骼和结束骨骼之间，动画就会产生“糖果纸式”的扭曲（看起来就像弯成了拱形）。

        解决：回到你的 IK Rig 中，确保手臂链仅仅是 UpperArm -> LowerArm -> Hand（大臂->小臂->手），跳过/排除所有 twist 骨骼。

4. 调整 IK 目标和极向量（Pole Vector）

如果手掌或脚掌的位置是对的，但是手肘或膝盖弯曲的方向反了（向后弯，或者向侧面弯），这是IK求解器不知道关节该往哪边弯导致的。

    操作方法：

        在 IK Retargeter 中，点击选中目标角色的手臂或腿部链（Chain）。

        在右侧细节面板找到 IK（反向动力学） 设置。

        找到 Blend to Source（混合到源） 或 FK/IK Blend 选项。如果你发现IK导致了严重变形，可以尝试把手和脚的 IK Blend 调低（比如从 1.0 降到 0.0），看看仅仅使用 FK（正向动力学）是否表现更好。

        如果必须用 IK（比如角色需要握枪、双手拿大剑），你需要在目标角色的 IK Rig 中为手肘和膝盖设置 Pole Vector（极向量），强行指定它们只能朝前（膝盖）或朝后（手肘）弯曲。

5. 调整 FK 旋转模式

在 IK Retargeter 中，选中弯曲怪异的链（如腿部），在细节面板找到 FK Settings（FK 设置）：

    尝试更改 Rotation Mode（旋转模式）。

    通常默认是 Interpolated（插值），你可以尝试改为 Absolute（绝对）。对于某些骨骼比例差异极大的情况，Absolute 能强制目标骨骼完全复制源骨骼在世界空间中的旋转角度，从而避免诡异的扭曲。

总结排查顺序：

    先查 Retarget Pose（初始姿势），没对齐T/A Pose绝对会扭曲。（解决80%的问题）

    再查 Translation Mode（位移模式），除了骨盆，全改成 Skeleton。（解决比例拉扯导致的面条手/拱形腿）

    检查 IK Rig 的骨骼链，千万别把扭转骨（Twist）当成主骨骼绑进去。

    如果上述都没问题但手肘/膝盖乱拐，去调 IK的混合权重 或添加 Pole Vector。

---

## 结论（逐项核对结果，2026-11）

| 项 | 结论 | 说明 |
| --- | --- | --- |
| 1 位移重定向模式 | **本来就满足** | 实测每条链 `TranslationMode=None`，只有 Root 是 `GloballyScaled`；Pelvis Motion 的 translation alpha / scale 都是 1.0。改成配置驱动后重测，画面无变化、无回退。 |
| 2 Retarget Pose 对齐 | **不需要手工摆** | `auto_align_bones` 已经把目标重定向姿态对齐到源；手工再摆只会引入误差（作者也说过两边是对应的）。 |
| 3 链里的多余骨（扭转骨） | **是「拱形」的真凶，已修** | 目标手臂 7 骨 / 腿 8 骨（源 3 / 4），`Interpolated` 把肘/膝的弯曲按骨序号分摊给中间的 Twist 骨 → 整条肢体被掰弯。UE 的链无法跳过路径上的骨、两条链也不能共用骨（共用会让 `GetChainNameForBone` 返回合成名并断言崩溃），最终做法是**相邻不重叠地切段 + 每段映射到单骨源链**，扭转骨刚性跟随所属关节。见 TECHNICAL-GUIDE §5.6 / §6.23。 |
| 4 IK 混合 / 极向量 | **不适用** | `Retarget IK Goals` 与 `Run IK Rig` 两个 op 是关闭的（目标 IK Rig 没有 goal/solver，打开会崩游戏），所以链路里根本没有 IK，只做 FK 旋转复制 + 骨盆/根位移。 |
| 5 FK 旋转模式 | **保持 `Interpolated`** | 切段之后每段的源链都是单骨，插值退化为「刚性复制该关节」，比换 `OneToOne` / `MatchChain` 更可预测；`Interpolated` 保留给 Spine/Neck 这种多骨链（脊柱的渐变弯曲是想要的）。 |

已经用同一套方法把**手指**也接上了（逐关节切段 + 单骨源链），绑定姿态从握拳版换成 `npc_036_APOSE.blend`。见 TECHNICAL-GUIDE §5.4。
