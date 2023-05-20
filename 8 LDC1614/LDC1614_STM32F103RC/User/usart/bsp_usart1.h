#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>


static void USART1_Config(void);
static void NVIC_Configuration(void);
void USART1_Init(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif /* __USART1_H */
