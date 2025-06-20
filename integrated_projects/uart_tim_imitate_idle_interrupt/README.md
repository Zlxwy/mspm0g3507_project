## 简介

用定时器配合串口模拟空闲中断，接收字符串连续的数据，如果连续2ms之内未接收到数据，则认为此次字符串数据已接收完成。



## 器件

- 立创地猛星MSPM0G3507核心板。

- J-Link OB调试器



## Sysconfig配置

### 【重新选择芯片封装】

- 立创这块MSPM0G3507芯片是LQFP-48封装，要在syscfg右下角点击**SWITCH**，选择封装为**LQFP-48**，点击**Confirm**确认。

- **Project Configuration**会有一个报错、一个警告，再在里面选择一下芯片型号，忽略掉警告就行。

### 【I2C0连接OLED】

- 填写名称**I2C_OLED**，

- 勾选**Enable Controller Mode**，

- **Standard Bus Speed**选择**Fast Mode (400kHz)**，

- **PinMux**内选择外设**I2C0**，**SDA**引脚选择**PA0**，**SCL**引脚选择**PA1**。

### 【UART0连接CH340串口芯片】

- 填写名称**UART_CH340**，

- 填写波特率**115200**，位长、校验位、停止位、硬件流控这些保持默认，

- **Interrupt Configuration**栏目内打开**Receive**中断，优先级**Level 0 - Highest**，

- **PinMux**栏目内选择**UART0**，**RX Pin**选择**PA11**，**TX Pin**选择**PA10**，

- **Pin Configuration**内两个引脚都设置上拉：勾选**Enable pin configuration**，点开新增栏目**Digital IOMUX Features**，**Internal Resistor**下拉栏选择**Pull-Up Resistor**就行了。（这个步骤很重要，要不然串口引脚空闲状态都是高阻态）

### 【TIMG8模拟串口UART0空闲中断】

- 填写名称**TIMER_UART**，

- **Timer Mode**选择**Periodic Up Counting**

- **Basic Configuration / Desired Timer Period**填写**2ms**（如果报错的话，就在**Timer Clock Divider**修改时钟分频，**Timer Clock Prescaler**修改预分频值）。

- **Interrupts Configuration**栏目内选择**Load event**，中断优先级选择**Level 1 - High**，要比串口接收中断低。




## 连线

| 引脚 | 外设功能 | 连接设备 | 作用 |
| --- | --- | --- | --- |
| PA0 | I2C0_SDA | OLED_SDA | OLED屏幕显示 |
| PA1 | I2C0_SCL | OLED_SCL | OLED屏幕显示 |
| PA10 | UART0_TX | CH340_RX | 与电脑进行串口通信 |
| PA11 | UART0_RX | CH340_TX | 与电脑进行串口通信 |



## 现象

- 用数据线直接连接电脑和核心板上的Type-C插座，在核心板上电后，会先在屏幕显示"receiving..."，然后通过串口发送一串提示初始化成功的字符。

- 电脑串口助手选择115200波特率，1位停止位，8位数据位，无校验位，向G3507发送字符串，G3507会将接收到的字符串显示在OLED上，然后添加换行符后回传至电脑。

