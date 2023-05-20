#include "bsp_i2c.h"


void IIC_Delay()
{
	delay_us(4);
}	

void IIC_Init(void)		//初始化引脚
{
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRL &= 0x00FFFFFF;
	GPIOB->CRL |= 0x77000000;	//通用开漏输出，PB6-SCL PB7-SDA
	GPIOB->ODR |= 3<<6;			//PB6 PB7给高
}

void IIC_Start(void)	//发送起始位
{
	SCL = 1;		//释放总线
	SDA = 1;
	IIC_Delay();
	SDA = 0;		//SCL高电平期间拉低SDA
	IIC_Delay();
	SCL = 0;		//为了对齐时序
}

void IIC_Stop(void)		//发送结束条件
{
	SCL = 0;
	SDA = 0;
	SCL = 1;		//拉高SCL
	IIC_Delay();	
	SDA = 1;		//在SCL高期间拉高SDA
}

unsigned char IIC_ReadBck(void)	//接收应答
{
	u8 ack;
	SDA = 1;		//释放SDA
	SCL = 1;	
	IIC_Delay();
	ack = PBin(sda);
	SCL = 0;
	SDA = 0;
	return ack;
}

void IIC_SendBck(void)			//发送应答
{
	SCL = 0;
	IIC_Delay();
	SDA = 0;		//给应答
	IIC_Delay();
	SCL = 1;
	IIC_Delay();
	SCL = 0;
}

void IIC_SendByte(unsigned char byte)	//发送一个字节
{
	int i;
	for(i=0; i<8; i++)
	{
		SCL = 0;			//拉低时钟线，允许改变SDA
		if(byte&1<<(7-i)){SDA = 1;}else{SDA = 0;}
		SCL = 1;
		IIC_Delay();
	}
	SCL = 0;			//发送结束，拉低SCL
}

unsigned char IIC_ReadByte()				//从总线上读一个字节
{
	int i;
	unsigned char byte=0;
	SDA = 1;			//释放SDA
	for(i=0; i<8; i++)
	{
		SCL = 1;		//拉高，然后读
		IIC_Delay();
		if(PBin(sda)){byte |= (1<<(7-i));}
		SCL = 0;
		IIC_Delay();
	}
	return byte;
}
	

