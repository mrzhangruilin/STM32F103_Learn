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
	RCC->AHBENR |= (1<<0);																	//开启DMA时钟
	
	/*
	通道优先级最高；		存储器数据宽度32位；
	外设数据宽度32位；	开启存储器数据地址增量；
	执行循环操作；		允许传输完成中断
	*/
	DMA1_Channel1->CCR |= (3<<12) | (2<<10) | (2<<8) | (1<<7) | (1<<5) | (1<<1);  				
	DMA1_Channel1->CNDTR |= 2;																//传输数量2
	DMA1_Channel1->CPAR |= (uint32_t)&(ADC1->DR);											//取外设地址
	DMA1_Channel1->CMAR |= (uint32_t)data;													//取存储器地址
	
	DMA1_Channel1->CCR |= (1<<0);															//开启通道
	MY_NVIC_Init(0,0,DMA1_Channel1_IRQn,0);
}


void ADC_Init(void)
{
	//时钟使能
	RCC->APB2ENR |= (1<<2);
	GPIOA->CRL &= 0XFF00FFFF;	//PA5模拟输入

	
	RCC->APB2ENR |= (1<<9);		//ADC1时钟使能
	RCC->APB2RSTR|=1<<9;   		//ADC1复位
	RCC->APB2RSTR&=~(1<<9);		//复位结束	    
	RCC->CFGR &= ~(3<<14);		//清零
	RCC->CFGR |= 2<<14;			//PCLK2 6分频后得12Mhz
	
	
	//配置ADC，独立，单次，非扫描，外部触发，右对齐，注入
	ADC1->CR1&=0XF0FFFF;   //工作模式清零，设置成了独立模式
	ADC1->CR1&=~(1<<8);    //关闭扫描模式	
	
	ADC1->CR2&=~(1<<1);    //单次转换模式
	ADC1->CR2 &=~(7<<12);	//清零
	ADC1->CR2 |= 7<<17;		//软件控制，SWSTART
	ADC1->CR2 |= 1<<20;		//使用外部事件启动转换
	ADC1->CR2&=~(1<<11);   	//右对齐
	
	
	ADC1->SQR1 |= (1<<20);	//2个转换
	ADC1->SQR3 |= (4<<0);	//第一个转换，通道4
	ADC1->SQR3 |= (5<<5);	//第二个转换，通道5 
	
	ADC1->SMPR2&=~(7<<15);  //通道5采样时间清空
	ADC1->SMPR2&=~(7<<12);  //通道4采样时间清空
	ADC1->SMPR2 |= (7<<12);		
 	ADC1->SMPR2 |= (7<<15);	//通道5,239.5周期
	
	ADC1->CR2 |=  (1<<8);	//使用DMA模式
	
	ADC1->CR2|=1<<0;	   	//开启AD转换器
	//校准
	ADC1->CR2 |= (1<<3);	//复位校准
	while(ADC1->CR2&1<<3); //等待校准结束
	ADC1->CR2 |= (1<<2);	//A/D校准
	while(ADC1->CR2&1<<2);  //等待校准结束

}	

uint16_t ADC1_GetAC()
{
	ADC1->CR2 |= (1<<22);	//手动开始转换，规则
	while(!(ADC1->SR&1<<1));//等待转换结束，JEOC标志位
	ADC1->SR&=~(1<<1);		//清除标志位
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
		ADC1->CR2 |= (1<<22);		//手动开始转换，规则
		while(!(ADC1->SR&1<<1));	//等待转换结束，JEOC标志位
		ADC1->SR&=~(1<<1);			//清除标志位
		
		
		delay_ms(30);
		
	}	 
} 






