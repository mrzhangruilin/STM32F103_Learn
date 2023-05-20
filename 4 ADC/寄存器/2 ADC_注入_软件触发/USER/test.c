#include "stm32f10x.h" 
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "stdio.h"

void ADC_Init(void)
{
	//时钟使能
	RCC->APB2ENR |= (1<<2);
	GPIOA->CRL &= 0XFF0FFFFF;	//PA5模拟输入

	
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
	ADC1->CR2 |= 7<<12;		//软件控制，JSWSTART
	ADC1->CR2 |= 1<<15;		//使用外部触发
	ADC1->CR2&=~(1<<11);   	//右对齐
	
	
	ADC1->JSQR &= ~(0X3<<20);	//1个转换在注册序列中
	ADC1->JSQR &= ~(0X1F<<15);
	ADC1->JSQR |= 5<<15;	//通道5
	
	ADC1->SMPR2&=~(7<<15);  //通道5采样时间清空	  
 	ADC1->SMPR2 |= 7<<15;	//通道5,239.5周期
	
	ADC1->CR2|=1<<0;	   	//开启AD转换器
	//校准
	ADC1->CR2 |= (1<<3);	//复位校准
	while(ADC1->CR2&1<<3); //等待校准结束
	ADC1->CR2 |= (1<<2);	//A/D校准
	while(ADC1->CR2&1<<2);  //等待校准结束

}	

uint16_t ADC1_GetAC()
{
	ADC1->CR2 |= (1<<21);	//手动开始转换，注入
	while(!(ADC1->SR&1<<1));//等待转换结束，JEOC标志位
	ADC1->SR&=~(1<<1);		//清除标志位
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
		printf("第5通道：%f",ac);
		delay_ms(300);
		
	}	 
} 






