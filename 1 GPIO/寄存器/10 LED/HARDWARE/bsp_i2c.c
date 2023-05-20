#include "bsp_i2c.h"


void IIC_Delay()
{
	delay_us(4);
}	

void IIC_Init(void)		//��ʼ������
{
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRL &= 0x00FFFFFF;
	GPIOB->CRL |= 0x77000000;	//ͨ�ÿ�©�����PB6-SCL PB7-SDA
	GPIOB->ODR |= 3<<6;			//PB6 PB7����
}

void IIC_Start(void)	//������ʼλ
{
	SCL = 1;		//�ͷ�����
	SDA = 1;
	IIC_Delay();
	SDA = 0;		//SCL�ߵ�ƽ�ڼ�����SDA
	IIC_Delay();
	SCL = 0;		//Ϊ�˶���ʱ��
}

void IIC_Stop(void)		//���ͽ�������
{
	SCL = 0;
	SDA = 0;
	SCL = 1;		//����SCL
	IIC_Delay();	
	SDA = 1;		//��SCL���ڼ�����SDA
}

unsigned char IIC_ReadBck(void)	//����Ӧ��
{
	u8 ack;
	SDA = 1;		//�ͷ�SDA
	SCL = 1;	
	IIC_Delay();
	ack = PBin(sda);
	SCL = 0;
	SDA = 0;
	return ack;
}

void IIC_SendBck(void)			//����Ӧ��
{
	SCL = 0;
	IIC_Delay();
	SDA = 0;		//��Ӧ��
	IIC_Delay();
	SCL = 1;
	IIC_Delay();
	SCL = 0;
}

void IIC_SendByte(unsigned char byte)	//����һ���ֽ�
{
	int i;
	for(i=0; i<8; i++)
	{
		SCL = 0;			//����ʱ���ߣ�����ı�SDA
		if(byte&1<<(7-i)){SDA = 1;}else{SDA = 0;}
		SCL = 1;
		IIC_Delay();
	}
	SCL = 0;			//���ͽ���������SCL
}

unsigned char IIC_ReadByte()				//�������϶�һ���ֽ�
{
	int i;
	unsigned char byte=0;
	SDA = 1;			//�ͷ�SDA
	for(i=0; i<8; i++)
	{
		SCL = 1;		//���ߣ�Ȼ���
		IIC_Delay();
		if(PBin(sda)){byte |= (1<<(7-i));}
		SCL = 0;
		IIC_Delay();
	}
	return byte;
}
	

