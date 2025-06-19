* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)
* [问题](#问题)

## 简介
定时器正交编码器接口 (Quadrature Encoder Interface) 的测试。（不想使用，不稳定。）

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin 芯片
- 正交编码器
- 0.96 寸 128*64 像素 OLED 显示屏
- J-Link OB 调试器

## 配置
### Switch Board or Device
- 在 syscfg 右下角点击 **SWITCH** ，选择封装为 **LQFP-48** ，点击 **Confirm** 确认。
- 左侧栏 **Project Configuration** 会有一个报错、一个警告，在 **Select Device** 重新选择一下芯片型号，忽略掉警告就行。
### GPIO
* Name: <u>GPIO_OLED</u>
  - Group Pins
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
### TIMER-QEI
* Name: <u>QEI_ENCODER</u>
  - PinMux
    * QEI Peripheral: <u>TIMG8</u>
    * Capture/Compare Pin 0: <u>PA26</u>
    * Capture/Compare Pin 1: <u>PA27</u>
  - Basic Configuration
    - Clock Configuration
      * Start Timer: <u>deselect</u>
### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PB6 | GPIO_OUTPUT | OLED_SCL | OLED 屏幕显示信息 |
| PB7 | GPIO_OUTPUT | OLED_SDA | OLED 屏幕显示信息 |
| PA26 | TIMER_QEI_CC0 | Encoder_A | 编码器 A 相脉冲信号 |
| PA27 | TIMER_QEI_CC1 | Encoder_B | 编码器 B 相脉冲信号 |

## 现象
编译、下载、复位后
  - 转动编码器，可看到显示屏上 Cnt 数值增加
  - 反转编码器，可看到显示屏上 Dir 标签改变

## 问题
|  | 问题 | 解决 |
| :---: | --- | --- |
| 1 | <div>编码器外设功能映射在一些引脚上（如 PA22 和 PA23 、PA1 和 PA0），<br>会出现计数不稳定，甚至无法计数的情况，<br>不知道是芯片的问题，还是这块地猛星核心板的问题。</div> | 暂无解决方法，只把编码器功能映射到了稍微稳定一点的引脚上 (PA26 PA27) |
| 2 | ... | ... |