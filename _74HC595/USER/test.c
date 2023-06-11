#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"
#include "bsp_74hc595.h"

int main(void)
{				 
	Stm32_Clock_Init(9);
	Delay_Init(72);

	SMG_74HC595_Init();
	
	while(1)
	{
		SMG_74HC595_Display_Int(-1234);
	}	 
} 






