#ifndef	__BSP_I2C_H_
#define	__BSP_I2C_H_

#include "stm32f10x.h" 
#include "delay.h"
#include "sys.h"

//PB6-SCL     PB7-SDA
#define SCL PBout(6)
#define SDA PBout(7)
#define	scl 6
#define sda	7

void IIC_Delay(void);
void IIC_Init(void);						//��ʼ������
void IIC_Start(void);						//������ʼ����
void IIC_Stop(void);						//���ͽ�������
unsigned char IIC_ReadBck(void);			//����Ӧ��
void IIC_SendBck(void);						//����Ӧ��
void IIC_SendByte(unsigned char byte);		//����һ���ֽ�
unsigned char IIC_ReadByte(void);			//��һ���ֽ�

#endif
