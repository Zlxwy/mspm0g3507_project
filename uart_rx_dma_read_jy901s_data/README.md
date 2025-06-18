* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)
* [问题](#问题)

> 使用这个程序之前，先要在维特上位机设置 JY901S 的输出数据格式，参考[配置部分操作](#配置)。

## 简介
通过串口接收 DMA 的方式读取维特JY901S九轴姿态传感器数据，该串口接收方式不占用CPU资源。

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin 芯片
- 维特 JY901S 九轴姿态传感器
- 4线 I2C 、128*64 像素 OLED 屏幕
- J-Link OB调试器

## 配置
### JY901S配置（在维特的上位机中）
- 算法：<u>九轴算法</u>
- 波特率：<u>115200</u>
- 输出带宽：<u>188Hz</u>
- 输出速率：<u>200Hz</u>
- 输出数据：<u>角加速度、角速度、欧拉角（只勾选这三种）</u>
### GPIO
* Name: <u>GPIO_OLED</u>
  - Group Pins (2 added)
    * Name: <u>PIN_SCL</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Set</u>
    - Digital IOMUX Features
      * Internal Resistor: <u>Pull-Up Resistor</u>
    * Assigned Port: <u>PORTB</u>
    * Assigned Pin: <u>6</u>
    * 
    * Name: <u>PIN_SDA</u>
    * Direction: <u>Output</u>
    * Initial Value: <u>Set</u>
    - Digital IOMUX Features
      * Internal Resistor: <u>Pull-Up Resistor</u>
    * Assigned Port: <u>PORTB</u>
    * Assigned Pin: <u>7</u>
### UART
* UART Name: <span style="text-decoration: underline;">tzrgz</span>UART_JY901S</span>
- PinMux
  * UART Peripheral: <u>UART3</u>
  * RX Pin: <u>PA13</u>
- Basic Configuration
  - UART Initialization Configuration
    * Target Baud Rate: <u>115200</u>
- Advanced Configuration
  * Communication Direction: <u>RX only</u>
- DMA Configuration
  * Configure DMA RX Trigger: <u>UART RX interrupt</u>
  * Enable DMA RX Trigger: <u>select</u>
  - DMA Channel RX
    * Name: <u>DMA_UART_JY901S</u>
    * Address Mode: <u>Fixed addr. to Block addr.</u>
    * Source Length: <u>Byte</u>
    * Destination Length: <u>Byte</u>
    * Destination Address Direction: <u>Increment</u>
    * Configure Transfer Size: <u>select</u>
    * Transfer Size: <u>66</u>
    * Transfer Mode: <u>Repeat Single</u>
    * Source Address Increment: <u>Do not change address after each transfer</u>
    * Destination Address Increment: <u>Increment</u>
- Pin Configuration
  - RX Pin
    * Enable pin configuration: <u>select</u>
    - Digital IOMUX Features
      * Internal Resistor: <u>Pull-Up Resistor</u>
### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PA13  | UART3_RXD | JY901S_TXD | 接收维特陀螺仪数据 |
| PB6  | GPIO_OUTPUT | OLED_SCL | 显示信息 |
| PB7  | GPIO_OUTPUT | OLED_SDA | 显示信息 |

## 现象
编译、下载、复位（一定一定要按复位键）后，芯片通过串口读取维特JY901S九轴姿态传感器数据，通过DMA转移到一个数组rxData中，在main函数的while循环不断读取这个数组rxData，并显示在OLED屏幕上。

## 问题
| 问题 | 解决 |
| ---- | --- |
| <div>下载程序时出现以下报错：<br><font color="red">Trouble Writing Register PC:Verification of RAMCode failed @ address 0x20200400.<br>Write: 0x2100486A 60416001 Read: 0x0D0B7707 00005255<br>Failed to prepare for programming. Failed to download RAMCode!</font></div> | 断开 JY901S 和 MCU 的连线，重新下载程序后再连接 |