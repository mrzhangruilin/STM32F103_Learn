#ifndef _BSP_MATRIX_KEYBOARD_H__
#define _BSP_MATRIX_KEYBOARD_H__

#include "stm32f10x.h"

#define MATRIX_KEYBOARD_R1_H    GPIOA->BSRR|=(1<<4)
#define MATRIX_KEYBOARD_R1_L    GPIOA->BRR|=(1<<4)
#define MATRIX_KEYBOARD_R2_H    GPIOA->BSRR|=(1<<5)
#define MATRIX_KEYBOARD_R2_L    GPIOA->BRR|=(1<<5)
#define MATRIX_KEYBOARD_R3_H    GPIOA->BSRR|=(1<<6)
#define MATRIX_KEYBOARD_R3_L    GPIOA->BRR|=(1<<6)

#define MATRIX_KEYBOARD_L1_READ    (GPIOA->IDR&(1<<0))>>0
#define MATRIX_KEYBOARD_L2_READ    (GPIOA->IDR&(1<<1))>>1
#define MATRIX_KEYBOARD_L3_READ    (GPIOA->IDR&(1<<2))>>2
#define MATRIX_KEYBOARD_L4_READ    (GPIOA->IDR&(1<<3))>>3

void Matrix_Keyboard_Init(void);
uint8_t Matrix_Keyboard_Scanf(void);
uint8_t Matrix_Keyboard_Read_L(void);



#endif

