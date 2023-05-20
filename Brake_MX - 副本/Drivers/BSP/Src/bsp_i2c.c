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

void IIC_Init(void)		//��ʼ������
{
	HAL_GPIO_WritePin(I2C_SCL_GPIO_Port , I2C_SCL_Pin , GPIO_PIN_SET);
	HAL_GPIO_WritePin(I2C_SDA_GPIO_Port , I2C_SDA_Pin , GPIO_PIN_SET);
	//����GPIO.c�����ã����ﲻ�ٳ�ʼ��
}

void IIC_Start(void)	//������ʼλ
{
	SCL_H;		//�ͷ�����
	SDA_H;
	IIC_Delay();
	SDA_L;		//SCL�ߵ�ƽ�ڼ�����SDA
	IIC_Delay();
	SCL_L;		//Ϊ�˶���ʱ��
}

void IIC_Stop(void)		//���ͽ�������
{
	SCL_L;
	SDA_L;
	SCL_H;		//����SCL
	IIC_Delay();	
	SDA_H;		//��SCL���ڼ�����SDA
}

unsigned char IIC_ReadBck(void)	//����Ӧ��
{
	uint8_t ack;
	SDA_H;		//�ͷ�SDA
	SCL_H;	
	IIC_Delay();
	ack = SDA_Read;
	SCL_L;
	SDA_L;
	return ack;
}

void IIC_SendBck(void)			//����Ӧ��
{
	SCL_L;
	IIC_Delay();
	SDA_L;		//��Ӧ��
	IIC_Delay();
	SCL_H;
	IIC_Delay();
	SCL_L;
}

void IIC_SendByte(unsigned char byte)	//����һ���ֽ�
{
	int i;
	for(i=0; i<8; i++)
	{
		SCL_L;			//����ʱ���ߣ�����ı�SDA
		if(byte&1<<(7-i)){SDA_H;}else{SDA_L;}
		SCL_H;
		IIC_Delay();
	}
	SCL_L;			//���ͽ���������SCL
}

unsigned char IIC_ReadByte()				//�������϶�һ���ֽ�
{
	int i;
	unsigned char byte=0;
	SDA_H;			//�ͷ�SDA
	for(i=0; i<8; i++)
	{
		SCL_H;		//���ߣ�Ȼ���
		IIC_Delay();
		if(SDA_Read){byte |= (1<<(7-i));}
		SCL_L;
		IIC_Delay();
	}
	return byte;
}
	

