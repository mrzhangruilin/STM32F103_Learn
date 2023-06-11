#include "bsp_encoder.h"
#include "delay.h"


int16_t g_Encoder_cnt;

/**
 * A-PA5
 * B-PA6
*/
void Encoder_Init()
{
    RCC->APB2ENR |= (1<<0|1<<2);   /* AFIO、GPIOA时钟使能 */

    GPIOA->CRL &= 0xF00FFFFF;   
    GPIOA->CRL |= (0x08800000);   /* 上拉输入 */
    GPIOA->ODR |= (1<<5|1<<6);

    AFIO->EXTICR[1] &= ~(0xF<<4|0xF<<8); /* EXTI输入源为PA引脚*/
    EXTI->IMR |= (1<<5|1<<6);   /* 开放来自线上的中断请求 */
    EXTI->RTSR |= (1<<5|1<<6);  /* 允许线上的上升沿请求 */
    EXTI->FTSR |= (1<<5|1<<6);  /* 允许线上的下降沿请求 */

    MY_NVIC_Init(3 , 3 , EXTI9_5_IRQn , 2);
}

void EXTI9_5_IRQHandler(void)
{
    if (EXTI->PR&(1<<5))    //A相触发
    {
        if ( GPIOA->IDR&(1<<5)) //上升沿
        {
            if ( GPIOA->IDR&(1<<6) )
            {
                g_Encoder_cnt--;
            }
            else
            {
                g_Encoder_cnt++;
            }
        }
        else
        {
            if ( GPIOA->IDR&(1<<6) )
            {
                g_Encoder_cnt++;
            }
            else
            {
                g_Encoder_cnt--;
            }
        }
        EXTI->PR |= (1<<5);
    }
    else
    {
        if ( GPIOA->IDR&(1<<6)) //上升沿
        {
            if ( GPIOA->IDR&(1<<5) )
            {
                g_Encoder_cnt++;
            }
            else
            {
                g_Encoder_cnt--;
            }
        }
        else
        {
            if ( GPIOA->IDR&(1<<5) )
            {
                g_Encoder_cnt--;
            }
            else
            {
                g_Encoder_cnt++;
            }
        }
        EXTI->PR |= (1<<6);
    } 
}

int16_t Encoder_Get(void)
{
    return g_Encoder_cnt;
}

