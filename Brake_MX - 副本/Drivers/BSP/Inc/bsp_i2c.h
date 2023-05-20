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
void IIC_Init(void);						//初始化引脚
void IIC_Start(void);						//发送起始条件
void IIC_Stop(void);						//发送结束条件
unsigned char IIC_ReadBck(void);			//接收应答
void IIC_SendBck(void);						//发送应答
void IIC_SendByte(unsigned char byte);		//发送一个字节
unsigned char IIC_ReadByte(void);			//读一个字节

#endif
