#include "stm32f10x.h" 
#include "MY_LED.h"
#include "sys.h"
#include "delay.h"
/*
uint8_t bit:	λ��0-15
uint8_t out:	�����0-�͵�ƽ��1-�ߵ�ƽ
*/
void MY_PAout(unsigned char bit, unsigned char out)
{
	if(out)
	{//�ߵ�ƽ
		GPIOA->ODR |= (1<<bit);
	}else
	{//�͵�ƽ
		GPIOA->ODR &= ~(1<<bit);
	}
}

/*
uint8_t	   :	���أ�0-�͵�ƽ��1-�ߵ�ƽ
uint8_t bit:	λ��0-15
*/
unsigned char MY_PAin(unsigned char bit)
{
	if(GPIOA->IDR & (1<<bit))
	{
		return 1;
	}else
	{
		return 0;
	}
}

int main(void)
{	

	Stm32_Clock_Init(9);
	delay_init(72);
	MY_LED_Init();
	
	
	
  	while(1)
	{
		MY_PAout(0,!MY_PAin(0));
		delay_ms(100);
	}	 
} 






