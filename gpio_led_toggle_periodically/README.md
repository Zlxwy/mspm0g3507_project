* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)

## 简介
LED灯周期性翻转，用于测试芯片的GPIO功能。

## 器件
- 立创地猛星开发板，MSPM0G3507-48Pin芯片
- J-Link OB调试器

## 配置
### GPIO
- PORT Name: GPIO_LED
  - PIN Name: PIN_D2
    - Group Pins > Direction: Output
    - Group Pins > Initial Value: Cleared
    - Group Pins > Assigned Port: PORTA
    - Group Pins > Assigned Pin: 14
    - 其他默认配置
### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PA14  | GPIO_OUTPUT | 核心板上LED | 翻转电平显示 |

## 现象
- 编译、下载、复位后，PA14引脚周期性翻转电平，可看到LED闪烁。
