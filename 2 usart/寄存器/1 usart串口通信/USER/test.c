#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"
#include "usart.h"


int main(void)
{			
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ�� 
	uart_init(72,9600);	 //���ڳ�ʼ��Ϊ9600
	
  	while(1)
	{
		printf("hello world\n");
		delay_ms(1000);
	}	 
} 






