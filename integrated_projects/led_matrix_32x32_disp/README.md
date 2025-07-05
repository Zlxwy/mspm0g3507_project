* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)
* [问题](#问题)

## 简介
32*32 的 LED 矩阵，使用 74 系列芯片进行 IO 扩展驱动。

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin 芯片
- 74HC595
- 74HC138
- 74HC139
- 32*32 的 LED 点阵屏
- J-Link OB 调试器

## 配置
### Switch Board or Device
- 在 syscfg 右下角点击 **SWITCH** ，选择封装为 **LQFP-48** ，点击 **Confirm** 确认。
- 左侧栏 **Project Configuration** 会有一个报错、一个警告，在 **Select Device** 重新选择一下芯片型号，忽略掉警告就行。
### GPIO (2 Added)
* Name: <u>GPIO_HC595</u>
  - Group Pins (4 added)
    * Name: <u>DS</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Cleared</u>
    * Assigned Port: <u>PORTB</u>
    * Assigned Pin: <u>18</u>
    * 
    * Name: <u>SHCP</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Cleared</u>
    * Assigned Port: <u>PORTB</u>
    * Assigned Pin: <u>19</u>
    * 
    * Name: <u>STCP</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Cleared</u>
    * Assigned Port: <u>PORTB</u>
    * Assigned Pin: <u>20</u>
    * 
    * Name: <u>NOE</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Cleared</u>
    * Assigned Port: <u>PORTB</u>
    * Assigned Pin: <u>24</u>
* Name: <u>GPIO_YMQ</u>
  - Group Pins (5 added)
    * Name: <u>PIN_0</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Cleared</u>
    * Assigned Port: <u>PORTA</u>
    * Assigned Pin: <u>12</u>
    * 
    * Name: <u>PIN_1</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Cleared</u>
    * Assigned Port: <u>PORTA</u>
    * Assigned Pin: <u>13</u>
    * 
    * Name: <u>PIN_2</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Cleared</u>
    * Assigned Port: <u>PORTA</u>
    * Assigned Pin: <u>14</u>
    * 
    * Name: <u>PIN_3</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Cleared</u>
    * Assigned Port: <u>PORTA</u>
    * Assigned Pin: <u>15</u>
    * 
    * Name: <u>PIN_4</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Cleared</u>
    * Assigned Port: <u>PORTA</u>
    * Assigned Pin: <u>16</u>
### TIMER
* Name: <u>TIMER_LED_MATRIX</u>
- Basic Configuration
  - Clock Configuration
    * Timer Clock Source: <u>BUSCLK(总线时钟)</u>
    * Timer Clock Divider: <u>Divided by 1</u>
    * Timer Clock Prescaler: <u>256</u>
  * Timer Mode: <u>Periodic Up Counting</u>
  * Desired Timer Period: <u>500ms</u>
  * Start Timer: <u>deselect</u>
- Interrupts Configuration
  * Enable Interrupts: <u>Load event</u>
  * Interrupt Priority: <u>Level 0 - Highest</u>
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