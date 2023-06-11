#include "bsp_i2c.h"


void IIC_Delay()
{
	Delay_us(4);
}	

void IIC_Init(void)		//初始化引脚
{
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRL &= 0x00FFFFFF;
	GPIOB->CRL |= 0x77000000;						//通用开漏输出，PB6-SCL PB7-SDA
	GPIOB->ODR |= ((1<<6)|(1<<7));			//PB6 PB7给高
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
	uint8_t ack,i=0;
	SDA_H;		//释放SDA
	SCL_H;	
	IIC_Delay();
	ack = SDA_Read;
	while(ack)
	{
		ack = SDA_Read;
		i++;
		if(i>200)
		{
			return 1;
		}
	}
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
	

