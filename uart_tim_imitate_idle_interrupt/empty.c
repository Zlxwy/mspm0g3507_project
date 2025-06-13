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

    while (1) {
        if( get_ch340_TC_flag() ) { // 如果接收到数据
            OLED_Clear(); // 清屏
            OLED_ShowString_FromLineToLine(1, (char*)get_ch340_rx_pack(), 4); // 屏幕显示
            uart_ch340_printf(" >(%d) %s\n", get_ch340_rx_len(), (char*)get_ch340_rx_pack()); // 串口回传
        }
    }
}


