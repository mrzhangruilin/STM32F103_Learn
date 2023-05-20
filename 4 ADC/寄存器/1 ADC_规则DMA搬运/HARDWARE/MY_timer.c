#include "MY_timer.h"


void TIM2_IRQHandler(void)
{
	
	if(TIM2->SR&0X0001)
	{
		
	}
	    
	TIM2->SR &= ~(1<<0);	//清除标志位
}

void TIM2_Init(u16 PSC, u16 ARR)
{
	//使能时钟
	RCC->APB1ENR |= (1<<0);	//TIM2，通用定时器
	
	//预分频
	TIM2->PSC = PSC;	
	
	//自动重装载
	TIM2->ARR = ARR;	
	
	//允许中断
	TIM2->DIER |= (1<<0);
	
	//配置优先级
	MY_NVIC_Init(0,0,TIM2_IRQn,0);
	
	//使能计数器，开始计数
	TIM2->CR1 |= (1<<0);
}

