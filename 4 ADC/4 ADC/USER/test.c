#include "stm32f10x.h" 
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "stdio.h"
#include "MY_timer.h"


void ADC1_2_IRQHandler(void)
{
	int ac;
	float v;	//��ѹ
	
	if(ADC1->SR &(1<<2))		//ע��ת������
	{
		printf("SR:%d" , ADC1->SR);
		ac = ADC1->JDR1;			//���صõ���ת�����
		printf(" ͨ��5��%d",ac);
		v = (float)ac*3.3/0xfff;
		printf(" ��ѹֵ��%f\n",v);
	}
	
	ADC1->SR &= ~(7<<1);		//�����־λ
}

void ADC1_init(void)
{
	RCC->CFGR &= ~(3<<14);		//����
	RCC->CFGR |= (2<<14);		//ADC 6��Ƶ���õ�12Mhz
	RCC->APB2ENR |= (1<<9);		//��ADCʱ��
	
	RCC->APB2ENR |= (1<<2);		//��GPIOAʱ��
	GPIOA->CRL &= ~(0XF<<20);	//PA5ģ������
	
	//��λ
	RCC->APB2RSTR |= (1<<9);	//��λADC1
	RCC->APB2RSTR &= ~(1<<9);	//ֹͣ��λ	  
	
	//���Σ�ע�룬CH5����ɨ�裬�ֶ�������ʹ���ⲿ����
	ADC1->CR1 |= (1<<7);		//����JEOC�ж�
	ADC1->CR1 &= ~(1<<8);		//��ɨ��
	
	ADC1->CR2 |= (1<<15);		//ʹ���ⲿ�¼�����ת��
	ADC1->CR2 |= (3<<12);		//TIM2 CC1�¼�
	ADC1->CR2 &= ~(1<<11);		//�Ҷ���
	ADC1->CR2 &= ~(1<<1);		//����ת��
	
	ADC1->SMPR2 |= (7<<15);		//ͨ��5,239.5���ڣ������
	
	ADC1->JSQR &= ~(3<<20);		//1��ת��
	ADC1->JSQR |= (5<<15);		//ͨ��5
	
	
	ADC1->CR2 |= (1<<0);		//����ADC	//һ��Ҫ�ȿ�����У׼��
	
	//У׼������㲻��Ҫ��׼Ҳ���Բ�У׼
	ADC1->CR2 |= (1<<3);		//��λУ׼
	while(ADC1->CR2&(1<<3));
	ADC1->CR2 |= (1<<2);		//ADУ׼
	while(ADC1->CR2&(1<<2));
	
	MY_NVIC_Init(0,0,ADC1_2_IRQn,0);
}

int ADC1_get(void)				//��ȡͨ��5������
{
	//�ֶ�����ת��
	ADC1->CR2 |= (1<<21);		//��ʼת��ע��ͨ��
	while(!(ADC1->SR&1<<0));	//�ȴ�ת������
	ADC1->SR &= ~(3<<1);		//�����־λ������Ҳ���ã�ûʲô����
	return ADC1->JDR1;			//���صõ���ת�����
}



int main(void)
{			
	
	Stm32_Clock_Init(9);		//����ʱ�ӣ��������У������
	delay_init(72);				//ĳЩ���⹦����Ҫ�ĳ�ʼ��
	uart_init(72,9600);			//������Ϣ�õĳ�ʼ��
	
	ADC1_init();
	TIM2_ADC_Init(7200-1, 5000);
  	while(1)
	{
		
		

	}	 
} 






