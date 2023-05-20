#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"	 
 
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  		
//如果想串口中断接收，请不要注释以下宏定义
void Usart1_Init(u32 pclk2,u32 bound);

#endif	   
















