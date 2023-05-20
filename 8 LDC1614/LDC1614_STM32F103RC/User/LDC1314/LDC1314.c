//----------------------------------------------------------------------------
//Module	：LDC1314
//Author	：ZL
//Version	：V1.0
//Date		: 2016年10月10日21:02:58
//Platform:STM32F103R8T6 
//Company	：星林科技
//ID			:	https://shop114415195.taobao.com
//QQ      :	2509528710
//----------Xing Lin electronic technology co., LTD---------------------------- 
#include "ldc1314.h"

static uint8_t default_addr;

/***************************************
 * 函数名：ADDR_SD_Init
 * 描述  ：配置LDC用到的I/O口
           ADDR--PB13
					 SD  --PB14
 * 输入  ：无
 * 输出  ：无
 **************************************
 */
void ADDR_SD_Init(void)       //ADDR和SD引脚初始化
{
	
	 GPIO_InitTypeDef GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(EVM_ADDR_RCCEN, ENABLE);
	
   GPIO_InitStructure.GPIO_Pin = ADDR_PIN;	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(EVM_ADDR, &GPIO_InitStructure);
	 GPIO_SetBits(EVM_ADDR,ADDR_PIN);
	RCC_APB2PeriphClockCmd(EVM_SHUTDOWN_RCCEN, ENABLE);
   GPIO_InitStructure.GPIO_Pin = SD_PIN;	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(EVM_SHUTDOWN, &GPIO_InitStructure);
	 GPIO_SetBits(EVM_SHUTDOWN,SD_PIN); 	
}

/***************************************
 * 函数名：InitLDC1314
 * 描述  ：初始化LDC1314
 * 输入  ：无
 * 输出  ：无
 **************************************
 */
uint8_t InitLDC1314(void)
{
	uint8_t retVal=1;
	u8 ErrCount = 0;
	ADDR(LOW);
	default_addr = EVM_DEFAULT_I2CADDR;
	SD(LOW);
	Single_Write(default_addr,LDC13xx16xx_CMD_RESET_DEVICE,0x8000);	
	Delay_ms(10);
	
	do
	{
		if (ErrCount++ > 50)
			{
				return 0;
			}
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH0,0x04d6); // 4 clock periods
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH1,0x04d6);
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH2,0xFFFF);
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH3,0xFFFF);
			
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_OFFSET_CH0,0x0000);    //补偿值
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_OFFSET_CH1,0x0000);
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_OFFSET_CH2,0x0000);
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_OFFSET_CH3,0x0000);
			
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH0,0x0400); // 1 clock period
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH1,0x0400);
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH2,0x0400);
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH3,0x0400);
			
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH0,0x0000); // 1000
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH1,0x0000);
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH2,0x0000);
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH3,0x0000);
			
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_STATUS,0x0001); // report only DRDYs to INT
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_CONFIG,0x0000); // CLKIN pin1281
			
			
	  retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_MUX_CONFIG,0xC20F); // ch0, ch1,ch2,ch3-> Wipro for 4 ch
			
			
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_SYSTEM_CLOCK_CONFIG,0x0200); // default, divide by 2
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH0,0x0000); //
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH1,0x0000); //
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH2,0x0000); //
		retVal &= Single_Write(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH3,0x0000); //
	}while(retVal==0);
	
	return 1;
}
/***************************************
 * 函数名：evm_processDRDY
 * 描述  ：读取寄存器数据
 * 输入  ：无
 * 输出  ：无
 **************************************/
void evm_processDRDY(uint16_t allData[8]) {
	uint8_t retVal;
	do
	{
		retVal = 1;
	  retVal &= Single_Read(default_addr,LDC13xx16xx_CMD_DATA_MSB_CH0,&allData[0]);
	  retVal &= Single_Read(default_addr,LDC13xx16xx_CMD_DATA_LSB_CH0,&allData[1]);
		
	  retVal &= Single_Read(default_addr,LDC13xx16xx_CMD_DATA_MSB_CH1,&allData[2]);
	  retVal &= Single_Read(default_addr,LDC13xx16xx_CMD_DATA_LSB_CH1,&allData[3]);
		
	  retVal &= Single_Read(default_addr,LDC13xx16xx_CMD_DATA_MSB_CH2,&allData[4]);
	  retVal &= Single_Read(default_addr,LDC13xx16xx_CMD_DATA_LSB_CH2,&allData[5]);
		
	  retVal &= Single_Read(default_addr,LDC13xx16xx_CMD_DATA_MSB_CH3,&allData[6]);
	  retVal &= Single_Read(default_addr,LDC13xx16xx_CMD_DATA_LSB_CH3,&allData[7]);
		
		}while( retVal == 0);
}

