#include "stm32f10x.h" 
#include "delay.h"
int main(void)
{				
	delay_init(8);
	RCC->APB2ENR |= 1<<2;			//使能GPIOA的时钟
	GPIOA->CRL &= 0x0FFFFFFF;		//清空控制PA7的端口位
	GPIOA->CRL |= 0x10000000;		//配置PA0为通用推挽输出，速度为10M
	
	
  	while(1)
	{
		GPIOA->ODR |=(1<<7);			
		delay_ms(100);
		GPIOA->ODR &=~(1<<7);
		delay_ms(100);		
	}	 
} 






