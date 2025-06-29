#include "decoder_5_32.h"

// 由低位到高位
volatile uint32_t __ymq_pin[5] = {
    GPIO_YMQ_PIN_0_PIN,
    GPIO_YMQ_PIN_1_PIN,
    GPIO_YMQ_PIN_2_PIN,
    GPIO_YMQ_PIN_3_PIN,
    GPIO_YMQ_PIN_4_PIN
};

void YMQInit(void) {
    YMQWritePort(0);
}

/**
 * @brief 控制5-32译码器的0~31输出端口，哪一个使能（输出低电平）
 * @param data 控制使能的端口号，勿超过范围[0,31]
 */
void YMQWritePort(uint8_t data) {
    // // 写输出端口方法一
    // for (uint8_t i=0; i<5; i++) {
    //     DL_GPIO_writePinsVal(
    //         GPIO_YMQ_PORT,
    //         __ymq_pin[i],
    //         (data & (1 << i)) ? __ymq_pin[i] : 0
    //     );
    // }

    // // 写输出端口方法二
    // DL_GPIO_writePinsVal(
    //     GPIO_YMQ_PORT,
    //     GPIO_YMQ_PIN_0_PIN | GPIO_YMQ_PIN_1_PIN | GPIO_YMQ_PIN_2_PIN | GPIO_YMQ_PIN_3_PIN | GPIO_YMQ_PIN_4_PIN,
    //     data << (16-4)
    // );

    // 写输出端口方法三
    DL_GPIO_writePinsVal(GPIO_YMQ_PORT, 0x0001f000, data<<12);
}