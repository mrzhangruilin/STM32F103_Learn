#include "stm32f10x.h" 

int main(void)
{		
	RCC->APB2ENR |= (1<<2);		//��һ
	RCC->APB2ENR |= (1<<14);
	RCC->APB2ENR &= ~(1<<2);	//����
  	while(1)
	{
		
	}	 
} 






