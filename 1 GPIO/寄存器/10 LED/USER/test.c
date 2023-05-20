#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"
#include "usart.h"

int main(void)
{				 
	Stm32_Clock_Init(9);
	delay_init(72);
	
	RCC->APB2ENR |= 1<<2;		//使能GPIOA时钟
	
	GPIOA->CRL &= 0X00000000;	//清空寄存器
	GPIOA->CRL |= 0X88881111;	//PA4、5、6、7上拉输入，PA0、1、2、3推挽输出
	GPIOA->ODR |= 0xff;			//PA4、5、6、7上拉
	
  	while(1)
	{
		if(!(GPIOA->IDR&1<<4))		//读KEY1
		{
			GPIOA->ODR &= ~(1<<0);		//点亮LED1
		}else
		{
			GPIOA->ODR |= 1<<0;		//灭LED1
		}
		
		
		if(!(GPIOA->IDR&1<<5))		//读KEY2
		{
			GPIOA->ODR |= 1<<1;		//灭LED2
		}else
		{
			GPIOA->ODR &= ~(1<<1);		//点亮LED2
		}
		
		
		if(!(GPIOA->IDR&1<<6))		//读KEY3
		{
			//按下消抖
			delay_ms(10);
			
			GPIOA->ODR ^= (1<<2);	//翻转电平,异或运算符
			
			while(!(GPIOA->IDR&1<<6));	//等待松开按键
			//松开消抖
			delay_ms(10);
		}
		
		if(!(GPIOA->IDR&1<<7))		//读KEY4
		{
			//按下消抖
			delay_ms(10);
			
			GPIOA->ODR &= ~(1<<3);	//点亮LED4
			delay_ms(2000);			//延时2s
			GPIOA->ODR |= (1<<3);	//灭LED4
			
			while(!(GPIOA->IDR&1<<7));	//等待松开按键
			//松开消抖
			delay_ms(10);
		}

	}	 
} 






