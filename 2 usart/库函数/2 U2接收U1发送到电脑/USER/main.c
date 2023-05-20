#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "usart2.h"
#include "Delay.h"

int main(void)
{
	//USART1_Init();
	USART2_Init();
	while(1)
	{
		USART_SendData(USART2 ,0x99);
		Delay_s(1);
		//while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
}

