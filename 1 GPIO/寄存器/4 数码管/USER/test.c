#include "stm32f10x.h" 

int main(void)
{				 
	RCC->APB2ENR |= 1<<2;			//使能GPIOA的时钟
	GPIOA->CRL &= 0x0;				//清空控制PA0的端口位
	GPIOA->CRL |= 0x11111111;		//配置PA0为通用推挽输出，速度为10M
	
	GPIOA->ODR &=(0x00);			//配置PA0输出为低电平
	
  	while(1)
	{
		
	}	 
} 






