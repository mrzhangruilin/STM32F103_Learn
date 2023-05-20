#include "stm32f10x.h"                  // Device header
#include "delay.h"

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			//通用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	
	while(1)
	{
		GPIO_Write(GPIOA , 0x0001);
		Delay_ms(100);
		GPIO_Write(GPIOA , 0x0002);
		Delay_ms(100);
		GPIO_Write(GPIOA , 0x0004);
		Delay_ms(100);
		GPIO_Write(GPIOA , 0x0008);
		Delay_ms(100);
	}
}

