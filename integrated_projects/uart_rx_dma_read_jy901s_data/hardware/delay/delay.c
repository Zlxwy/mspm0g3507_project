#include "delay.h"

uint64_t SYSTEMCLOCK;
void delay_init(uint32_t sysclock) {
    SYSTEMCLOCK = sysclock;
}

void delay_ms(uint32_t ms_cycles) {
    while(ms_cycles--) DL_Common_delayCycles(SYSTEMCLOCK/1000);
}

void delay_us(uint32_t us_cycles) {
    while(us_cycles--) DL_Common_delayCycles(SYSTEMCLOCK/1000000);
}

/**
 * @brief 按键消抖函数
 * @param gpio GPIO端口
 * @param pins GPIO引脚号
 * @param value 按键按下后的值
 */
void KeyDebounce(GPIO_Regs* gpio, uint32_t pins, uint32_t value) {
    delay_ms(20);
    while(DL_GPIO_readPins(gpio,pins) == value);
    delay_ms(20);
}