* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)
* [问题](#问题)

## 简介
2025年电赛项目（只完成第一二问T_T）

## 器件
- 立创天猛星核心板，MSPM0G3507-64Pin 芯片
- 8 路循迹
- 0.96 寸 128*64 像素 OLED 显示屏
- 带编码器电机
- 按键
- 继电器，控制激光开关
- LX225 总线舵机
- K230 视觉模块庐山派
- J-Link OB 调试器

## 配置
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
    * Assigned Pin: <u>1</u>
### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PB6 | GPIO_OUTPUT | OLED_SCL | OLED 显示信息 |
| PB1 | GPIO_OUTPUT | OLED_SDA | OLED 显示信息 |
| PA28 | GPIO_OUTPUT | leftMotor_IN1 | 左电机方向引脚 |
| PA31 | GPIO_OUTPUT | leftMotor_IN2 | 左电机方向引脚 |
| PB12 | GPIO_OUTPUT | rightMotor_IN3 | 右电机方向引脚 |
| PB17 | GPIO_OUTPUT | rightMotor_IN4 | 右电机方向引脚 |
| PA12 | TIM_PWM | leftPWM  | 左电机速度PWM |
| PA13 | TIM_PWM | rightPWM | 右电机速度PWM |
| PB15 | GPIO_INTERRUPT | leftEncoder_A | 左电机编码器 |
| PB13 | GPIO_INTERRUPT | leftEncoder_B | 左电机编码器 |
| PB8 | GPIO_INTERRUPT | rightEncoder_A | 右电机编码器 |
| PB7 | GPIO_INTERRUPT | rightEncoder_B | 右电机编码器 |
| PB18 | GPIO_INPUT | 循迹传感器0 | 循迹模块 | 
| PB19 | GPIO_INPUT | 循迹传感器1 | 循迹模块 | 
| PB20 | GPIO_INPUT | 循迹传感器2 | 循迹模块 | 
| PB21 | GPIO_INPUT | 循迹传感器3 | 循迹模块 | 
| PB22 | GPIO_INPUT | 循迹传感器4 | 循迹模块 | 
| PB23 | GPIO_INPUT | 循迹传感器5 | 循迹模块 | 
| PB24 | GPIO_INPUT | 循迹传感器6 | 循迹模块 | 
| PB25 | GPIO_INPUT | 循迹传感器7 | 循迹模块 | 
| PA14 | GPIO_INPUT | key_add   | 按键控制 |
| PA15 | GPIO_INPUT | key_enter | 按键控制 |
| PA16 | GPIO_INPUT | key_xxx   | 按键控制 |
| PA27 | GPIO_OUTPUT | 继电器 | 控制激光开关 |
| PA8 | UART_TX | LX225_SIG | 总线舵机云台 |
| PA11 | UART_RX | K230_UART_TX | 视觉模块通信 |

5ms的定时中断控制电机

## 现象
编译、下载、复位后，核心板上LED熄灭，
然后核心板上的 LED 定时闪烁。

## 问题
|  | 问题 | 解决 |
| :---: | --- | --- |
| 1 | <div>第一行<br>第二行<br>第三行</div> | ... |
| 2 | ... | ... |