#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"
#include "usart.h"

int main(void)
{				 
	Stm32_Clock_Init(9);
	delay_init(72);
	
	RCC->APB2ENR |= 1<<2;		//ʹ��GPIOAʱ��
	
	GPIOA->CRL &= 0X00000000;	//��ռĴ���
	GPIOA->CRL |= 0X88881111;	//PA4��5��6��7�������룬PA0��1��2��3�������
	GPIOA->ODR |= 0xff;			//PA4��5��6��7����
	
  	while(1)
	{
		if(!(GPIOA->IDR&1<<4))		//��KEY1
		{
			GPIOA->ODR &= ~(1<<0);		//����LED1
		}else
		{
			GPIOA->ODR |= 1<<0;		//��LED1
		}
		
		
		if(!(GPIOA->IDR&1<<5))		//��KEY2
		{
			GPIOA->ODR |= 1<<1;		//��LED2
		}else
		{
			GPIOA->ODR &= ~(1<<1);		//����LED2
		}
		
		
		if(!(GPIOA->IDR&1<<6))		//��KEY3
		{
			//��������
			delay_ms(10);
			
			GPIOA->ODR ^= (1<<2);	//��ת��ƽ,��������
			
			while(!(GPIOA->IDR&1<<6));	//�ȴ��ɿ�����
			//�ɿ�����
			delay_ms(10);
		}
		
		if(!(GPIOA->IDR&1<<7))		//��KEY4
		{
			//��������
			delay_ms(10);
			
			GPIOA->ODR &= ~(1<<3);	//����LED4
			delay_ms(2000);			//��ʱ2s
			GPIOA->ODR |= (1<<3);	//��LED4
			
			while(!(GPIOA->IDR&1<<7));	//�ȴ��ɿ�����
			//�ɿ�����
			delay_ms(10);
		}

	}	 
} 






