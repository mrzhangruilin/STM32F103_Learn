#include "bsp_i2c.h"


void IIC_Delay()
{
	uint8_t udelay = 10;
	__IO uint32_t Delay = udelay * 72 / 8;//(SystemCoreClock / 8U / 1000000U)
  	do
  	{
  	  __NOP();
  	}
  while (Delay --);
}	

void IIC_Init(void)		//初始化引脚
{
	HAL_GPIO_WritePin(I2C_SCL_GPIO_Port , I2C_SCL_Pin , GPIO_PIN_SET);
	HAL_GPIO_WritePin(I2C_SDA_GPIO_Port , I2C_SDA_Pin , GPIO_PIN_SET);
	//已在GPIO.c里配置，这里不再初始化
}

void IIC_Start(void)	//发送起始位
{
	SCL_H;		//释放总线
	SDA_H;
	IIC_Delay();
	SDA_L;		//SCL高电平期间拉低SDA
	IIC_Delay();
	SCL_L;		//为了对齐时序
}

void IIC_Stop(void)		//发送结束条件
{
	SCL_L;
	SDA_L;
	SCL_H;		//拉高SCL
	IIC_Delay();	
	SDA_H;		//在SCL高期间拉高SDA
}

unsigned char IIC_ReadBck(void)	//接收应答
{
	uint8_t ack;
	SDA_H;		//释放SDA
	SCL_H;	
	IIC_Delay();
	ack = SDA_Read;
	SCL_L;
	SDA_L;
	return ack;
}

void IIC_SendBck(void)			//发送应答
{
	SCL_L;
	IIC_Delay();
	SDA_L;		//给应答
	IIC_Delay();
	SCL_H;
	IIC_Delay();
	SCL_L;
}

void IIC_SendByte(unsigned char byte)	//发送一个字节
{
	int i;
	for(i=0; i<8; i++)
	{
		SCL_L;			//拉低时钟线，允许改变SDA
		if(byte&1<<(7-i)){SDA_H;}else{SDA_L;}
		SCL_H;
		IIC_Delay();
	}
	SCL_L;			//发送结束，拉低SCL
}

unsigned char IIC_ReadByte()				//从总线上读一个字节
{
	int i;
	unsigned char byte=0;
	SDA_H;			//释放SDA
	for(i=0; i<8; i++)
	{
		SCL_H;		//拉高，然后读
		IIC_Delay();
		if(SDA_Read){byte |= (1<<(7-i));}
		SCL_L;
		IIC_Delay();
	}
	return byte;
}
	

