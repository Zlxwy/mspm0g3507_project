#include "encoder.h"
void Encoder_Init(void) {
    NVIC_ClearPendingIRQ(GPIO_ECD_INT_IRQN);
    NVIC_EnableIRQ(GPIO_ECD_INT_IRQN);
}
/**
 * @brief 正转反转是相对的，可以自己定义顺时针或逆时针为正转。
 *
 * 正转（自己定义的正转）
        ___     ___     ___     ___      
   A       |___|   |___|   |___|   |___
       __     ___     ___     ___     __
   B     |___|   |___|   |___|   |___|
   
 * 反转（自己定义的反转）
       __     ___     ___     ___     __
   A     |___|   |___|   |___|   |___|
        ___     ___     ___     ___      
   B       |___|   |___|   |___|   |___
 *
 */
int16_t leftEncoderCNT = 0;
int16_t righEncoderCNT = 0;
void GROUP1_IRQHandler(void) {
    uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(
        GPIO_ECD_PORT,
        GPIO_ECD_LEFT_A_PIN |
        GPIO_ECD_LEFT_B_PIN |
        GPIO_ECD_RIGH_A_PIN |
        GPIO_ECD_RIGH_B_PIN
    );
    if ((gpioB & GPIO_ECD_LEFT_A_PIN) == GPIO_ECD_LEFT_A_PIN) {
        if (DL_GPIO_readPins(GPIO_ECD_PORT, GPIO_ECD_LEFT_B_PIN) == GPIO_ECD_LEFT_B_PIN) leftEncoderCNT++;
        else                                                                leftEncoderCNT--;
        DL_GPIO_clearInterruptStatus(GPIO_ECD_PORT, GPIO_ECD_LEFT_A_PIN);
    }
    if ((gpioB & GPIO_ECD_LEFT_B_PIN) == GPIO_ECD_LEFT_B_PIN) {
        if (DL_GPIO_readPins(GPIO_ECD_PORT, GPIO_ECD_LEFT_A_PIN) == 0) leftEncoderCNT++;
        else                                             leftEncoderCNT--;   
        DL_GPIO_clearInterruptStatus(GPIO_ECD_PORT, GPIO_ECD_LEFT_B_PIN);
    }
    if ((gpioB & GPIO_ECD_RIGH_A_PIN) == GPIO_ECD_RIGH_A_PIN) {
        if (DL_GPIO_readPins(GPIO_ECD_PORT, GPIO_ECD_RIGH_B_PIN) == GPIO_ECD_RIGH_B_PIN) righEncoderCNT++;
        else                                                                            righEncoderCNT--;
        DL_GPIO_clearInterruptStatus(GPIO_ECD_PORT, GPIO_ECD_RIGH_A_PIN);
    }
    if ((gpioB & GPIO_ECD_RIGH_B_PIN) == GPIO_ECD_RIGH_B_PIN) {
        if (DL_GPIO_readPins(GPIO_ECD_PORT, GPIO_ECD_RIGH_A_PIN) == 0) righEncoderCNT++;
        else                                                          righEncoderCNT--;
        DL_GPIO_clearInterruptStatus(GPIO_ECD_PORT, GPIO_ECD_RIGH_B_PIN);
    }
}

void getEncoderCNT(int16_t *left, int16_t *righ) {
    *left = leftEncoderCNT;
    *righ = righEncoderCNT;
}

void qlEncoderCNT(void) {
    leftEncoderCNT = 0;
    righEncoderCNT = 0;
}