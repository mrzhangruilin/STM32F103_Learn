#include "bsp_at24c02.h"

/***
addr:�ӻ���ַ
dataAdd:���ݵ�ַ
data:����ָ��
len:д�����ݳ���
*/
void AT24C02_WriteByte(uint8_t addr, uint8_t dataAdd, unsigned char *data, uint8_t len)		//дAT24C02һ���ֽ�,addr����λ��ַ
{
	{
		unsigned char i;
	
		IIC_Start();			//������ʼ����
		IIC_SendByte(addr<<1);	//������λ��ַ������λ0��д��
		IIC_ReadBck();			//��Ӧ��λ
		IIC_SendByte(dataAdd);	//�������ݵ�ַλ
		IIC_ReadBck();			//��Ӧ��λ

		for( i=0; i<len; i++)
		{
			IIC_SendByte(*(data+i));		//��������
			IIC_ReadBck();					//��Ӧ��λ
		}

		IIC_Stop();				//����ֹͣ����
		Delay_ms(10);
	}
}

void AT24C02_ReadByte(uint8_t addr, uint8_t dataAdd, unsigned char *data, uint8_t len)				//��AT24C02���һ���ֽڣ�addr����λ��ַ
{
	unsigned char i;
	
	IIC_Start();				//������ʼ����
	IIC_SendByte(addr<<1);		//������λ��ַ������λ0��д��
	IIC_ReadBck();				//��Ӧ��λ
	IIC_SendByte(dataAdd);		//�������ݵ�ַλ
	IIC_ReadBck();				//��Ӧ��λ
	
	//���·�����ʼ����
	IIC_Start();					//������ʼ����
	IIC_SendByte(addr<<1|1<<0);		//������λ��ַ������λ1����
	IIC_ReadBck();					//��Ӧ��λ
	for(i=0; i<len; i++)
	{
		*(data+i) = IIC_ReadByte();			//��һ���ֽ�
		IIC_SendBck();						//����Ӧ��
	}

	IIC_Stop();						//����ֹͣ����
	Delay_ms(10);
}

