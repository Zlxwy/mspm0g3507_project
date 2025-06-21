* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)
* [问题](#问题)

## 简介
用编码器控制 PWM 输出占空比，来调节 LED 的亮度。（其实这个项目是用来测试电机驱动模块的）

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin 芯片
- 正交编码器
- 0.96 寸 128*64 像素 OLED 显示屏
- J-Link OB 调试器

## 配置
### Switch Board or Device
- 在 syscfg 右下角点击 **SWITCH** ，选择封装为 **LQFP-48** ，点击 **Confirm** 确认。
- 左侧栏 **Project Configuration** 会有一个报错、一个警告，在 **Select Device** 重新选择一下芯片型号，忽略掉警告就行。
### GPIO (3 Added)
* Name: <u>GPIO_OLED</u>
  - Group Pins (2 added)
    * Name: <u>SCL</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Set</u>
    - Digital IOMUX Features
      * Internal Resistor: <u>Pull-Up Resistor</u>
    * Assigned Port: <u>PORTB</u>
    * Assigned Pin: <u>6</u>
    * 
    * Name: <u>SDA</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Set</u>
    - Digital IOMUX Features
      * Internal Resistor: <u>Pull-Up Resistor</u>
    * Assigned Port: <u>PORTB</u>
    * Assigned Pin: <u>7</u>
* Name: <u>GPIO_ENCODER</u>
  - Group Pins (2 added)
    * Name: <u>PHASE_A</u>
    * Direction: <u>Input</u>
    - Digital IOMUX Features
      * Internal Resistor: <u>Pull-Up Resistor</u>
    * Assigned Port: <u>PORTA</u>
    * Assigned Pin: <u>26</u>
    - Interrupts/Events
      * Enable Interrupts: <u>select</u>
      * Interrupt Priority: <u>Default</u>
      * Trigger Polarity: <u>Trigger on Both Edges</u>
    *
    * Name: <u>PHASE_B</u>
    * Direction: <u>Input</u>
    - Digital IOMUX Features
      * Internal Resistor: <u>Pull-Up Resistor</u>
    * Assigned Port: <u>PORTA</u>
    * Assigned Pin: <u>27</u>
    - Interrupts/Events
      * Enable Interrupts: <u>select</u>
      * Interrupt Priority: <u>Default</u>
      * Trigger Polarity: <u>Trigger on Both Edges</u>
* Name: <u>GPIO_MOTOR</u>
  - Group Pins (4 added)
    * Name: <u>LIN1</u>
    * Direction: <u>Output</u>
    * Assigned Port: <u>PORTB (随便设置的)</u>
    * Assigned Pin: <u>18 (随便设置的)</u>
    *
    * Name: <u>LIN2</u>
    * Direction: <u>Output</u>
    * Assigned Port: <u>PORTB (随便设置的)</u>
    * Assigned Pin: <u>14 (随便设置的)</u>
    *
    * Name: <u>RIN1</u>
    * Direction: <u>Output</u>
    * Assigned Port: <u>PORTB (随便设置的)</u>
    * Assigned Pin: <u>15 (随便设置的)</u>
    *
    * Name: <u>RIN2</u>
    * Direction: <u>Output</u>
    * Assigned Port: <u>PORTB (随便设置的)</u>
    * Assigned Pin: <u>9 (随便设置的)</u>
### TIMER-PWM
* Name: <u>PWM_MOTOR</u>
  - Basic Configuration
    * PWM Period Count: <u>1000</u>
    * Start Timer: <u>deselect</u>
    - PWM Configuration
      * PWM Mode: <u>Edge-aligned Up Counting</u>
      * PWM Channel(s): <u>PWM Channel 0, PWM Channel 1</u>
  - PinMux
    * Timer Peripheral: <u>TIMA1</u>
    * Capture/Compare Pin 0: <u>PB2</u>
    * Capture/Compare Pin 1: <u>PB3</u>
### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PB6 | GPIO_OUTPUT | OLED_SCL | OLED 屏幕显示信息 |
| PB7 | GPIO_OUTPUT | OLED_SDA | OLED 屏幕显示信息 |
| PA26 | GPIO_INPUT | 编码器 A 相引脚 | 读取编码器 A 相脉冲信号 |
| PA27 | GPIO_INPUT | 编码器 A 相引脚 | 读取编码器 B 相脉冲信号 |
| PB2 | PWM_OUTPUT | 左轮速度控制引脚 | 控制左轮电机转速 |
| PB3 | PWM_OUTPUT | 右轮速度控制引脚 | 控制右轮电机转速 |
| 系统自动分配 | GPIO_OUTPUT | 左轮方向引脚1 | 控制左轮转动方向和启停 |
| 系统自动分配 | GPIO_OUTPUT | 左轮方向引脚2 | 控制左轮转动方向和启停 |
| 系统自动分配 | GPIO_OUTPUT | 右轮方向引脚1 | 控制右轮转动方向和启停 |
| 系统自动分配 | GPIO_OUTPUT | 右轮方向引脚2 | 控制右轮转动方向和启停 |

## 现象
编译、下载、复位后，转动编码器，可测到 PWM 引脚输出变化，以及方向引脚上的电平变化。

## 问题
|  | 问题 | 解决 |
| :---: | --- | --- |
| 1 | <div>第一行<br>第二行<br>第三行</div> | ... |
| 2 | ... | ... |