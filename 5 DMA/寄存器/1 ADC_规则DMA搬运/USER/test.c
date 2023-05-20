#include "stm32f10x.h" 
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "stdio.h"

uint32_t data[16];

void DMA1_Channel1_IRQHandler(void)
{
	printf("OKK");
}

void DMA_Init(void)
{
	RCC->AHBENR |= (1<<0);																	//����DMAʱ��
	
	/*
	ͨ�����ȼ���ߣ�		�洢�����ݿ��32λ��
	�������ݿ��32λ��	�����洢�����ݵ�ַ������
	ִ��ѭ��������		����������ж�
	*/
	DMA1_Channel1->CCR |= (3<<12) | (2<<10) | (2<<8) | (1<<7) | (1<<5) | (1<<1);  				
	DMA1_Channel1->CNDTR |= 2;																//��������2
	DMA1_Channel1->CPAR |= (uint32_t)&(ADC1->DR);											//ȡ�����ַ
	DMA1_Channel1->CMAR |= (uint32_t)data;													//ȡ�洢����ַ
	
	DMA1_Channel1->CCR |= (1<<0);															//����ͨ��
	MY_NVIC_Init(0,0,DMA1_Channel1_IRQn,0);
}


void ADC_Init(void)
{
	//ʱ��ʹ��
	RCC->APB2ENR |= (1<<2);
	GPIOA->CRL &= 0XFF00FFFF;	//PA5ģ������

	
	RCC->APB2ENR |= (1<<9);		//ADC1ʱ��ʹ��
	RCC->APB2RSTR|=1<<9;   		//ADC1��λ
	RCC->APB2RSTR&=~(1<<9);		//��λ����	    
	RCC->CFGR &= ~(3<<14);		//����
	RCC->CFGR |= 2<<14;			//PCLK2 6��Ƶ���12Mhz
	
	
	//����ADC�����������Σ���ɨ�裬�ⲿ�������Ҷ��룬ע��
	ADC1->CR1&=0XF0FFFF;   //����ģʽ���㣬���ó��˶���ģʽ
	ADC1->CR1&=~(1<<8);    //�ر�ɨ��ģʽ	
	
	ADC1->CR2&=~(1<<1);    //����ת��ģʽ
	ADC1->CR2 &=~(7<<12);	//����
	ADC1->CR2 |= 7<<17;		//������ƣ�SWSTART
	ADC1->CR2 |= 1<<20;		//ʹ���ⲿ�¼�����ת��
	ADC1->CR2&=~(1<<11);   	//�Ҷ���
	
	
	ADC1->SQR1 |= (1<<20);	//2��ת��
	ADC1->SQR3 |= (4<<0);	//��һ��ת����ͨ��4
	ADC1->SQR3 |= (5<<5);	//�ڶ���ת����ͨ��5 
	
	ADC1->SMPR2&=~(7<<15);  //ͨ��5����ʱ�����
	ADC1->SMPR2&=~(7<<12);  //ͨ��4����ʱ�����
	ADC1->SMPR2 |= (7<<12);		
 	ADC1->SMPR2 |= (7<<15);	//ͨ��5,239.5����
	
	ADC1->CR2 |=  (1<<8);	//ʹ��DMAģʽ
	
	ADC1->CR2|=1<<0;	   	//����ADת����
	//У׼
	ADC1->CR2 |= (1<<3);	//��λУ׼
	while(ADC1->CR2&1<<3); //�ȴ�У׼����
	ADC1->CR2 |= (1<<2);	//A/DУ׼
	while(ADC1->CR2&1<<2);  //�ȴ�У׼����

}	

uint16_t ADC1_GetAC()
{
	ADC1->CR2 |= (1<<22);	//�ֶ���ʼת��������
	while(!(ADC1->SR&1<<1));//�ȴ�ת��������JEOC��־λ
	ADC1->SR&=~(1<<1);		//�����־λ
	return ADC1->DR;
}

int main(void)
{			
	
	Stm32_Clock_Init(9);
	delay_init(72);
	uart_init(72,9600);
	ADC_Init();
	DMA_Init();
	
  	while(1)
	{
		ADC1->CR2 |= (1<<22);		//�ֶ���ʼת��������
		while(!(ADC1->SR&1<<1));	//�ȴ�ת��������JEOC��־λ
		ADC1->SR&=~(1<<1);			//�����־λ
		
		
		delay_ms(30);
		
	}	 
} 






