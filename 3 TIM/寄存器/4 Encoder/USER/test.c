/*
	PB13	TIM1-CH1
	PB14	TIM1-CH2
*/

#include "stm32f10x.h" 
#include "stdio.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "bsp_timer.h"

int main(void)
{				 
	Stm32_Clock_Init(9);
	Delay_Init(72);
	Usart1_Init(72,115200);
	TIM1_Encoder_Init();
	
	while(1)
	{
		printf("%d\r\n" , TIM1_Encoder_Get());
		Delay_ms(1000);
	}	 
} 






