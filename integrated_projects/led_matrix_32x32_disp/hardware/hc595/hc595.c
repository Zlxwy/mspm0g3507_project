#include "hc595.h"

/*interface***************************************************************************/
#define HC595_DS_SET  DL_GPIO_writePinsVal(GPIO_HC595_PORT, GPIO_HC595_DS_PIN, GPIO_HC595_DS_PIN) // 拉高HC595_DS
#define HC595_DS_CLR  DL_GPIO_writePinsVal(GPIO_HC595_PORT, GPIO_HC595_DS_PIN, 0) // 拉低HC595_DS

#define HC595_SHCP_SET  DL_GPIO_writePinsVal(GPIO_HC595_PORT, GPIO_HC595_SHCP_PIN, GPIO_HC595_SHCP_PIN) // 拉高HC595_SHCP
#define HC595_SHCP_CLR  DL_GPIO_writePinsVal(GPIO_HC595_PORT, GPIO_HC595_SHCP_PIN, 0) // 拉低HC595_SHCP

#define HC595_STCP_SET  DL_GPIO_writePinsVal(GPIO_HC595_PORT, GPIO_HC595_STCP_PIN, GPIO_HC595_STCP_PIN) // 拉高HC595_STCP
#define HC595_STCP_CLR  DL_GPIO_writePinsVal(GPIO_HC595_PORT, GPIO_HC595_STCP_PIN, 0) // 拉低HC595_STCP

#define HC595_NOE_SET  DL_GPIO_writePinsVal(GPIO_HC595_PORT, GPIO_HC595_NOE_PIN, GPIO_HC595_NOE_PIN) // 拉高HC595_NOE
#define HC595_NOE_CLR  DL_GPIO_writePinsVal(GPIO_HC595_PORT, GPIO_HC595_NOE_PIN, 0) // 拉低HC595_NOE

#define HC595_DELAY  ; // 如果单片机速度过快，在此设置一些延时

void HC595Init(void) {
    HC595_DS_CLR;
    HC595_SHCP_CLR;
    HC595_STCP_CLR;
    HC595_NOE_CLR;
}
/***************************************************************************interface*/

/**
 * @brief 将给定位数的数据逐位串行写入HC595移位寄存器。
 * @param data 需要输出的数据
 * @param bitslen 指定输出的数据位数
 */
void HC595ShiftBits(uint64_t data, uint8_t bitslen) {
    for (uint8_t i=0; i<bitslen; i++) {
        if( data & (1<<(bitslen-1-i)) )
            HC595_DS_SET;
        else
            HC595_DS_CLR;
        HC595_SHCP_SET;
        HC595_DELAY;
        HC595_SHCP_CLR;
        HC595_DELAY;
    }
}

/**
 * @brief 该函数用于将HC595移位寄存器中当前的位锁存到输出端。
 * @note 需要在已经配置好HC595移位寄存器的引脚以及数据之后调用该函数。
 */
void HC595LatchBits(void) {
    HC595_STCP_SET;
    HC595_DELAY;
    HC595_STCP_CLR;
    HC595_DELAY;
}

/**
 * @brief 向74HC595移位寄存器的输出端口写入指定长度的位数据，内部依此调用HC595ShiftBits()和HC595LatchBits()函数
 * @note 若写入的位数比上一次写入的位数少，则输出端口的高位数据仍保留上一次写入的低位数据。
 * @param data 要写入的位数据，类型为uint64_t
 * @param bitslen 要写入的位数，类型为uint8_t
 */
void HC595OutputBits(uint64_t data, uint8_t bitslen) {
    HC595ShiftBits(data, bitslen);
    HC595LatchBits();
}



/**
 * @brief 指示每个位上显示的数，例如：
 * @arg __disp_num[0]=6，则数码管第0位显示6；
 * @arg __disp_num[3]=8，则数码管第3位显示8；
 * @arg __disp_num[5]=10，则数码管第5位显示空格' '
 * @arg __disp_num[6]=11，则数码管第6位显示横杆'-'
 */
volatile uint8_t __disp_num[8] = {10, 10, 10, 10, 10, 10, 10, 10};

/**
 * @brief 共阳数码管显示的字形，例如：
 * @arg __disp_seg[0]是数字0的字形，
 * @arg __disp_seg[2]是数字2的字形，
 * @arg __disp_seg[10]是空格' '的字形，
 * @arg __disp_seg[11]是横杆'-'的字形
 */
const uint8_t __disp_seg[12] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF, 0xBF};

/**
 * @brief 共阳数码管在哪一个位上显示
 */
const uint8_t __disp_sel[8]  = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

/**
 * @brief 我自己的共阳数码管模块，在第digit位上显示数字num
 * @note 数码管从右到左分别为第0~7位
 * @param digit 第digit位
 * @param num 显示的数字
 */
void MyCasegShowNum(uint8_t digit, uint8_t num) {
    /*输入的这个16位数，由高到低位依次为：DIG7~DIG0, DP, G~A*/
    uint16_t disp = (__disp_sel[digit]<<8) | __disp_seg[num];
    HC595OutputBits(disp, 16);
}