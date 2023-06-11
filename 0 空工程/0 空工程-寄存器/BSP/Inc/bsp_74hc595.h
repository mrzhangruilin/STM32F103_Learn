#ifndef _BSP_74HC595_H_
#define _BSP_74HC595_H_

#include "stm32f10x.h"

#define SMG595_DATA_Pin 4
#define SMG595_DATA_H       GPIOA->BSRR|=(1<<SMG595_DATA_Pin)
#define SMG595_DATA_L       GPIOA->BRR|=(1<<SMG595_DATA_Pin)


#define SMG595_CS_Pin 5
#define SMG595_CS_H         GPIOA->BSRR|=(1<<SMG595_CS_Pin)
#define SMG595_CS_L         GPIOA->BRR|=(1<<SMG595_CS_Pin)


#define SMG595_CLK_Pin 6
#define SMG595_CLK_H        GPIOA->BSRR|=(1<<SMG595_CLK_Pin)
#define SMG595_CLK_L        GPIOA->BRR|=(1<<SMG595_CLK_Pin)

#define SMG595_POSITION_0

void SMG_74HC595_Init(void);
void SMG_74HC595_SendData(uint8_t data);
void SMG_74HC595_Display(uint8_t position , uint8_t num , uint8_t point);
void SMG_74HC595_Display_Int(int16_t num);

#endif


