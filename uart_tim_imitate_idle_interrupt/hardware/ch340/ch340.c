#include "ch340.h"
#include "stdbool.h"
#include "stdarg.h"
#include "string.h"
#include "stdio.h"

uint16_t ch340_rx_cnt = 0; // 接收字节计数
uint16_t ch340_rx_len = 0; // 一次接收字节的数量，用于保存上面这个接收字节计数变量的
#define ch340_rx_cnt_MAX  500 // 接收字节计数最大值
uint8_t
    ch340_tx_package[100],
    ch340_rx_byte, //用于接收单个字节
    ch340_rx_package[ch340_rx_cnt_MAX]; //连续字节存放的数据包

volatile bool is_timer_uart_ch340_enable = false; //定时器是否已打开
volatile bool is_uart_ch340_receive_ok = false; //串口是否已接收完毕

void UART_CH340_INST_IRQHandler(void)
{
    switch( DL_UART_getPendingInterrupt(UART_CH340_INST) )
    {
        case DL_UART_IIDX_RX:
            ch340_rx_byte = DL_UART_receiveData(UART_CH340_INST);
            ch340_rx_package[ch340_rx_cnt] = ch340_rx_byte;
            if(ch340_rx_cnt < ch340_rx_cnt_MAX-1) ch340_rx_cnt++;
            //若接收数据超出数据包的长度，则接收到的新的字节只会不断赋给数据包数组最后一个元素

            DL_Timer_setTimerCount(TIMER_UART_CH340_INST, 0);
            if(is_timer_uart_ch340_enable == false)                 //如果定时器还没有打开
            {
                NVIC_ClearPendingIRQ(TIMER_UART_CH340_INST_INT_IRQN);   //清除定时器中断标志位
                DL_Timer_startCounter(TIMER_UART_CH340_INST);           //打开定时器
                is_timer_uart_ch340_enable = true;                      //标记定时器已打开
            }
            break;
        default: break;
    }
}

//定时中断函数
void TIMER_UART_CH340_INST_IRQHandler(void)
{
    switch( DL_Timer_getPendingInterrupt(TIMER_UART_CH340_INST) )
    {
        case DL_TIMER_IIDX_LOAD:
            ch340_rx_package[ch340_rx_cnt] = '\0';      //在接收数据最后一位补上结束符
            ch340_rx_len = ch340_rx_cnt;                //记录接收到的字节个数
            ch340_rx_cnt = 0;                           //计数清零，以待下一次接收
            is_uart_ch340_receive_ok = true;            //标记接收完成
            
            DL_Timer_stopCounter(TIMER_UART_CH340_INST);            //关闭定时器
            DL_Timer_setTimerCount(TIMER_UART_CH340_INST,0);        //清零定时器计数器
            is_timer_uart_ch340_enable = false;                     //标记定时器关闭
            NVIC_ClearPendingIRQ(TIMER_UART_CH340_INST_INT_IRQN);   //清除定时器中断标志位
            break;
        default: break;
    }
}





/* @brief 获取接收完毕的标志位，查看是否已接收完成。
 * @retval 1: 接收完成
 *         0: 未接收完成
 */
uint8_t get_ch340_TC_flag(void)
{
    if(is_uart_ch340_receive_ok == true)
    {
        is_timer_uart_ch340_enable = false;
        is_uart_ch340_receive_ok = false;
        return 1;//如果接收已完成，返回1
    }
    else
        return 0;//接收未完成，返回0
}

/* @brief 获取接收到的数据包。
 * @retval  接收到的数据包，是一个长度为256的uint8_t数组指针，有结束符'\0'。
 */
uint8_t* get_ch340_rx_package(void)
{ return ch340_rx_package; }

/* @brief 获取接收到的数据包长度。
 * @retval 接收完一帧数据的长度
 */
uint16_t get_ch340_rx_len(void)
{ return ch340_rx_len; }

/* @brief 清空数据包，实际是把第一位用结束符替代。*/
void clear_uart_ch340_rx_package(void)
{ ch340_rx_package[0] = '\0'; }





/* @brief 阻塞式地发送一个字节。*/
void uart_ch340_send_byte_blocking(uint8_t data)
{ DL_UART_transmitDataBlocking(UART_CH340_INST, data); }

/* @brief uart_ch340发送函数，printf的参数格式*/
void uart_ch340_printf(char* fmt,...)
{
    va_list ap;
    va_start(ap, fmt);
    vsprintf((char*)ch340_tx_package, fmt, ap);
    va_end(ap);
    uint16_t len = strlen((char*)ch340_tx_package);
    for(uint16_t i=0; i<len; i++)
        uart_ch340_send_byte_blocking(ch340_tx_package[i]);
}





/* @brief 初始化中断通道*/
static void uart_ch340_init(void)
{
    NVIC_ClearPendingIRQ(UART_CH340_INST_INT_IRQN);  //清除中断的挂起标志，防止意外的中断
    NVIC_EnableIRQ(UART_CH340_INST_INT_IRQN);        //开启UART_CH340的中断通道
}

/* @brief 辅助串口模拟空闲中断的定时器初始化。*/
static void timer_uart_ch340_init(void)
{
    NVIC_ClearPendingIRQ(TIMER_UART_CH340_INST_INT_IRQN);     //清除中断的挂起标志，防止意外的中断
    NVIC_EnableIRQ(TIMER_UART_CH340_INST_INT_IRQN);           //开启中断通道
}

/* @brief 总初始化*/
void ch340_init(void)
{
    uart_ch340_init();
    timer_uart_ch340_init();
}