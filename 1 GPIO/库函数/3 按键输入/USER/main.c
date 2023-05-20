#include "stm32f10x.h"                  // Device header


int main(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//没啥用，填吧
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	while(1)
	{
		if((GPIO_ReadInputData(GPIOA)&0xf<<4) != 0xf<<4)
		{
			GPIO_ResetBits(GPIOA , (~(GPIO_ReadInputData(GPIOA)>>4))&0xf);
		}else
		{
			GPIO_SetBits(GPIOA , GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
		}
		
		/*
		if(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_4) == 0)
		{
			GPIO_ResetBit();
			GPIO_WriteBit(GPIOA , GPIO_Pin_0 , Bit_RESET);
		} 
		if(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_5) == 0)
		{
			GPIO_WriteBit(GPIOA , GPIO_Pin_1 , Bit_RESET);
		} 
		if(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_6) == 0)
		{
			GPIO_WriteBit(GPIOA , GPIO_Pin_2 , Bit_RESET);
		} 
		if(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_7) == 0)
		{
			GPIO_WriteBit(GPIOA , GPIO_Pin_3 , Bit_RESET);
		} 
		GPIO_SetBits(GPIOA , GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
		*/
		
		
		
		
		
	}
}

