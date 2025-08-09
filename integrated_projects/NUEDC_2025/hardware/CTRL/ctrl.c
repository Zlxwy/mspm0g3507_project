#include "ctrl.h"
#include "OLED.h"
#include "moto.h"
#include "math.h"
#include "encoder.h"
void Ctrl_Init(void) {
    NVIC_ClearPendingIRQ(TIMER_CTRL_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMER_CTRL_INST_INT_IRQN);
}
void Ctrl_Run(void) {
    DL_Timer_startCounter(TIMER_CTRL_INST);
}
void Ctrl_Stop(void) {
    DL_Timer_stopCounter(TIMER_CTRL_INST);
}
trailing_data_t currTrk;
trailing_data_t prevTrk;
uint32_t GPIO_TRK_PIN[8] = {
    GPIO_TRK_P0_PIN,
    GPIO_TRK_P1_PIN,
    GPIO_TRK_P2_PIN,
    GPIO_TRK_P3_PIN,
    GPIO_TRK_P4_PIN,
    GPIO_TRK_P5_PIN,
    GPIO_TRK_P6_PIN,
    GPIO_TRK_P7_PIN
};
void readTrailingPins(trailing_data_t *tp) {
    for (uint8_t i=0; i<8; i++) {
        if (DL_GPIO_readPins(GPIO_TRK_PORT, GPIO_TRK_PIN[i]) == GPIO_TRK_PIN[i]) {
            tp->pin[i] = BLACK_BLOB;
        } else {
            tp->pin[i] = WHITE_BLOB;
        }
    }
}
uint8_t cntBlackBlobs(trailing_data_t *tp) {
    uint8_t cnt = 0;
    for (uint8_t i=0; i<8; i++) {
        if (tp->pin[i] == BLACK_BLOB) {
            cnt++;
        }
    }
    return cnt;
}
// const float SensorOffset[8] = {-10, -7, -4, -1, +1, +4, +7, +10};
const float SensorOffset[8] = {-38.5, -27.5, -16.5, -5.5, +5.5, +16.5, +27.5, +38.5};
float
    kp = 28,
    ki = 0,
    kd = 32;
float curr_te = 0;
float last_te = 0;
float outp = 0;
float baseSpeed, leftSpeed, rightSpeed;
float 
    kkp = 2.4,
    kki = 0.2,
    kkd = 0.4;
