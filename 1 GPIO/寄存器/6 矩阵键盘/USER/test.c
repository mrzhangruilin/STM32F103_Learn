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
	//EXTI��NVIC��������ʱ����һֱ���ŵģ�����Ҫ��
	//NVIC���ں����裬��CPUһ�����У�RCC�ܵ����ں�����
	
	GPIOA->CRL &= 0x00000000;	//����
	GPIOA->CRL |= 0x88881111;	//����λ���룬����λ���
	GPIOA->ODR |= 0xFF;			//�������룬������ߵ�ƽ
	
	//�ⲿ�ж����üĴ���
	AFIO->EXTICR[2] = 0x0000;	//����PA4 PA5 PA6 PA7 
	
	//����EXTI�Ĵ���
	EXTI->IMR |= (0xF<<4);		//��������4567���ϵ��ж�����
	EXTI->FTSR |= (0xF<<4);		//����������4567�ϵ��½��ش���
	
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
	while(PAin(4)==0);	//����
	printf("nihao");
	EXTI->PR=1<<4;  //���LINE4�ϵ��жϱ�־λ  
}

void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);	//����
	
	if(EXTI->PR&(1<<5))
	{
		LED2_on;
		delay_ms(500);
		LED2_off;
		EXTI->PR=1<<5;  //���LINE5�ϵ��жϱ�־λ  
	}else if(EXTI->PR&(1<<6))
	{
		LED3_on;
		delay_ms(500);
		LED3_off;
		EXTI->PR=1<<6;  //���LINE6�ϵ��жϱ�־λ  
	}else if(EXTI->PR&(1<<7))
	{
		LED4_on;
		delay_ms(500);
		LED4_off;
		EXTI->PR=1<<7;  //���LINE7�ϵ��жϱ�־λ  
	}
}
