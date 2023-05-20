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


/*
	CH1ͨ����PA0�����
*/
void TIM2_PWM_Init(void)
{
	RCC->APB1ENR |= (1<<0);	//ʹ��TIM2
	RCC->APB2ENR |= (1<<2);	//ʹ��GPIOA
	
	GPIOA->CRL &= 0xFFFFFFF0;//���һ��
	GPIOA->CRL |= (0xB<<0);	//���츴�����
	GPIOA->ODR |= (1<<0);	//���ߵ�ƽ��ʼ
	
	TIM2->PSC = 7200;		//�õ�10000Hz
	TIM2->ARR = 200;			
	
	TIM2->CCMR1 |= (7<<4);	//PWMģʽ2
	TIM2->CCMR1 |= (1<<3); 	//CH1Ԥװ��ʹ��
	TIM2->CCER |= (1<<0);	//���ʹ��

	
	TIM2->CR1 |= (1<<7);   	//ARPEʹ�� 
	TIM2->CR1 |= (1<<0);	//ʹ�ܼ�����
}

