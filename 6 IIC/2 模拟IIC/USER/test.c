#include "stm32f10x.h" 


#include "usart.h"
#include "stdio.h"
#include "bsp_at24c02.h"


int main(void)
{				 
	unsigned char wdata[8] = {0x19,0x12,0x16,0x18,0x16,0x32,0x48,0x64};
	unsigned char rdata[8] = {0};
	Stm32_Clock_Init(9);
	delay_init(72);
	uart_init(72,115200);
	IIC_Init();
	
	AT24C02_WriteByte(0x50 , 0x00 , wdata , 8);
	
	AT24C02_ReadByte(0x50 , 0x00 , rdata , 8);
	printf("0x00:%2x\r\n0x01:%2x\r\n0x02:%2x\r\n0x03:%2x\r\n", rdata[0] , rdata[1], rdata[2], rdata[3]);


  	while(1)
	{
		
	}	 
} 






