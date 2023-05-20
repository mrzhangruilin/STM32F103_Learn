#include "bsp_ldc1614.h"

static uint8_t default_addr;

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

uint8_t LDC1614_Init(void)
{
	uint8_t retVal=1;
	u8 ErrCount = 0;
	

	
	ADDR(LOW);
	default_addr = EVM_DEFAULT_I2CADDR;
	SD(LOW);
	LDC1614_Write(default_addr,LDC13xx16xx_CMD_RESET_DEVICE,0x8000);	
	Delay_ms(10);
	
	do
	{
		if (ErrCount++ > 50)
		{
			return 0;
		}
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH0,0xFFFF); // 4 clock periods
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH1,0xFFFF);
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH2,0xFFFF);
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH3,0xFFFF);
		
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_OFFSET_CH0,0x0000);    //补偿值
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_OFFSET_CH1,0x0000);
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_OFFSET_CH2,0x0000);
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_OFFSET_CH3,0x0000);
		
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH0,0x0014); // 1 clock period
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH1,0x0014);
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH2,0x0014);
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH3,0x0014);
		
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH0,0x02); // 2分频
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH1,0x02);
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH2,0x02);
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH3,0x02);
			
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_STATUS,0x0001); // report only DRDYs to INT
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_CONFIG,0x1401); // CLKIN pin1281
			
			
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_MUX_CONFIG,0x820C); // ch0, ch1,ch2,ch3-> Wipro for 4 ch
		
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_SYSTEM_CLOCK_CONFIG,0x0200); // default, divide by 2
		
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH0,0x9000); //
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH1,0x9000); //
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH2,0x0000); //
		retVal &= LDC1614_Write(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH3,0x0000); //
		
	}while(retVal==0);
	
	return 1;
}

void LDC1614_GetData(uint16_t allData[8])
{
	uint8_t retVal;
	do
	{
		retVal = 1;
		retVal &= LDC1614_Read(default_addr,LDC13xx16xx_CMD_DATA_MSB_CH0,&allData[0]);
		retVal &= LDC1614_Read(default_addr,LDC13xx16xx_CMD_DATA_LSB_CH0,&allData[1]);
		
		retVal &= LDC1614_Read(default_addr,LDC13xx16xx_CMD_DATA_MSB_CH1,&allData[2]);
		retVal &= LDC1614_Read(default_addr,LDC13xx16xx_CMD_DATA_LSB_CH1,&allData[3]);
			
		retVal &= LDC1614_Read(default_addr,LDC13xx16xx_CMD_DATA_MSB_CH2,&allData[4]);
		retVal &= LDC1614_Read(default_addr,LDC13xx16xx_CMD_DATA_LSB_CH2,&allData[5]);
			
		retVal &= LDC1614_Read(default_addr,LDC13xx16xx_CMD_DATA_MSB_CH3,&allData[6]);
		retVal &= LDC1614_Read(default_addr,LDC13xx16xx_CMD_DATA_LSB_CH3,&allData[7]);
		
	}while( retVal == 0);
}

uint8_t LDC1614_Read(u8 SlaveAddress, u8 reg_add,u16 *Read)	//读寄存器值
{
	u8 Dat_L = 0;
	u8 Dat_H = 0;
	
	
	IIC_Start();
	IIC_SendByte(SlaveAddress << 1);
	if(IIC_ReadBck() == 1){return 0;}
	
	IIC_SendByte(reg_add);
	if(IIC_ReadBck() == 1){return 0;}
	
	IIC_Start();
	IIC_SendByte((SlaveAddress << 1)+1);
	if(IIC_ReadBck() == 1){return 0;}
	
	Dat_H = IIC_ReadByte();
	IIC_SendBck();
	Dat_L = IIC_ReadByte();
	//不给应答
	
	IIC_Stop();
	*Read = ((Dat_H<<8) | Dat_L);
	return 1;
}

uint8_t LDC1614_Write(u8 SlaveAddress, u8 REG_Address,uint16_t REG_data)
{
	u8 buffer[2];
	buffer[0] = (REG_data >> 8);
	buffer[1] = (u8)(REG_data&0x00ff);
	
	IIC_Start();
	IIC_SendByte(SlaveAddress<<1);
	if(IIC_ReadBck() == 1){return 0;}
	
	IIC_SendByte(REG_Address);
	if(IIC_ReadBck() == 1){return 0;}
	
	IIC_SendByte(buffer[0]);
	if(IIC_ReadBck() == 1){return 0;}
	
	IIC_SendByte(buffer[1]);
	if(IIC_ReadBck() == 1){return 0;}
	
	IIC_Stop();
	
	return 1;
}
