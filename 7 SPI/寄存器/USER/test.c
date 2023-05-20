#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "bsp_rc522.h"
#include "usart.h"

unsigned char g_ucTempbuf[4]; 
//SPI1
//SPI_RST	PA0		通用推挽
//SPI_NSS	PA4		通用推挽		手动控制片选
//SPI_CLK	PA5		推挽复用
//SPI_MISO	PA6		带上拉输入
//SPI_MOSI	PA7		推挽复用


int main(void)
{				 
	u8 status;
	
	Stm32_Clock_Init(9);
	delay_init(72);
	uart_init(72,9600);
	RC522_Init();

	printf("初始化成功\n");
  	while(1)
	{
		
		status = RC522_PcdRequest(PICC_REQALL , g_ucTempbuf);
		if(status!=MI_OK)continue;
		printf("防冲撞");
		status = RC522_PcdAnticoll(g_ucTempbuf);		//防冲撞
		if(status!=MI_OK)continue;
		
		printf("%d %d %d %d\n" , g_ucTempbuf[0] , g_ucTempbuf[1] , g_ucTempbuf[2] , g_ucTempbuf[3]);
		
		RC522_PcdHalt();   //命令卡片进入休眠状态
	}	                              
} 







