#include "stm32f10x.h"


int main(void)
{
	/*
	RCC->APB2ENR |= 1<<2;			//ʹ��GPIOA��ʱ��
	GPIOA->CRL &= 0xFFFFFFF0;		//��տ���PA0�Ķ˿�λ
	GPIOA->CRL |= 0x00000001;		//����PA0Ϊͨ������������ٶ�Ϊ10M
	GPIOA->ODR |=(0<<0);			//����PA0���Ϊ�͵�ƽ
	*/
	*(unsigned int*)(0x40021000+0x18)|= 1<<2;		//ʹ��GPIOA
	*(unsigned int*)(0x40010800+0x00)&=0xFFFFFF00;	//���PA0�Ķ˿�λ
	*(unsigned int*)(0x40010800+0x00)|=0x11;		//PA0����������ٶ�10M
	*(unsigned int*)(0x40010800+0x0C)&=~(3<<0);		//����͵�ƽ

	while(1);
	
}

	