float leftSpeedCurrErr, rightSpeedCurrErr;
float leftSpeedPrevErr, rightSpeedPrevErr;
float leftSpeedInteg, righSpeedInteg;
float leftSpeedDiff, rightSpeedDiff;
// bool hasLostBlackBlob = false;
int32_t leftEncoderSum = 0, rightEncoderSum = 0;
extern uint16_t round_cnt;
int64_t left_encoder_cnt_sum, right_encoder_cnt_sum;
#define PULSE_PER_ROUND  5200
void TIMER_CTRL_INST_IRQHandler(void) {
    switch (DL_Timer_getPendingInterrupt(TIMER_CTRL_INST)) {
        case DL_TIMER_IIDX_LOAD:
            readTrailingPins(&currTrk); // 读一下当前引脚状态
            uint8_t black_num = cntBlackBlobs(&currTrk); // 数一下有多少个

            // if (black_num == 0) hasLostBlackBlob = true;
            // else hasLostBlackBlob = false;

            // if (!hasLostBlackBlob) {
            //     for (uint16_t i=0; i<8; i++) {
            //         if (currTrk.pin[i] == BLACK_BLOB) {
            //             curr_te += SensorOffset[i];
            //         }
            //     }
            //     curr_te = curr_te / black_num;
            //     curr_te = 0.7*last_te + 0.3*curr_te;
            //     outp = kp*curr_te + kd*(curr_te-last_te);
            //     last_te = curr_te;
            //     baseSpeed = 580;
            //     leftSpeed = baseSpeed + outp;
            //     rightSpeed = baseSpeed - outp;
            //     if (leftSpeed < -999) leftSpeed = -999;
            //     else if (leftSpeed > 999) leftSpeed = 999;
            //     if (rightSpeed < -999) rightSpeed = -999;
            //     else if (rightSpeed > 999) rightSpeed = 999;
            // } else {
            //     leftSpeed = 500;
            //     rightSpeed = 300;
            // }
            // Moto_SetSpeed((int)leftSpeed, (int)rightSpeed);


            if (black_num == 0) {// 如果没有找到黑块
                // currTrk = prevTrk; //使用上一次的数据
                for (uint16_t i=0; i<4; i++) currTrk.pin[i] = BLACK_BLOB;
                for (uint16_t i=4; i<8; i++) currTrk.pin[i] = WHITE_BLOB;
            } else { //如果找到黑块
                prevTrk = currTrk; //则更新prevTrk
            }
            black_num = cntBlackBlobs(&currTrk); // 再数一下有多少个黑块

            curr_te = 0;
            for (uint16_t i=0; i<8; i++) {
                if (currTrk.pin[i] == BLACK_BLOB) {
                    curr_te += SensorOffset[i];
                }
            }

            curr_te = (black_num==0)?0:(curr_te/black_num);
            curr_te = 0.7*last_te + 0.3*curr_te;
            outp = kp*curr_te + kd*(curr_te-last_te);
            last_te = curr_te;
            float baseSpeed = 859;
            float leftSpeed = baseSpeed + outp;
            float rightSpeed = baseSpeed - outp;
            // if (leftSpeed < -999) leftSpeed = -999;
            // else if (leftSpeed > 999) leftSpeed = 999;
            // if (rightSpeed < -999) rightSpeed = -999;
            // else if (rightSpeed > 999) rightSpeed = 999;
            if (leftSpeed < 0) leftSpeed = 0;
            if (rightSpeed < 0) rightSpeed = 0;

            int16_t leftEncoder, rightEncoder;
            getEncoderCNT(&leftEncoder, &rightEncoder);
            leftEncoderSum += leftEncoder;
            rightEncoderSum += rightEncoder;
            qlEncoderCNT();
            
            leftSpeedCurrErr = leftSpeed - 350*leftEncoder;
            rightSpeedCurrErr = rightSpeed - 350*rightEncoder;
            leftSpeedInteg += leftSpeedCurrErr; if (leftSpeedInteg > 1000) leftSpeedInteg = 1000; else if (leftSpeedInteg < -1000) leftSpeedInteg = -1000;
            righSpeedInteg += rightSpeedCurrErr; if (righSpeedInteg > 1000) righSpeedInteg = 1000; else if (righSpeedInteg < -1000) righSpeedInteg = -1000;
            leftSpeedDiff = leftSpeedCurrErr - leftSpeedPrevErr;
            rightSpeedDiff = rightSpeedCurrErr - rightSpeedPrevErr;
            leftSpeed = kkp* leftSpeedCurrErr + kki*leftSpeedInteg + kkd*leftSpeedDiff;
            rightSpeed = kkp*rightSpeedCurrErr + kki*righSpeedInteg + kkd*rightSpeedDiff;
            leftSpeedPrevErr = leftSpeedCurrErr;
            rightSpeedPrevErr = rightSpeedCurrErr;

            /*如果所有的编码器之和大于10000了*/
            int64_t all_encoder_cnt_sum = leftEncoderSum + rightEncoderSum;
            if ((all_encoder_cnt_sum/2) > PULSE_PER_ROUND) { // 除以2，如果大于10000个脉冲，说明已经跑完一圈
                leftEncoderSum = rightEncoderSum = 0;
                round_cnt--;
                if (round_cnt == 0) {
                    Ctrl_Stop();
                    Moto_Stop();
                    Moto_Brake();
                    goto jumpend;
                }
            }

            // float speedDiffMax = 500;
            // if (fabs(leftSpeed-rightSpeed)>speedDiffMax) {
            //     if (leftSpeed > rightS   apeed) {
            //         float diff = (leftSpeed-rightSpeed-speedDiffMax)/2;
            //         leftSpeed -= diff;
            //         rightSpeed += diff;
            //     } else {
            //         float diff = (rightSpeed-leftSpeed-speedDiffMax)/2;
            //         leftSpeed += diff;
            //         rightSpeed -= diff;
            //     }
            // }
            Moto_SetSpeed((int)leftSpeed, (int)rightSpeed);



            
            OLED_Printf(0, 9, OLED_6X8, "%1d%1d%1d%1d%1d%1d%1d%1d", currTrk.pin[0], currTrk.pin[1], currTrk.pin[2], currTrk.pin[3], currTrk.pin[4], currTrk.pin[5], currTrk.pin[6], currTrk.pin[7]);
            OLED_Printf(0, 18, OLED_6X8, "BLACK: %d", black_num);
            OLED_Printf(0, 27, OLED_6X8, "%+5d, %+5d", leftEncoder, rightEncoder);
            OLED_Printf(0, 36, OLED_6X8, "%+9d %+9d", leftEncoderSum, rightEncoderSum);
            break;

        default: break;
    }
    jumpend:;
}