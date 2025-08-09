#ifndef __CTRL_H
#define __CTRL_H
#include "ti_msp_dl_config.h"
typedef struct {
    bool pin[8];
} trailing_data_t;
#define BLACK_BLOB ((bool)1)
#define WHITE_BLOB ((bool)0)
void Ctrl_Init(void);
void Ctrl_Run(void);
void Ctrl_Stop(void);
void readTrailingPins(trailing_data_t *tp);
uint8_t cntBlackBlobs(trailing_data_t *tp);
#endif