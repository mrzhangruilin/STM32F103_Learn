#include "MY_LED.h"

void MY_LED_Init(void)
{
	RCC->APB2ENR |= 1<<2;			//ʹ��GPIOA��ʱ��
	GPIOA->CRL &= 0xFFFFFFF0;		//��տ���PA0��PA1��PA2��PA3�Ķ˿�λ
	GPIOA->CRL |= 0x00001111;		//����PA0��PA1��PA2��PA3Ϊͨ������������ٶ�Ϊ10M
	GPIOA->ODR |=(0xF);			//��ʼ��Ϊ�ߵ�ƽ
}
