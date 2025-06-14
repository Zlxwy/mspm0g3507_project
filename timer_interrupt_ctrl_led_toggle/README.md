* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)

## 简介
串口的接收DMA，每接收到一个字节，就会转移到一个数组之中，地址不断自增，到数组末尾后又会回到起始位置。

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin芯片
- J-Link OB调试器

## 配置
### Switch Board or Device
- 在syscfg右下角点击 **SWITCH** ，选择封装为 **LQFP-48** ，点击 **Confirm** 确认。
- 左侧栏 **Project Configuration** 会有一个报错、一个警告，在 **Select Device** 重新选择一下芯片型号，忽略掉警告就行。
### GPIO
* Name: <u>GPIO_LED</u>
  - Group Pins
    * Name: <u>PIN_D2</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Cleared</u>
    * Assigned Port: <u>PORTA</u>
    * Assigned Pin: <u>14</u>
### TIMER
* Name: <u>TIMER_TEST</u>
- Basic Configuration
  - Clock Configuration
    * Timer Clock Source: <u>BUSCLK(总线时钟)</u>
    * Timer Clock Divider: <u>Divided by 8</u>
    * Timer Clock Prescaler: <u>200</u>
  * Timer Mode: <u>Periodic Up Counting</u>
  * Desired Timer Period: <u>500ms</u>
  * Start Timer: <u>select</u>
- Interrupts Configuration
  * Enable Interrupts: <u>Load event</u>

### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PA14  | GPIO_OUTPUT | LED | 控制LED灯翻转 |

## 现象
编译、下载、复位后，核心板上LED熄灭，
然后核心板上的LED定时闪烁。