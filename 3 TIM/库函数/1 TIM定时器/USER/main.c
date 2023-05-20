#include "stm32f10x.h"                  // Device header

#include "delay.h"
#include "sys.h"

#include "bsp_usart.h"
#include "bsp_tim.h"




int main(void)
{
	//SystemInit();
	
	Stm32_Clock_Init(9);
	USART1_Init();
	TIM2_TimBaseInit();
	while(1)
	{
		printf("%d" , TIM_GetCounter(TIM2));
		Delay_ms(500);
	}
}

