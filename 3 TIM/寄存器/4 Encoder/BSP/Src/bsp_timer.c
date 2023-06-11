#include "bsp_timer.h"


void TIM2_IRQHandler(void)
{
	
	if(TIM2->SR&0X0001)
	{
		
	}
	    
	TIM2->SR &= ~(1<<0);	//�����־λ
}

void TIM2_Init(u16 PSC, u16 ARR)
{
	//ʹ��ʱ��
	RCC->APB1ENR |= (1<<0);	//TIM2��ͨ�ö�ʱ��
	
	//Ԥ��Ƶ
	TIM2->PSC = PSC;	
	
	//�Զ���װ��
	TIM2->ARR = ARR;	
	
	//�����ж�
	TIM2->DIER |= (1<<0);
	
	//�������ȼ�
	MY_NVIC_Init(0,0,TIM2_IRQn,0);
	
	//ʹ�ܼ���������ʼ����
	TIM2->CR1 |= (1<<0);
}

//��������ʼ��
void TIM1_Encoder_Init(void)
{
	//ʹ��ʱ��
	RCC->APB2ENR |= (1<<11|1<<3);
	
	//PB13	TIM1-CH1N
	//PB14	TIM1-CH2N
	GPIOB->CRH &= 0xF00FFFFF;
	GPIOB->CRH |= 0x08800000;
	GPIOB->ODR |= (1<<13|1<<14);	//������
	
	//�Զ���װ��
	TIM1->ARR = 65535;		//�������
	
	//���ô���Դ
	TIM1->SMCR |= (6<<4|3<<0);	//������һ�����
	
	//����Ƚ�ѡ��
	TIM1->CCMR1 |= (1<<8|1<<0);	//����CC2ӳ�䵽TI2��CC1ӳ�䵽TI1
	
	//����Ƚ�ʹ�ܺͼ���ѡ��
	TIM1->CCER |= (0<<1|0<<5);	//�����࣬ʹ��
	
	//ʹ�ܼ���������ʼ����
	TIM1->CR1 |= (1<<0);
}

uint16_t TIM1_Encoder_Get(void)
{
	return TIM1->CNT;
}
