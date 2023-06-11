#include "bsp_timer.h"


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

//编码器初始化
void TIM1_Encoder_Init(void)
{
	//使能时钟
	RCC->APB2ENR |= (1<<11|1<<3);
	
	//PB13	TIM1-CH1N
	//PB14	TIM1-CH2N
	GPIOB->CRH &= 0xF00FFFFF;
	GPIOB->CRH |= 0x08800000;
	GPIOB->ODR |= (1<<13|1<<14);	//给上拉
	
	//自动重装载
	TIM1->ARR = 65535;		//给到最大
	
	//设置触发源
	TIM1->SMCR |= (6<<4|3<<0);	//两个沿一起计数
	
	//捕获比较选择
	TIM1->CCMR1 |= (1<<8|1<<0);	//配置CC2映射到TI2，CC1映射到TI1
	
	//捕获比较使能和极性选择
	TIM1->CCER |= (0<<1|0<<5);	//不反相，使能
	
	//使能计数器，开始计数
	TIM1->CR1 |= (1<<0);
}

uint16_t TIM1_Encoder_Get(void)
{
	return TIM1->CNT;
}
