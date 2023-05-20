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

void TIM2_PWM_Init()
{
	//使能时钟
	RCC->APB1ENR |= (1<<0);	//TIM2，通用定时器
	RCC->APB2ENR |= (1<<2);	//使能GPIOA
	GPIOA->CRL &= 0xFFFFFF00;//清除一下
	GPIOA->CRL |= (0xBB<<0);	//推挽复用输出
	GPIOA->ODR |= (0xF<<0);	//给高电平初始
	
	//预分频
	TIM2->PSC = 7200-1;		//得到10kHz	
	TIM2->ARR = 200;		//20ms的时基脉冲	
	TIM2->CCMR1 |= (6<<4);	//PWM模式1，通道1
	TIM2->CCMR1 |= (7<<12);	//PWM模式1，通道2
	TIM2->CCER |= (1<<0);	//输出比较使能，通道1
	TIM2->CCER |= (1<<4);	//输出比较使能，通道2
	
	
	//TIM2->CCMR1 |= (1<<3); //CH1预装载使能//太高级，不考虑溢出，不用
	//TIM2->CR1 |= (1<<7);   	//ARPE使能，TIMx_ARR寄存器被装入缓冲器，好像也不用这个
	
	//使能计数器，开始计数
	TIM2->CR1 |= (1<<0);
}
