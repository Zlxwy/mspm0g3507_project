* [简介](#简介)
* [器件](#器件)
* [配置](#配置)
* [连线](#连线)
* [现象](#现象)

## 简介
产生一路PWM触发GPIO中断，在GPIO中断函数内控制LED翻转。

## 器件
- 立创地猛星核心板，MSPM0G3507-48Pin芯片
- 跳线帽1个，或杜邦线1根
- J-Link OB调试器

## 配置
### Switch Board or Device
- 在syscfg右下角点击 **SWITCH** ，选择封装为 **LQFP-48** ，点击 **Confirm** 确认。
- 左侧栏 **Project Configuration** 会有一个报错、一个警告，在 **Select Device** 重新选择一下芯片型号，忽略掉警告就行。
### TIMER-PWM
- Name: <u>PWM_TRIG</u>
- PinMux
  * Capture/Compare Pin 0: <u>PA12</u>
- Basic Configuration
  - Clock Configuration
    * Timer Clock Prescale: <u>100</u>
  * PWM Period Count: <u>32000</u>
  * Calculated PWM Frequency (Hz): <u>(由PWM Period Count影响)10Hz</u>
  * Start Timer: <u>select</u>
  - PWM Configuration
    * PWM Mode: <u>Edge-aligned Up Counting</u>
    * PWM Channel(s): <u>PWM Channel 0 (only)</u>
    - PWM Channel 0
      * Desired Duty Cycle (%): <u>50</u>
      * Channel Update Mode: <u>Capture Compare value has immediate effect</u>
### GPIO
* Name: <u>GPIO_EXTI</u>
- Group Pins
  * Name: <u>PIN_EXTI</u>
  * Direction: <u>Input</u>
  * Assigned Port: <u>GPIOA</u>
  * Assigned Pin: <u>13</u>
  - Interrupts/Events
    * Enable Interrupts: <u>select</u>
    * Trigger Polarity: <u>Trigger on Rising Edge</u>
* Name: <u>GPIO_LED</u>
  * Name: <u>PIN_D2</u>
  * Direction: <u>Output</u>
  * Initial Value: <u>Cleared</u>
  * Assigned Port: <u>GPIOA</u>
  * Assigned Pin: <u>14</u>

### TIMER-PWM

### 调试配置
- SEGGER J-Link Emulator

## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| ---- | --- | --- | --- |
| PA12 | TIMERG0_PWM | 跳线帽短接至PA13 | 产生PWM触发GPIO中断 |
| PA13 | GPIO_EXTI | 跳线帽短接至PA12 | 由PWM触发GPIO中断 |
| PA14 | GPIO_OUTPUT | LED | 控制LED翻转 |

## 现象
编译、下载、复位后，核心板上的LED定时闪烁。