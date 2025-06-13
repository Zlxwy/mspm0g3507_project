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
- DMA Configuration
  * Configure DMA RX Trigger: <u>UART RX interrupt</u>
  * Enable DMA RX Trigger: <u>select</u>
  - DMA Channel RX
    * Name: <u>DMA_UART_CH340</u>
    * Address Mode: <u>Fixed addr. to Block addr.</u>
    * Source Length: <u>Byte</u>
    * Destination Length: <u>Byte</u>
    * Destination Address Direction: <u>Increment</u>
    * Configure Transfer Size: <u>select</u>
    * Transfer Size: <u>5</u>
    * Transfer Mode: <u>Repeat Single</u>
    * Source Address Increment: <u>Do not change address after each transfer</u>
    * Destination Address Increment: <u>Increment</u>
- PinMux
  * UART Peripheral: <u>UART0</u>
  * RX Pin: <u>PA11</u>
### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PA11  | UART0_RXD | CH340_TXD | 接收电脑串口助手发送的数据 |
| PA14  | GPIO_OUTPUT | LED | 控制LED灯 |

## 现象
编译、下载、复位后，核心板上LED点亮，通过Type-C数据线将核心板连接到电脑，在电脑串口助手向核心板发送一个字符串"12345"，然后核心板上的LED快速闪烁。