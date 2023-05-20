#include "stm32f10x.h" 
#include "usart.h"
#include "MY_LED.H"
#include "delay.h"
#include "MY_timer.h"




int main(void)
{				 
	Stm32_Clock_Init(9);	//72Mhz
	uart_init(72,9600);		
	MY_LED_Init();
	delay_init(72);
	TIM2_Init(7199,5000);
	
  	while(1)
	{
		
	}	 
} 






