#include "stm32f10x.h"                  // Device header

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;		//�ṹ�壬��������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);		//ʱ��ʹ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//PA0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//����������50Mhz
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	while(1)
	{
		
	}
}

