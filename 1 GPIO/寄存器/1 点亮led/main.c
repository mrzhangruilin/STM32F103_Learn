#include "stm32f10x.h"


int main(void)
{
	/*
	RCC->APB2ENR |= 1<<2;			//使能GPIOA的时钟
	GPIOA->CRL &= 0xFFFFFFF0;		//清空控制PA0的端口位
	GPIOA->CRL |= 0x00000001;		//配置PA0为通用推挽输出，速度为10M
	GPIOA->ODR |=(0<<0);			//配置PA0输出为低电平
	*/
	*(unsigned int*)(0x40021000+0x18)|= 1<<2;		//使能GPIOA
	*(unsigned int*)(0x40010800+0x00)&=0xFFFFFF00;	//清空PA0的端口位
	*(unsigned int*)(0x40010800+0x00)|=0x11;		//PA0推挽输出，速度10M
	*(unsigned int*)(0x40010800+0x0C)&=~(3<<0);		//输出低电平

	while(1);
	
}

	

