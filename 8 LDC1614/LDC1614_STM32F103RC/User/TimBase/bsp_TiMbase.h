#ifndef TIME_TEST_H
#define TIME_TEST_H


#include "stm32f10x.h"
extern volatile u32 time;

/********************通用定时器 TIMx,x[2,3,4,5]参数定义************/

#define             macTIMx                                TIM2
#define             macTIM_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define             macTIM_CLK                             RCC_APB1Periph_TIM2
#define             macTIM_IRQ                             TIM2_IRQn
#define             macTIM_INT_FUN                         TIM2_IRQHandler

//#define             macTIMx                                TIM3
//#define             macTIM_APBxClock_FUN                   RCC_APB1PeriphClockCmd
//#define             macTIM_CLK                             RCC_APB1Periph_TIM3
//#define             macTIM_IRQ                             TIM3_IRQn
//#define             macTIM_INT_FUN                         TIM3_IRQHandler

/**************************函数声明********************************/
static void               TIMx_NVIC_Configuration                   (void);
static void               TIMx_Configuration                        (void);
			 void 							TIMx_Init                                 (void);

#endif	/* TIME_TEST_H */


