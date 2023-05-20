#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"
#include "usart.h"


int main(void)
{			
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化 
	uart_init(72,9600);	 //串口初始化为9600
	
  	while(1)
	{
		printf("hello world\n");
		delay_ms(1000);
	}	 
} 






