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


/*
	CH1通道，PA0口输出
*/
void TIM2_PWM_Init(void)
{
	RCC->APB1ENR |= (1<<0);	//使能TIM2
	RCC->APB2ENR |= (1<<2);	//使能GPIOA
	
	GPIOA->CRL &= 0xFFFFFFF0;//清除一下
	GPIOA->CRL |= (0xB<<0);	//推挽复用输出
	GPIOA->ODR |= (1<<0);	//给高电平初始
	
	TIM2->PSC = 7200;		//得到10000Hz
	TIM2->ARR = 200;			
	
	TIM2->CCMR1 |= (7<<4);	//PWM模式2
	TIM2->CCMR1 |= (1<<3); 	//CH1预装载使能
	TIM2->CCER |= (1<<0);	//输出使能

	
	TIM2->CR1 |= (1<<7);   	//ARPE使能 
	TIM2->CR1 |= (1<<0);	//使能计数器
}

