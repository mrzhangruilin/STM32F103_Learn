/*********************************/
//串口1初始化程序，包含了引脚初始化
//其中fputc()对printf进行重定义，给usart1做输出

#ifndef __USART_H_
#define __USART_H_

#include "stm32f10x.h"                  // Device header
#include "stdio.h"

void USART1_Init(void);

#endif
