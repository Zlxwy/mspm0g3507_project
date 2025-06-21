* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)
* [问题](#问题)

## 简介
用编码器旋钮控制普通 180 度 PWM 舵机的角度。

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin 芯片
- 正交编码器
- 普通 180 度 PWM 舵机
- 0.96 寸 128*64 像素 OLED 显示屏
- J-Link OB 调试器

## 配置
### Switch Board or Device
- 在 syscfg 右下角点击 **SWITCH** ，选择封装为 **LQFP-48** ，点击 **Confirm** 确认。
- 左侧栏 **Project Configuration** 会有一个报错、一个警告，在 **Select Device** 重新选择一下芯片型号，忽略掉警告就行。
### GPIO (1 Added)
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
### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PB6 | GPIO_OUTPUT | OLED_SCL | OLED 屏幕显示信息 |
| PB7 | GPIO_OUTPUT | OLED_SDA | OLED 屏幕显示信息 |

## 现象
编译、下载、复位后，核心板上LED熄灭，
然后核心板上的 LED 定时闪烁。

## 问题
|  | 问题 | 解决 |
| :---: | --- | --- |
| 1 | <div>第一行<br>第二行<br>第三行</div> | ... |
| 2 | ... | ... |