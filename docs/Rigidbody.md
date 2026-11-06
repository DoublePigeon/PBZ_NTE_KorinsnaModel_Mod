在UE5中，使用 RigidBody（刚体）节点 + Component Space（组件空间） 是一种非常优雅且原生的解决方案。它能完美剥离原游戏世界物理（如主角奔跑的巨大惯性、世界风力），仅仅利用骨骼动画本身的运动来驱动裙子，并通过物理碰撞防止穿模。

以下是保姆级的详细实现步骤，分为 “物理资产设置”、“动画蓝图设置” 和 “模型绑定” 三个阶段。
第一阶段：调教专属物理资产 (Physics Asset)

这一步是核心。刚体节点完全依赖物理资产（PhAT）来进行碰撞和解算。我们需要明确分工：腿是“推土机”（只撞人不挨撞），裙子是“被推的土”（受重力和碰撞影响）。

    打开或创建物理资产：

        找到你的女性骨骼网格体（Skeletal Mesh），右键 -> Create -> Physics Asset -> Create and Assign（如果已经有了就双击打开）。

    设置“腿部”为运动学 (Kinematic)：

        在物理资产的骨架树（Skeleton Tree）中，选中 骨盆（Pelvis）、大腿（Thigh_L/R）、小腿（Calf_L/R） 的骨骼。

        右键 -> Add/Replace Bodies（如果还没有胶囊体的话）。

        在右侧的细节面板（Details）中，找到 Physics Type（物理类型），将其从 Default 或 Simulated 改为 Kinematic（运动学）。

        关键调整： 在视口中，把大腿和小腿的胶囊体稍微放大/加粗一圈。因为原动作是男性的，跨步可能很大，稍微加粗的胶囊体能提前把裙子推开，提供一个“防穿模缓冲层”。

    设置“裙子”为模拟 (Simulated)：

        选中裙子的所有骨骼。

        右键 -> Add/Replace Bodies 生成碰撞体（通常用胶囊体Capsule或球体Sphere，尽量调小一点，贴合裙摆）。

        在细节面板中，将它们的 Physics Type（物理类型） 设置为 Simulated（模拟）。

    调教裙子的约束 (Constraints) —— 防止裙子乱翻：

        在骨架树中，选中裙子骨骼之间的 Constraints（约束，图标是像两根骨头连在一起的小图标）。

        在细节面板找到 Angular Limits（角度限制）：

            将 Swing 1 Motion, Swing 2 Motion, Twist Motion 全部设置为 Limited（限制）。

            将角度（Limit Angle）设置在 15度 到 45度 之间（具体看你希望裙子有多飘）。

            这一步是为了防止裙摆在受到腿部撞击时，直接翻转180度掀到头顶下不来。

    关闭裙子自身的乱撞 (Disable Collision)：

        裙子相邻骨骼的胶囊体通常会重叠，这会导致刚开始模拟时裙子直接“爆炸”抖动。

        选中所有裙子骨骼，右键 -> Collision -> Disable Collision Between Selected（禁用选中项之间的碰撞）。让裙子只和腿（Kinematic）碰撞，不和自己互相挤压。

第二阶段：编写后处理动画蓝图 (Post Process AnimBP)

后处理动画蓝图会在 IK Retargeter 结算完男转女的动作之后，最后附加物理效果。

    创建后处理蓝图：

        在内容浏览器空白处右键 -> Animation -> Animation Blueprint。

        选择你的女性模型的 Skeleton（骨架）。命名为 ABP_Female_PostProcess。

    添加 RigidBody 节点：

        双击打开该蓝图。进入 AnimGraph（动画图表）。

        你会看到一个 Input Pose 和一个 Output Pose。

        从 Input Pose 拖出线，搜索并添加 RigidBody（刚体） 节点。

        将 RigidBody 的输出连接到 Output Pose。

        (注：如果连线时自动生成了 Local to Component 和 Component to Local 节点，保留它们即可，这是正常的空间转换。)

    设置 RigidBody 节点的“魔法参数”：

        点击选中 RigidBody 节点，看右侧的细节面板（Details）。

        Override Physics Asset（覆盖物理资产）： 勾选它，并在下拉菜单中选择你在第一阶段调教好的那个物理资产。

        Simulation Space（模拟空间）： 这是最重要的！默认是 World Space，必须改成 Component Space（组件空间）。

            原理解释：Component Space 意味着裙子的物理完全忽略角色在游戏世界中的位移（不管主角跑多快、瞬移、下落），它只计算“腿部骨骼相对于模型中心点的运动”，从而彻底解决了跑动惯性导致裙子往后拉扯变形的问题。

        Gravity Override（重力覆盖）： 建议勾选，并确保 Z 轴是 -980（维持向下的重力，让裙子垂合）。

        External Forces（外部力）：

            确保没有勾选任何接收世界风力（Wind）的选项。

            Enable World Geometry（启用世界几何体）： 取消勾选。这样裙子就不会和游戏环境（比如墙壁、楼梯、水面）产生交互碰撞，彻底独立。

第三阶段：将后处理蓝图绑定到模型

代码写好了，需要告诉模型去使用它。

    双击打开你的女性角色的 Skeletal Mesh（骨骼网格体） 资产。

    在左侧或右侧找到 Asset Details（资产细节） 面板。

    搜索框中输入 Post，找到 Post Process Anim Blueprint（后处理动画蓝图） 选项。

    在下拉菜单中，选择你刚才制作的 ABP_Female_PostProcess。

    保存所有资产。

调试与避坑指南 (Troubleshooting)

现在把模型放进游戏（或者在预览窗口播放一个跑步动画），裙子应该已经有基于组件空间的物理了。如果效果不理想，请对照以下排查：

    问题1：裙子一直在疯狂高频抖动/鬼畜。

        原因： 默认姿势（A-Pose或T-Pose）下，裙子的胶囊体和腿的胶囊体已经重叠（穿模）了。物理引擎在一瞬间试图把它们弹开，导致死循环。

        解决： 回到物理资产（PhAT），把大腿胶囊体稍微缩小一点，或者把裙子骨骼的胶囊体调小/往外挪一点。确保默认站立时，它们互不干涉。

    问题2：男性跨步太猛，裙子依然会穿出腿部。

        原因： 腿部运动速度太快，穿透了裙子的碰撞计算。

        解决：

            在物理资产中，把大腿（Thigh）和骨盆（Pelvis）的胶囊体再加粗一点。

            检查 RigidBody 节点的细节面板，尝试增加 Position Solver Iterations 和 Velocity Solver Iterations（迭代次数，比如改成8或16），提高物理计算精度。

    问题3：裙子感觉太轻、像纸片，或者太重、像铁皮。

        解决： 回到物理资产，选中裙子的所有骨骼。在细节面板找到 Mass（质量），可以调高一点（比如增加到 50或100）。同时可以适当增加 Linear Damping（线性阻尼，控制平移空气阻力）和 Angular Damping（角阻尼，控制旋转阻力），比如分别设为 1.0 和 2.0，能让裙子看起来更像厚实的布料。