#include "stm32f10x.h" 

int main(void)
{				 
	RCC->APB2ENR |= 1<<2;			//ʹ��GPIOA��ʱ��
	GPIOA->CRL &= 0x0;				//��տ���PA0�Ķ˿�λ
	GPIOA->CRL |= 0x11111111;		//����PA0Ϊͨ������������ٶ�Ϊ10M
	
	GPIOA->ODR &=(0x00);			//����PA0���Ϊ�͵�ƽ
	
  	while(1)
	{
		
	}	 
} 






