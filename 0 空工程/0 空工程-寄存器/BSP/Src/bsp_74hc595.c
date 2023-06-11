/**
 * 共阳极数码管
 * 段选：
 * A0-PA0    A1-PA1    A2-PA2   A3-PA3
 * 74CH595：
 * DAT-PA4    CS-PA5    CLK-PA6
 * 
*/
#include "bsp_74hc595.h"
#include "delay.h"

void SMG_74HC595_Init(void)
{
    RCC->APB2ENR |= (1<<2);

    GPIOA->CRL &= 0xF0000000;
    GPIOA->CRL |= 0x03333333;    //通用推挽
    GPIOA->ODR &= ~(1<<4|1<<5|1<<6);
    GPIOA->ODR |= (1<<0|1<<1|1<<2|1<<3);
}

/**
 * @brief   向74HC595发送数据
*/
void SMG_74HC595_SendData(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        SMG595_CLK_L;
        if (data&(1<<(7-i)))
        {
            SMG595_DATA_H;
        }
        else
        {
            SMG595_DATA_L;
        }
        SMG595_CLK_H;

    }
    
    SMG595_CS_H;
    Delay_us(1);
    SMG595_CS_L;
}

/**
 * @brief   数码管显示数字
 * @param   position    参考表Position
 * @param   num         0-9可选，10为全不亮
 * @param   point       0-不显示小数点，1-显示小数点,11-横杠
*/
void SMG_74HC595_Display(uint8_t position , uint8_t num , uint8_t point)
{
    uint8_t data;
    switch (num)
    {
    case 0:default:
        data = 1<<6;
        break;
    case 1:
        data = ~(1<<1|1<<2);
        break;
    case 2:
        data = 1<<2|1<<5;
        break;
    case 3:
        data = 1<<4|1<<5;
        break;
    case 4:
        data = 1<<0|1<<3|1<<4;
        break;
    case 5:
        data = 1<<1|1<<4;
        break;
    case 6:
        data = 1<<1;
        break;
    case 7:
        data = ~(1<<0|1<<1|1<<2);
        break;
    case 8:
        data = 0;
        break;
    case 9:
        data = 1<<4;
        break;
    case 10:
        data = 0xff;
        break;
    case 11:
        data = ~(1<<6);
        break;
    }

    if (point)
    {
        data &= ~(1<<7);
    }
    else
    {
        data |= 1<<7;
    }
    
    
    SMG_74HC595_SendData(data);

    GPIOA->BSRR|=(1<<0|1<<1|1<<2|1<<3);
    if (position&1<<0)
    {
        GPIOA->BRR|=(1<<0);
    }

    if (position&1<<1)
    {
        GPIOA->BRR|=(1<<1);
    }

    if (position&1<<2)
    {
        GPIOA->BRR|=(1<<2);
    }

    if (position&1<<3)
    {
        GPIOA->BRR|=(1<<3);
    }
}

/**
 * @brief   控制四个数码管显示一个整数
 * @brief   -999<num<9999
*/
void SMG_74HC595_Display_Int(int16_t num)
{
    uint8_t array[4]; 
    uint8_t i;   
    if (num>=0)
    {
        array[0] = num/1000%10;
        array[1] = num/100%10;
        array[2] = num/10%10;
        array[3] = num%10;
        for (i = 0; i<4&&array[i]==0; i++)
        {
            array[i] = 10;
        }
        
        
        SMG_74HC595_Display(1<<3 , array[3] , 0);
        Delay_ms(1);
        SMG_74HC595_Display(0xf , 10 , 0);
   
        SMG_74HC595_Display(1<<2 , array[2] , 0);
        Delay_ms(1);
        SMG_74HC595_Display(0xf , 10 , 0);

        SMG_74HC595_Display(1<<1 , array[1] , 0);
        Delay_ms(1);
        SMG_74HC595_Display(0xf , 10 , 0);

        SMG_74HC595_Display(1<<0 , array[0] , 0);
        Delay_ms(1);
        SMG_74HC595_Display(0xf , 10 , 0);
    }
    else
    {
        array[0] = num/-1000%10;
        array[1] = num/-100%10;
        array[2] = num/-10%10;
        array[3] = num/-1%(10);
        for (i = 0; i<4&&array[i]==0; i++)
        {
            array[i] = 10;
        }
        if (i==0)
        {
            array[0] = 11;
        }
        else
        {
            array[i-1] = 11;
        }
        
        SMG_74HC595_Display(1<<3 , array[3] , 0);
        Delay_ms(1);
        SMG_74HC595_Display(0xf , 10 , 0);
   
        SMG_74HC595_Display(1<<2 , array[2] , 0);
        Delay_ms(1);
        SMG_74HC595_Display(0xf , 10 , 0);

        SMG_74HC595_Display(1<<1 , array[1] , 0);
        Delay_ms(1);
        SMG_74HC595_Display(0xf , 10 , 0);

        SMG_74HC595_Display(1<<0 , array[0] , 0);
        Delay_ms(1);
        SMG_74HC595_Display(0xf , 10 , 0);
    }
}

