#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "delay.h"
int main(void)
{
	USART1_Init();
	while(1)
	{
		printf("hello world\n");
		Delay_ms(500);
	}
}

