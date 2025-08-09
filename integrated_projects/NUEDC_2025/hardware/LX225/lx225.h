#ifndef __LX225_H
#define __LX225_H
#include "ti_msp_dl_config.h"
#include <stdint.h>

typedef struct {
    uint16_t CommandIndex;
    uint16_t DataLen;
} ServoCommand;

void LX225_SetServoAngle(uint8_t ServoID, float Angle, uint16_t Time);
void LX225_SetServoID(uint8_t ServoID, uint8_t NewID);

#endif