/**
 * 给Rx高电平，然后读Lx，若Lx是高电平则是按下按键
 * 其他Rx要保持低电平
*/

#include "bsp_matrix_keyboard.h"
#include "delay.h"
/**
 * L1-L4    PA0-PA3
 * R1-R3    PA4-PA6
*/

void Matrix_Keyboard_Init(void)
{
    RCC->APB2ENR |= 1<<2;

    GPIOA->CRL &= 0xF0000000;
    GPIOA->CRL |= 0x03338888;
    GPIOA->BRR |= (7<<4);
    GPIOA->ODR &= ~(0xF<<0);
}

uint8_t Matrix_Keyboard_Scanf(void)
{
    uint8_t res;

    MATRIX_KEYBOARD_R1_H;
    res = Matrix_Keyboard_Read_L();
    if (res!=0)
    {
        Delay_ms(10);
        while (Matrix_Keyboard_Read_L());
        Delay_ms(10);
        MATRIX_KEYBOARD_R1_L;
        return res*3-2;
    }
    MATRIX_KEYBOARD_R1_L;

    MATRIX_KEYBOARD_R2_H;
    res = Matrix_Keyboard_Read_L();
    if (res!=0)
    {
        Delay_ms(10);
        while (Matrix_Keyboard_Read_L());
        Delay_ms(10);
        MATRIX_KEYBOARD_R2_L;
        return res*3-1;
    }
    MATRIX_KEYBOARD_R2_L;

    MATRIX_KEYBOARD_R3_H;
    res = Matrix_Keyboard_Read_L();
    if (res!=0)
    {
        Delay_ms(10);
        while (Matrix_Keyboard_Read_L());
        Delay_ms(10);
        MATRIX_KEYBOARD_R3_L;
        return res*3;
    }
    MATRIX_KEYBOARD_R3_L;

    return 0;
}

uint8_t Matrix_Keyboard_Read_L(void)
{
    if (MATRIX_KEYBOARD_L1_READ)
    {
        return 1;
    }else if (MATRIX_KEYBOARD_L2_READ)
    {
        return 2;
    }else if (MATRIX_KEYBOARD_L3_READ)
    {
        return 3;
    }else if (MATRIX_KEYBOARD_L4_READ)
    {
        return 4;
    }else
    {
        return 0;
    }
    
}

