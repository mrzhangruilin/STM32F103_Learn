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

