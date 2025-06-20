* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)

## 简介
串口的超时中断（空闲中断）。

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin芯片
- J-Link OB调试器

## 配置
### GPIO
* Name: <u>GPIO_LED</u>
  - Group Pins
    * Name: <u>PIN_D2</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Cleared</u>
    * Assigned Port: <u>PORTA</u>
    * Assigned Pin: <u>14</u>
### UART
* UART Name: <u>UART_CH340</u>
- Basic Configuration
  - UART Initialization Configuration
    * Target Baud Rate: <u>115200</u>
- Advanced Configuration
  * Communication Direction: <u>RX only</u>
  * RX Timeout Interrupt Counts: <u>1</u>
- Interrupt Configuration
  * Enable Interrupts: <u>RX timeout</u>
- PinMux
  * UART Peripheral: <u>UART0</u>
  * RX Pin: <u>PA11</u>
### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PA11  | UART0_RXD | CH340_TXD | 接收电脑串口助手发送的数据 |
| PA14  | GPIO_OUTPUT | LED | 控制LED灯翻转 |

## 现象
编译、下载、复位后，通过Type-C数据线将核心板连接到电脑，
在电脑串口助手向核心板发送一个字符、或是一个字符串，
在芯片接收完串口数据后，重新回归空闲状态，便会触发一个接收超时中断，
在接收超时中断函数内触发PA14上的LED翻转电平。