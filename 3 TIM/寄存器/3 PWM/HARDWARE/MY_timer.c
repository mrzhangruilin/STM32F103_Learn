#include "MY_timer.h"


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

void TIM2_PWM_Init()
{
	//ʹ��ʱ��
	RCC->APB1ENR |= (1<<0);	//TIM2��ͨ�ö�ʱ��
	RCC->APB2ENR |= (1<<2);	//ʹ��GPIOA
	GPIOA->CRL &= 0xFFFFFF00;//���һ��
	GPIOA->CRL |= (0xBB<<0);	//���츴�����
	GPIOA->ODR |= (0xF<<0);	//���ߵ�ƽ��ʼ
	
	//Ԥ��Ƶ
	TIM2->PSC = 7200-1;		//�õ�10kHz	
	TIM2->ARR = 200;		//20ms��ʱ������	
	TIM2->CCMR1 |= (6<<4);	//PWMģʽ1��ͨ��1
	TIM2->CCMR1 |= (7<<12);	//PWMģʽ1��ͨ��2
	TIM2->CCER |= (1<<0);	//����Ƚ�ʹ�ܣ�ͨ��1
	TIM2->CCER |= (1<<4);	//����Ƚ�ʹ�ܣ�ͨ��2
	
	
	//TIM2->CCMR1 |= (1<<3); //CH1Ԥװ��ʹ��//̫�߼������������������
	//TIM2->CR1 |= (1<<7);   	//ARPEʹ�ܣ�TIMx_ARR�Ĵ�����װ�뻺����������Ҳ�������
	
	//ʹ�ܼ���������ʼ����
	TIM2->CR1 |= (1<<0);
}
