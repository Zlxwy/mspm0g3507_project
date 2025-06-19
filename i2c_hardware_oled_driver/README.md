* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)

## 简介
使用芯片的硬件 I2C 外设，控制 OLED 进行显示，移植自江协科技的 OLED 驱动库。
- [江协科技 0.96 英寸 OLED 视频教程](https://www.bilibili.com/video/BV1EN41177Pc)
- [江协科技 0.96 英寸 OLED 资料下载](https://jiangxiekeji.com/download.html)

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin 芯片
- 0.96 英寸 OLED 显示屏，芯片 SSD1306（1.3寸 OLED 显示屏也可以，芯片是 SH1106 ，需要更改 OLED.c 中的 OLED_SetCursor 函数）
- J-Link OB调试器

## 配置
### Switch Board or Device
- 在 syscfg 右下角点击 **SWITCH** ，选择封装为 **LQFP-48** ，点击 **Confirm** 确认。
- 左侧栏 **Project Configuration** 会有一个报错、一个警告，在 **Select Device** 重新选择一下芯片型号，忽略掉警告就行。
### I2C
* Name: <u>I2C_OLED</u>
- PinMux
  * I2C Peripheral: <u>I2C0</u>
  * I2C Serial Data line (SDA): <u>PA0</u>
  * I2C Serial Clock line (SCL): <u>PA1</u>
- Basic Configuration
  * Enable Controller Mode: <u>select</u>
  - I2C Controller Basic Configuration
    * Standard Bus Speed: <u>Fast Mode Plus (1MHz)</u>
    * Custom Bus Speed (Hz): <u>800000</u>
### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PA1  | I2C0_SCL | OLED_SCL | 控制OLED显示 |
| PA0  | I2C0_SDA | OLED_SDA | 控制OLED显示 |

## 现象
编译、下载、复位后，OLED 根据 main 函数中的程序进行显示。