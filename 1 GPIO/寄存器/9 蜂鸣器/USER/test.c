#include "stm32f10x.h" 
#include "delay.h"
int main(void)
{				
	delay_init(8);
	RCC->APB2ENR |= 1<<2;			//ʹ��GPIOA��ʱ��
	GPIOA->CRL &= 0x0FFFFFFF;		//��տ���PA7�Ķ˿�λ
	GPIOA->CRL |= 0x10000000;		//����PA0Ϊͨ������������ٶ�Ϊ10M
	
	
  	while(1)
	{
		GPIOA->ODR |=(1<<7);			
		delay_ms(100);
		GPIOA->ODR &=~(1<<7);
		delay_ms(100);		
	}	 
} 






