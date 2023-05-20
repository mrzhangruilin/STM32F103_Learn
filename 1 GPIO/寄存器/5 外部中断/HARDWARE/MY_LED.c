#include "MY_LED.h"

void MY_LED_Init(void)
{
	RCC->APB2ENR |= 1<<2;			//使能GPIOA的时钟
	GPIOA->CRL &= 0xFFFFFFF0;		//清空控制PA0、PA1、PA2、PA3的端口位
	GPIOA->CRL |= 0x00001111;		//配置PA0、PA1、PA2、PA3为通用推挽输出，速度为10M
	GPIOA->ODR |=(0xF);			//初始化为高电平
}
