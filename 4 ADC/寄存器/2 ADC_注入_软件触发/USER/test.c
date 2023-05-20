#include "stm32f10x.h" 
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "stdio.h"

void ADC_Init(void)
{
	//ʱ��ʹ��
	RCC->APB2ENR |= (1<<2);
	GPIOA->CRL &= 0XFF0FFFFF;	//PA5ģ������

	
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
	ADC1->CR2 |= 7<<12;		//������ƣ�JSWSTART
	ADC1->CR2 |= 1<<15;		//ʹ���ⲿ����
	ADC1->CR2&=~(1<<11);   	//�Ҷ���
	
	
	ADC1->JSQR &= ~(0X3<<20);	//1��ת����ע��������
	ADC1->JSQR &= ~(0X1F<<15);
	ADC1->JSQR |= 5<<15;	//ͨ��5
	
	ADC1->SMPR2&=~(7<<15);  //ͨ��5����ʱ�����	  
 	ADC1->SMPR2 |= 7<<15;	//ͨ��5,239.5����
	
	ADC1->CR2|=1<<0;	   	//����ADת����
	//У׼
	ADC1->CR2 |= (1<<3);	//��λУ׼
	while(ADC1->CR2&1<<3); //�ȴ�У׼����
	ADC1->CR2 |= (1<<2);	//A/DУ׼
	while(ADC1->CR2&1<<2);  //�ȴ�У׼����

}	

uint16_t ADC1_GetAC()
{
	ADC1->CR2 |= (1<<21);	//�ֶ���ʼת����ע��
	while(!(ADC1->SR&1<<1));//�ȴ�ת��������JEOC��־λ
	ADC1->SR&=~(1<<1);		//�����־λ
	return ADC1->JDR1;
}

int main(void)
{			
	float ac;
	
	Stm32_Clock_Init(9);
	delay_init(72);
	uart_init(72,9600);
	ADC_Init();
	
	
  	while(1)
	{
		ac = 3.3/0xfff*ADC1_GetAC();
		printf("��5ͨ����%f",ac);
		delay_ms(300);
		
	}	 
} 






