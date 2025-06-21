#ifndef __TWO_MOTOR_DRIVER_H
#define __TWO_MOTOR_DRIVER_H

#include "ti_msp_dl_config.h"
#include <stdint.h>

void MotorInit(void);

float MotorSpeedClamp(float val, float min, float max);
void SetMotorSpeed(float percent_l, float percent_r);
void StopMotor(void);
void BrakeMotor(void);

#endif // #ifndef __TWO_MOTOR_DRIVER_H