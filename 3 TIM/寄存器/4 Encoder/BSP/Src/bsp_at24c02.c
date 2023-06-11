#include "bsp_at24c02.h"

/***
*function:	��AT24C02д������
*para��
	@addr:		�ӻ���ַ
	@dataAdd:	���ݵ�ַ
	@data:		����ָ��
	@len:			д�����ݳ���
*retval��NULL
*ע�⣬ҳд���˸��ֽ�һҳ��0-7��һҳ��8-15��һҳ
*/
void AT24C02_WriteByte(uint8_t addr, uint8_t dataAdd, unsigned char *data, uint8_t len)
{
	unsigned char i;
	if(len>8){len = 8;}			//�ж϶�ȡ�����Ƿ񳬳���Χ
	SCL_H;									//�ͷ�����
	SDA_H;									//�ͷ�SDA
	i = SDA_Read;
	while(!(SDA_Read));			//�ȴ����߿���
	IIC_Start();						//������ʼ����
	IIC_SendByte(addr<<1);	//������λ��ַ������λ0��д��
	IIC_ReadBck();					//��Ӧ��λ
	IIC_SendByte(dataAdd);	//�������ݵ�ַλ
	IIC_ReadBck();					//��Ӧ��λ
	
	for( i=0; i<len; i++)
	{
		IIC_SendByte(*(data+i));		//��������
		IIC_Delay();
		IIC_ReadBck();							//��Ӧ��λ
		IIC_Delay();
	}
	
	IIC_Stop();				//����ֹͣ����
	Delay_ms(10);
}

/**
*function:	��AT24C02����ֽ�
*para
	@addr:		�ӻ���ַ
	@dataAdd:	��ȡ��ַ
	@data:		��ȡ������
	@len:			��ȡ����
*retval��		NULL
*/
void AT24C02_ReadByte(uint8_t addr, uint8_t dataAdd, unsigned char *data, uint8_t len)
{
	unsigned char i;
	SCL_H;													//�ͷ�����
	SDA_H;													//�ͷ�SDA
	while(!(SDA_Read));							//�ȴ����߿���
	IIC_Start();										//������ʼ����������λ0��д��
	IIC_ReadBck();									//��Ӧ��λ
	IIC_SendByte(addr<<1);					//������λ��ַ
	IIC_SendByte(dataAdd);					//�������ݵ�ַλ
	IIC_ReadBck();									//��Ӧ��λ
	
	//���·�����ʼ����
	SCL_H;													//�ͷ�����
	SDA_H;													//�ͷ�SDA
	while(!(SDA_Read));							//�ȴ����߿���
	IIC_Start();										//������ʼ����
	IIC_SendByte(addr<<1|1<<0);			//������λ��ַ������λ1����
	IIC_ReadBck();									//��Ӧ��λ
	for(i=0; i<len; i++)
	{
		*(data+i) = IIC_ReadByte();		//��һ���ֽ�
		IIC_Delay();
		IIC_SendBck();								//����Ӧ��
		IIC_Delay();
	}
	IIC_Stop();											//����ֹͣ����
	Delay_ms(10);
}
