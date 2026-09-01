# 机器狗项目 · KICKOFF 提示词

> 给下一轮新对话使用。把这段提示词贴到新对话开头,让 AI 从已整理好的工作区开始。

---

## 提示词正文

```
你刚接手一个新项目:桌面四足机器狗(纯技术开源项目,大二学生作品)。

【项目背景】
- love-bot 三战(2026-08-21 终止)已结束,详细经验见 `../love-bot项目/love-bot-body/三战总结.md` 和 `../love-bot项目/love-bot-body/robot-pcb-v2/STOP.md`
- 机器狗是新项目,完全独立的工作区,在 `c:/Users/17402/Desktop/机器狗/`
- 这是 v3 PCB 阶段(love-bot 的 v1 烧芯片/v2 未投板都是前车之鉴)
- 已开 GitHub 仓库:`https://github.com/xiaolongsya/pi-stm32-robot-dog.git`

【工作区位置】
- 根目录: `c:/Users/17402/Desktop/机器狗/`
- 必读规则: `c:/Users/17402/Desktop/机器狗/CLAUDE.md`
- 项目说明: `c:/Users/17402/Desktop/机器狗/README.md`
- 三战总结: `../love-bot项目/love-bot-body/三战总结.md`
- v2 教训: `../love-bot项目/love-bot-body/robot-pcb-v2/STOP.md`
- 当前网表: `c:/Users/17402/Desktop/机器狗/网表/Netlist_控制板_2026-09-01.tel`
- 数据手册: `c:/Users/17402/Desktop/机器狗/数据手册/`

【第一步目标】
继续 PCB 阶段的准备工作——原理图已经接近完成,接下来:
- 跑 ERC 检查网表(用户已经在原理图编辑器跑过)
- 检查 STM32G431KBT6 数据手册核对每个引脚
- 准备 ASCII 草图给 PCB Layout

【v3 已确定的设计决策(2026-09-01)】
1. 4 层板(双层板 EMC 失控,love-bot 教训)
2. 双 MCU 架构:香橙派 Zero3(主) + STM32G431KBT6(LQFP-32,7×7,0.8mm pitch)
3. 8 路舵机 MG90S,STM32 直驱(无 PCA9685)
4. 模块化接口:XH2.54 连接器,板边接口便于维修
5. 板尺寸 80×80 mm(从机械模型反推,JLC 4 层免费券内)
6. 电源:2S 7.4V 6800mAh 锂电池(蓝火新能源)+ 板载双 LM2596(5V/3A ×2)+ AMS1117(3.3V)
7. 摄像头:**USB 夹子成品**(1080p UVC 免驱),夹在狗头部前置,不走 PCB
8. 麦克风:**USB 声卡**(不走 I2S,Pi 无 26-pin I2S)
9. OLED:**SSD1306 0.96 寸 I2C 4 脚**(显示表情/状态)
10. 视觉跟踪:Pi 跑 MediaPipe Pose(本地,不依赖电脑)
11. 不做跳跃、不做力传感器、不做充电电路、不做 ORing
12. 不画原理图禁止画 PCB(love-bot v1 死法)

【关键 IO 接口表(v3 PCB 板载预留)】
- 8 路舵机:H5/H6 12pin 排针 ×2(每排针 4 路,信号/5V/GND 错位排列)
- 1 路 I2C:MPU6050 + OLED 共用(4.7kΩ 上拉,PB6 SDA + PA15 SCL)
- 1 路 USB-C:仅 PWR2 LED 指示(不接任何电源母线)
- 1 路电池 XT30:CN1
- 1 路 Pi 供电:CN2(XH2.54 2P)→ 5V_LOGIC → Pi
- 1 路 Pi UART:J1.7(J1 排针,4 pin 排针 TX/RX/3V3/GND)
- 1 路 SWD 调试:J1 排针(SWDIO/SWCLK/GND/3V3)
- 1 路 LED1 + KEY1:J2 排针(STM32 PA0 + PA1)

【给你的规则】
1. 用中文和我交谈
2. 必须先读完 `机器狗/CLAUDE.md` 和 `README.md` 再开始动手
3. 拍板事项必须停下来等我,不要继续推进或说"下一步做什么"
4. 诚实回答:不知道就说不知道,不准猜电路参数
5. 下载依赖优先清华源/阿里源,不行才用官方源
6. 涉及 PCB 板布局变更,先画 ASCII 草图给我确认再画
7. 必须先画原理图,不能直接画 PCB(love-bot v1 死法)
8. 每颗 IC 的外围对照数据手册逐引脚核对(电源/地/自举/补偿/反馈/使能/续流)
9. 修复 bug 尽量每修一个提交一次,方便回溯
10. 整体规划前置:走线 + 芯片选型 + 散热 + EMC 在原理图阶段一起看
11. 我在改原理图(不是在改网表),指令要用原理图思维("把 X 加进 Y 网络"),不是网表术语

【重要:用户偏好】
- 网格命名风格(3V3, GND, SDA, SCL),不用标签
- 标签容易漏接,网格强制连接
- 调试排针 J1/J2 闲置脚标 NC,不冗余布线
- 不喜欢功能堆砌(ORing 等"锦上添花"已被撤)

【参考文件清单(按需读取,不要全读)】
- `机器狗/CLAUDE.md` — AI 规则
- `机器狗/README.md` — 项目说明 + 架构 + 决策表
- `机器狗/网表/Netlist_控制板_2026-09-01.tel` — v3 当前网表
- `机器狗/数据手册/` — 各 IC 数据手册(按需查)
- `love-bot-body/三战总结.md` — 三战经验沉淀
- `love-bot-body/robot-pcb-v2/STOP.md` — v2 PCB 终止说明 + 教训清单

开始之前,先告诉我:
1. 你已经读完了哪些文件
2. 你对当前网表的理解
3. 第一步具体打算怎么动(PCB 阶段的哪一部分)
4. 有什么需要我先拍板的
```

---

## 使用方法

1. 复制「提示词正文」整段(从 `你刚接手一个新项目` 到 `有什么需要我先拍板的`)
2. 粘贴到新对话开头
3. AI 回复"已经读完哪些文件 + 第一步打算"后,再继续对话
4. 后续 README / KICKOFF / CLAUDE 改动后记得 `git commit + push` 到仓库