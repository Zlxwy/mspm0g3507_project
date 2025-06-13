#include "ti_msp_dl_config.h"
#include "delay.h"
#include "OLED.h"
#include "ch340.h"


int main(void)
{
    SYSCFG_DL_init();
    delay_init(CPUCLK_FREQ);

    ch340_init();
    OLED_Init();
    OLED_ShowString(01, 01, "Receiving......");

    while (1)
    {
        if( get_ch340_TC_flag() )
        {
            uart_ch340_printf("此次接收了%d个数据。\n发送的数据为：%s\n", get_ch340_rx_len(), (char*)get_ch340_rx_package());//串口回传
            OLED_Clear(); OLED_ShowString_FromLineToLine(1, (char*)get_ch340_rx_package(), 4);//屏幕显示
        }
    }
}


