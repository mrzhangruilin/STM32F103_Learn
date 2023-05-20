#include "stm32f10x.h"                  // Device header
#include "delay.h"

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetFlagStatus(EXTI_Line5) == SET)
	{
		Delay_ms(5);	//�������������µ�����
		while(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_5) == RESET);	//�������ȴ������ɿ�
		Delay_ms(5);	//�����������ɿ�������
		GPIO_WriteBit(GPIOA , GPIO_Pin_1 , (BitAction)!GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_1));
		EXTI_ClearFlag(EXTI_Line5);
	}
	if(EXTI_GetFlagStatus(EXTI_Line6) == SET)
	{
		Delay_ms(5);	//�������������µ�����
		while(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_6) == RESET);	//�������ȴ������ɿ�
		Delay_ms(5);	//�����������ɿ�������
		GPIO_WriteBit(GPIOA , GPIO_Pin_2 , (BitAction)!GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_2));
		EXTI_ClearFlag(EXTI_Line6);
	}
	if(EXTI_GetFlagStatus(EXTI_Line7) == SET)
	{
		Delay_ms(5);	//�������������µ�����
		while(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_7) == RESET);	//�������ȴ������ɿ�
		Delay_ms(5);	//�����������ɿ�������
		GPIO_WriteBit(GPIOA , GPIO_Pin_3 , (BitAction)!GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_3));
		EXTI_ClearFlag(EXTI_Line7);
	}
	
}

void EXTI4_IRQHandler(void)
{
	Delay_ms(5);	//�������������µ�����
	while(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_4) == RESET);	//�������ȴ������ɿ�
	Delay_ms(5);	//�����������ɿ�������
	GPIO_WriteBit(GPIOA , GPIO_Pin_0 , (BitAction)!GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_0));
	EXTI_ClearFlag(EXTI_Line4);
}

void GPIOA_init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//ûɶ�ã����
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA , GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
}


int main(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	GPIOA_init();
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7;	//PA4/5/6/7������4/5/6/7��
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;											//ʹ���ⲿ�ж�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;									//�����ж϶������¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;								//�½��ش���
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;							//��ռ���ȼ���balabala���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	while(1)
	{

	}
}

