#include "stm32f10x.h" 
#include "sys.h"
#include "MY_LED.H"
#include "delay.h"
#include "stdio.h"
#include "usart.h"


void EXTI_init(void)
{
	RCC->APB2ENR |= (1<<2);		//GPIOA
	RCC->APB2ENR |= (1<<0);		//AFIO
	//EXTI和NVIC两个外设时钟是一直开着的，不需要开
	//NVIC是内核外设，和CPU一起运行，RCC管的是内核以外
	
	GPIOA->CRL &= 0x00000000;	//清零
	GPIOA->CRL |= 0x88881111;	//高四位输入，低四位输出
	GPIOA->ODR |= 0xFF;			//上拉输入，和输出高电平
	
	//外部中断配置寄存器
	AFIO->EXTICR[2] = 0x0000;	//配置PA4 PA5 PA6 PA7 
	
	//配置EXTI寄存器
	EXTI->IMR |= (0xF<<4);		//开放来自4567线上的中断请求
	EXTI->FTSR |= (0xF<<4);		//允许输入线4567上的下降沿触发
	
	MY_NVIC_Init(0,0,EXTI4_IRQn,0);
	MY_NVIC_Init(0,0,EXTI9_5_IRQn,0);
}

int main(void)
{				 
	delay_init(8);
	EXTI_init();
	MY_LED_Init();
	uart_init(8,9600);
	printf("nihao");
  	while(1)
	{
		
	}	 
} 


void EXTI4_IRQHandler(void)
{
	while(PAin(4)==0);	//消抖
	printf("nihao");
	EXTI->PR=1<<4;  //清除LINE4上的中断标志位  
}

void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);	//消抖
	
	if(EXTI->PR&(1<<5))
	{
		LED2_on;
		delay_ms(500);
		LED2_off;
		EXTI->PR=1<<5;  //清除LINE5上的中断标志位  
	}else if(EXTI->PR&(1<<6))
	{
		LED3_on;
		delay_ms(500);
		LED3_off;
		EXTI->PR=1<<6;  //清除LINE6上的中断标志位  
	}else if(EXTI->PR&(1<<7))
	{
		LED4_on;
		delay_ms(500);
		LED4_off;
		EXTI->PR=1<<7;  //清除LINE7上的中断标志位  
	}
}
