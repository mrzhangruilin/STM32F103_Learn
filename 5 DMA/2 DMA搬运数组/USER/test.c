#include "stm32f10x.h" 
#include "stdio.h"
#include "usart.h"
#include "delay.h"

void MY_DMA_init(void)	//register to register
{
	RCC->AHBENR |= (1<<0);				//使能
	
	DMA1_Channel1->CCR |= (1<<14);		//存储器到存储器模式
	DMA1_Channel1->CCR |= (2<<10);		//32位存储器数据宽度
	DMA1_Channel1->CCR |= (2<<8);		//32外设数据宽度
	DMA1_Channel1->CCR |= (1<<7);		//执行存储器地址增量操作
	DMA1_Channel1->CCR |= (1<<6);		//执行外设地址增量操作
	DMA1_Channel1->CCR |= (0<<4);		//传输方向，从外设读
	DMA1_Channel1->CCR |= (1<<1);		//允许TC中断
	
}

void MY_DMA_transfer(uint32_t Data_source, uint32_t Data_purpose, uint16_t num)
{
	
	DMA1_Channel1->CPAR = Data_source;	//源数据地址
	DMA1_Channel1->CMAR = Data_purpose;	//目的地地址	
	DMA1_Channel1->CNDTR = num;			//传输数量
	
	DMA1_Channel1->CCR |= (1<<0);		//通道开启
	while(!(DMA1->ISR&1<<1));			//等待传输完成
	printf("ISR:%d\n",DMA1->ISR);
	DMA1->IFCR |= 0xF<<0;				//清除标志位
	while((DMA1->ISR&1<<1));			//等待标志位清除完毕
	DMA1_Channel1->CCR &= ~(1<<0);		//通道关闭
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






