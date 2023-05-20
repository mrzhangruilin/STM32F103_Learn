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
void IIC_Init(void);						//初始化引脚
void IIC_Start(void);						//发送起始条件
void IIC_Stop(void);						//发送结束条件
unsigned char IIC_ReadBck(void);			//接收应答
void IIC_SendBck(void);						//发送应答
void IIC_SendByte(unsigned char byte);		//发送一个字节
unsigned char IIC_ReadByte(void);			//读一个字节

#endif
