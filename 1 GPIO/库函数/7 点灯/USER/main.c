#include "stm32f10x.h"                  // Device header

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;		//结构体，变量类型
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);		//时钟使能
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//PA0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//输出速率最高50Mhz
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	while(1)
	{
		
	}
}

