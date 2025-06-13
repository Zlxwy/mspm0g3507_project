#include "ti_msp_dl_config.h"
#include "delay.h"
#include "OLED.h"

int main(void)
{
    SYSCFG_DL_init(); //SYSCFG的所有初始化函数
    delay_init(CPUCLK_FREQ); //延时函数初始化

    OLED_Init();

    OLED_ShowString_FromLineToLine(1,"0123456789ABCDEF0123456789abcdefabcdefghijklmnopABCDEFGHIJKLMNOP",4);
    // OLED_ShowString(1, 1, "This is G3507");

    while(1)
    {

    }
}
