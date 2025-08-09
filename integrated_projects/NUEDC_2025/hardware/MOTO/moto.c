#include "moto.h"
void Moto_Init(void) {
    
}
// 输入的速度值应该在范围[-999,999]
void Moto_SetSpeed(int left, int righ) {
    if (left >= 0) {
        DL_GPIO_clearPins(GPIO_LEFT_DIR_PORT, GPIO_LEFT_DIR_IN1_PIN);
        DL_GPIO_setPins(GPIO_LEFT_DIR_PORT, GPIO_LEFT_DIR_IN2_PIN);
    } else {
        left = -left;
        DL_GPIO_setPins(GPIO_LEFT_DIR_PORT, GPIO_LEFT_DIR_IN1_PIN);
        DL_GPIO_clearPins(GPIO_LEFT_DIR_PORT, GPIO_LEFT_DIR_IN2_PIN);
    }
    if (righ >= 0) {
        DL_GPIO_clearPins(GPIO_RIGHT_DIR_PORT, GPIO_RIGHT_DIR_IN3_PIN);
        DL_GPIO_setPins(GPIO_RIGHT_DIR_PORT, GPIO_RIGHT_DIR_IN4_PIN);
    } else {
        righ = -righ;
        DL_GPIO_setPins(GPIO_RIGHT_DIR_PORT, GPIO_RIGHT_DIR_IN3_PIN);
        DL_GPIO_clearPins(GPIO_RIGHT_DIR_PORT, GPIO_RIGHT_DIR_IN4_PIN);
    }
    DL_Timer_setCaptureCompareValue(PWM_MOTO_INST, left, GPIO_PWM_MOTO_C0_IDX);
    DL_Timer_setCaptureCompareValue(PWM_MOTO_INST, righ, GPIO_PWM_MOTO_C1_IDX);
}

void Moto_start(void) {
    DL_Timer_startCounter(PWM_MOTO_INST);
}

void Moto_Stop(void) {
    DL_Timer_startCounter(PWM_MOTO_INST);
}

void Moto_Brake(void) {
    DL_GPIO_setPins(GPIO_LEFT_DIR_PORT, GPIO_LEFT_DIR_IN1_PIN);
    DL_GPIO_setPins(GPIO_LEFT_DIR_PORT, GPIO_LEFT_DIR_IN2_PIN);
    DL_GPIO_setPins(GPIO_RIGHT_DIR_PORT, GPIO_RIGHT_DIR_IN3_PIN);
    DL_GPIO_setPins(GPIO_RIGHT_DIR_PORT, GPIO_RIGHT_DIR_IN4_PIN);
}