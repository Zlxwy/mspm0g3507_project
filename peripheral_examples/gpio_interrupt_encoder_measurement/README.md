* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)
* [问题](#问题)

<font color="red">**（不要接 5V 电压的编码器）**</font>

## 简介
用 GPIO 中断读取编码器脉冲信号进行计数，并在 OLED 屏幕上显示信息。

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin 芯片
- 正交编码器
- 0.96 寸 128*64 像素 OLED 显示屏
- J-Link OB 调试器

## 配置
### Switch Board or Device
- 在 syscfg 右下角点击 **SWITCH** ，选择封装为 **LQFP-48** ，点击 **Confirm** 确认。
- 左侧栏 **Project Configuration** 会有一个报错、一个警告，在 **Select Device** 重新选择一下芯片型号，忽略掉警告就行。
### GPIO (2 Added)
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


### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PB6 | GPIO_OUTPUT | OLED_SCL | OLED 屏幕显示信息 |
| PB7 | GPIO_OUTPUT | OLED_SDA | OLED 屏幕显示信息 |
| PA26 | GPIO_INPUT | 编码器 A 相引脚 | 读取编码器 A 相脉冲信号 |
| PA27 | GPIO_INPUT | 编码器 A 相引脚 | 读取编码器 B 相脉冲信号 |

## 现象
编译、下载、复位后
  - 转动编码器，可看到显示屏上 Cnt 数值增加
  - 反转编码器，可看到显示屏上 Dir 标签改变

## 问题
暂无问题