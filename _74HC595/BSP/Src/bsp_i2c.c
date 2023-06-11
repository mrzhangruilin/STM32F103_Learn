#include "bsp_i2c.h"


void IIC_Delay()
{
	Delay_us(4);
}	

void IIC_Init(void)		//��ʼ������
{
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRL &= 0x00FFFFFF;
	GPIOB->CRL |= 0x77000000;						//ͨ�ÿ�©�����PB6-SCL PB7-SDA
	GPIOB->ODR |= ((1<<6)|(1<<7));			//PB6 PB7����
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
	uint8_t ack,i=0;
	SDA_H;		//�ͷ�SDA
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
	

