#include "stm32f10x.h" 

int main(void)
{		
	RCC->APB2ENR |= (1<<2);		//ÖÃÒ»
	RCC->APB2ENR |= (1<<14);
	RCC->APB2ENR &= ~(1<<2);	//ÇåÁã
  	while(1)
	{
		
	}	 
} 






