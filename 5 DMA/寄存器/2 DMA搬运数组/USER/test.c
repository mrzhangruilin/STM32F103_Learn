#include "stm32f10x.h" 
#include "stdio.h"
#include "usart.h"
#include "delay.h"

void MY_DMA_init(void)	//register to register
{
	RCC->AHBENR |= (1<<0);				//ʹ��
	
	DMA1_Channel1->CCR |= (1<<14);		//�洢�����洢��ģʽ
	DMA1_Channel1->CCR |= (2<<10);		//32λ�洢�����ݿ��
	DMA1_Channel1->CCR |= (2<<8);		//32�������ݿ��
	DMA1_Channel1->CCR |= (1<<7);		//ִ�д洢����ַ��������
	DMA1_Channel1->CCR |= (1<<6);		//ִ�������ַ��������
	DMA1_Channel1->CCR |= (0<<4);		//���䷽�򣬴������
	DMA1_Channel1->CCR |= (1<<1);		//����TC�ж�
	
}

void MY_DMA_transfer(uint32_t Data_source, uint32_t Data_purpose, uint16_t num)
{
	
	DMA1_Channel1->CPAR = Data_source;	//Դ���ݵ�ַ
	DMA1_Channel1->CMAR = Data_purpose;	//Ŀ�ĵص�ַ	
	DMA1_Channel1->CNDTR = num;			//��������
	
	DMA1_Channel1->CCR |= (1<<0);		//ͨ������
	while(!(DMA1->ISR&1<<1));			//�ȴ��������
	printf("ISR:%d\n",DMA1->ISR);
	DMA1->IFCR |= 0xF<<0;				//�����־λ
	while((DMA1->ISR&1<<1));			//�ȴ���־λ������
	DMA1_Channel1->CCR &= ~(1<<0);		//ͨ���ر�
}

int main(void)
{				 
	uint32_t dataA[4]={0,10,100,200};
	uint32_t dataB[4];
	
	Stm32_Clock_Init(9);
	uart_init(72,9600);
	delay_init(72);
	MY_DMA_init();
	
  	while(1)
	{
		MY_DMA_transfer((uint32_t)dataA,(uint32_t)dataB,4);
		printf("dataA: %d %d %d %d\n",dataA[0],dataA[1],dataA[2],dataA[3]);
		printf("dataB: %d %d %d %d\n",dataB[0],dataB[1],dataB[2],dataB[3]);
		dataA[0]++;dataA[1]++;dataA[2]++;dataA[3]++;
		delay_ms(1000);
	}	 
} 






