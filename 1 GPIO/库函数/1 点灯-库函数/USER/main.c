#include "stm32f10x.h"                  // Device header


int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;							//通用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	//PIN0/1/2/3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//输出速度最大50Mhz
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA , GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);		//将PIN0/1/2/3置低电平
	while(1)
	{
		
	}
}

