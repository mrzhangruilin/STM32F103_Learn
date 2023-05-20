#include "stm32f10x.h" 
#include "MY_LED.h"
#include "sys.h"
#include "delay.h"
/*
uint8_t bit:	位，0-15
uint8_t out:	输出，0-低电平，1-高电平
*/
void MY_PAout(unsigned char bit, unsigned char out)
{
	if(out)
	{//高电平
		GPIOA->ODR |= (1<<bit);
	}else
	{//低电平
		GPIOA->ODR &= ~(1<<bit);
	}
}

/*
uint8_t	   :	返回：0-低电平，1-高电平
uint8_t bit:	位，0-15
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






