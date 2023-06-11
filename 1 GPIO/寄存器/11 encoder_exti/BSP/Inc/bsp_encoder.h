#ifndef _BSP_ENCODER_H__
#define _BSP_ENCODER_H__

#include "stm32f10x.h"
#include "sys.h"

void Encoder_Init(void);
int16_t Encoder_Get(void);


#endif


