

#include "include.h"
uint16_t Buffer[8]={0};
uint16_t last_Buffer[4]={0};
int main(void)
{
	int i = 0;
	uint8_t retVal=0;
	/* USART1 配置模式为 115200 8-N-1，中断接收 */
	USART1_Init();   
	SysTick_Init();
	printf ("\r\n欢迎来到星林科技\r\n");
	Delay_ms(1000);
	for(i = 0;i <2;i++)			   
	{
			printf ("Next\r\n");
			Delay_ms(500); 
	}	
	printf("\r\n LDC1614 模块测试 \r\n");	
	ADDR_SD_Init();
	I2C_INIT();
	do					//LDC1314初始化
	{
		retVal = 1;
		retVal = InitLDC1314();
		printf ("LDC1614 Init Success.\r\n");
	}while (retVal!= 1)	;	 
	while(1)
	{
		evm_processDRDY(Buffer);
		printf( "CH0:%d  \r",Buffer[0]*65536+Buffer[1]);
		printf( "CH1:%d  \r",Buffer[2]*65536+Buffer[3]);
		printf( "CH2:%d  \r",Buffer[4]*65536+Buffer[5]);
		printf( "CH3:%d  \r\n",Buffer[6]*65536+Buffer[7]);
	 Delay_ms(1000);
	}
 
}

