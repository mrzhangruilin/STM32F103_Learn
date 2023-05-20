#ifndef _MY_TIMER_H__
#define _MY_TIMER_H__

#include "stm32f10x.h" 
#include "sys.h"

void TIM2_Init(u16 PSC, u16 ARR);
void TIM2_PWM_Init(void);

#endif


