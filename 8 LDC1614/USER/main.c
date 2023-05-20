#include "stm32f10x.h"                  // Device header
#include "bsp_usart.h"
#include "sys.h"
#include "delay.h"
#include "bsp_ldc1614.h"

uint16_t Buffer[8]={0};

int main(void)
{
	u8 retVal;
	u16 dat = 0;
	
	Stm32_Clock_Init(9);
	USART1_Init();
	ADDR_SD_Init();
	IIC_Init();
	
	do					//LDC1314初始化
	{
		retVal = LDC1614_Init();
	}while (retVal==0)	;			//检测初始化成功	 
	
	
	while(1)
	{

		LDC1614_GetData(Buffer);
		printf( "CH0:%d  \r",Buffer[0]*65536+Buffer[1]);
		printf( "CH1:%d  \r",Buffer[2]*65536+Buffer[3]);
		printf( "CH2:%d  \r",Buffer[4]*65536+Buffer[5]);
		printf( "CH3:%d  \r",Buffer[6]*65536+Buffer[7]);
		Delay_ms(1000);
	}
}

