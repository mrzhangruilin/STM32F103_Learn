#ifndef	__BSP_I2C_H_
#define	__BSP_I2C_H_

#include "stm32f10x.h"
#include "delay.h"

/* 接口定义 */
//PB6-SCL     PB7-SDA
#define SCL_H			GPIOB->BSRR	|=	1<<6
#define SCL_L			GPIOB->BRR	|=	1<<6
#define SDA_H 		GPIOB->BSRR	|=	1<<7
#define SDA_L 		GPIOB->BRR	|=	1<<7
#define	SDA_Read	GPIOB->IDR&1<<7

void IIC_Delay(void);
void IIC_Init(void);						
void IIC_Start(void);						
void IIC_Stop(void);						
unsigned char IIC_ReadBck(void);			
void IIC_SendBck(void);						
void IIC_SendByte(unsigned char byte);		
unsigned char IIC_ReadByte(void);			

#endif
