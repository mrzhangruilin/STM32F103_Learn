#ifndef	__BSP_I2C_H_
#define	__BSP_I2C_H_

#include "main.h" 
#include "gpio.h"

//PB6-SCL     PB7-SDA
#define SCL_H       HAL_GPIO_WritePin(I2C_SCL_GPIO_Port , I2C_SCL_Pin , GPIO_PIN_SET)
#define SCL_L       HAL_GPIO_WritePin(I2C_SCL_GPIO_Port , I2C_SCL_Pin , GPIO_PIN_RESET)
#define SDA_H       HAL_GPIO_WritePin(I2C_SDA_GPIO_Port , I2C_SDA_Pin , GPIO_PIN_SET)
#define SDA_L       HAL_GPIO_WritePin(I2C_SDA_GPIO_Port , I2C_SDA_Pin , GPIO_PIN_RESET)
#define SDA_Read    HAL_GPIO_ReadPin(I2C_SDA_GPIO_Port , I2C_SDA_Pin)

#define Delay_ms(ms) HAL_Delay(ms)

void IIC_Delay(void);
void IIC_Init(void);						//��ʼ������
void IIC_Start(void);						//������ʼ����
void IIC_Stop(void);						//���ͽ�������
unsigned char IIC_ReadBck(void);			//����Ӧ��
void IIC_SendBck(void);						//����Ӧ��
void IIC_SendByte(unsigned char byte);		//����һ���ֽ�
unsigned char IIC_ReadByte(void);			//��һ���ֽ�

#endif
