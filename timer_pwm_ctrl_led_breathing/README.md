* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)

## 简介
定时器输出PWM控制LED呼吸。

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin芯片
- J-Link OB调试器

## 配置
### TIMER-PWM
* Name: <u>PWM_LED2</u>
- PinMux
  * Capture/Compare Pin 0: <u>PA14</u>
- Basic Configuration
  - Clock Configuration
    * Timer Clock Source: <u>BUSCLK (总线时钟)</u>
    * Timer Clock Divider: <u>Divided by 1 (时钟分频)</u>
    * Timer Clock Prescale: <u>1 (时钟预分频)</u>
  * PWM Period Count: <u>1000</u>
  * Start Timer: <u>select (在初始化完成后立即启动)</u>
  - PWM Configuration
    * PWM Mode: <u>Edge-aligned Up Counting (边缘对齐向上计数)</u>
    * PWM Channel(s): <u>PWM Channel 0 (only)</u>
    - PWM Channel 0
      * Initial Value: <u>Low</u>
      * Counter Compare Value: <u>0</u>
      * Desired Duty Cycle (%): <u>(会自动关联至Counter Compare Value)</u>
      * Channel Update Mode: <u>Capture Compare value has immediate effect</u>

### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PA14  | TIMER_PWM | LED | 控制LED灯呼吸 |

## 现象
编译、下载、复位后，核心板上LED呈现呼吸灯效果。
