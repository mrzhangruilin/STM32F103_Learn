#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"
#include "bsp_encoder.h"
#include "usart.h"

extern int16_t g_Encoder_cnt;

int main(void)
{				 
	Stm32_Clock_Init(9);
	Delay_Init(72);
	Usart1_Init(72,115200);
	Encoder_Init();

	while(1)
	{
		printf("%d\r\n" , g_Encoder_cnt);
	}	 
} 






