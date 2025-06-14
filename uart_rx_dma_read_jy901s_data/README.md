* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)

## 简介
通过串口接收DMA的方式读取维特JY901S九轴姿态传感器数据，该串口接收方式不占用CPU资源。

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin芯片
- 维特JY901S九轴姿态传感器
- 4线I2C、128*64像素 OLED 屏幕
- J-Link OB调试器

## 配置
### I2C
* I2C Name: <u>I2C_OLED</u>
- Basic Configuration
  * Enable Controller Mode: <u>select</u>
  - I2C Controller Basic Configuration
    * Standard Bus Speed: <u>Fast Mode (400kHz)</u>
- PinMux
  * I2C Peripheral: <u>I2C0</u>
  * I2C Serial Data line (SDA): <u>PA0</u>
  * I2C Serial Clock line (SCL): <u>PA1</u>
### UART
* UART Name: <u>UART_JY901S</u>
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
    * Transfer Size: <u>88</u>
    * Transfer Mode: <u>Repeat Single</u>
    * Source Address Increment: <u>Do not change address after each transfer</u>
    * Destination Address Increment: <u>Increment</u>
- Pin Configuration
  - RX Pin
    * Enable pin configuration: <u>select</u>
    - Digital IOMUX Features
      * Internal Resistor: <u>Pull-Up Resistor</u>
- PinMux
  * UART Peripheral: <u>UART3</u>
  * RX Pin: <u>PA13</u>
### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PA13  | UART3_RXD | JY901S_TXD | 接收维特陀螺仪数据 |
| PA1  | I2C0_SCL | OLED_SCL | 显示信息 |
| PA0  | I2C0_SDA | OLED_SDA | 显示信息 |

## 现象
编译、下载、复位（一定一定要按复位键）后，芯片通过串口读取维特JY901S九轴姿态传感器数据，通过DMA转移到一个数组rxData中，在main函数的while循环不断读取这个数组rxData，并显示在OLED屏幕上。