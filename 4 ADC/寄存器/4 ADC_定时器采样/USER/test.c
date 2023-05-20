#include "stm32f10x.h" 
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "stdio.h"
#include "MY_timer.h"


void ADC1_2_IRQHandler(void)
{
	int ac;
	float v;	//电压
	
	if(ADC1->SR &(1<<2))		//注入转换结束
	{
		printf("SR:%d" , ADC1->SR);
		ac = ADC1->JDR1;			//返回得到的转换结果
		printf(" 通道5：%d",ac);
		v = (float)ac*3.3/0xfff;
		printf(" 电压值：%f\n",v);
	}
	
	ADC1->SR &= ~(7<<1);		//清除标志位
}

void ADC1_init(void)
{
	RCC->CFGR &= ~(3<<14);		//清零
	RCC->CFGR |= (2<<14);		//ADC 6分频，得到12Mhz
	RCC->APB2ENR |= (1<<9);		//打开ADC时钟
	
	RCC->APB2ENR |= (1<<2);		//打开GPIOA时钟
	GPIOA->CRL &= ~(0XF<<20);	//PA5模拟输入
	
	//复位
	RCC->APB2RSTR |= (1<<9);	//复位ADC1
	RCC->APB2RSTR &= ~(1<<9);	//停止复位	  
	
	//单次，注入，CH5，非扫描，手动触发，使用外部触发
	ADC1->CR1 |= (1<<7);		//允许JEOC中断
	ADC1->CR1 &= ~(1<<8);		//非扫描
	
	ADC1->CR2 |= (1<<15);		//使用外部事件启动转换
	ADC1->CR2 |= (3<<12);		//TIM2 CC1事件
	ADC1->CR2 &= ~(1<<11);		//右对齐
	ADC1->CR2 &= ~(1<<1);		//单次转换
	
	ADC1->SMPR2 |= (7<<15);		//通道5,239.5周期，最长周期
	
	ADC1->JSQR &= ~(3<<20);		//1个转换
	ADC1->JSQR |= (5<<15);		//通道5
	
	
	ADC1->CR2 |= (1<<0);		//开启ADC	//一定要先开启再校准呢
	
	//校准，如果你不想要精准也可以不校准
	ADC1->CR2 |= (1<<3);		//复位校准
	while(ADC1->CR2&(1<<3));
	ADC1->CR2 |= (1<<2);		//AD校准
	while(ADC1->CR2&(1<<2));
	
	MY_NVIC_Init(0,0,ADC1_2_IRQn,0);
}

int ADC1_get(void)				//获取通道5的数据
{
	//手动开启转换
	ADC1->CR2 |= (1<<21);		//开始转换注入通道
	while(!(ADC1->SR&1<<0));	//等待转换结束
	ADC1->SR &= ~(3<<1);		//清除标志位，好像也不用，没什么鬼用
	return ADC1->JDR1;			//返回得到的转换结果
}



int main(void)
{			
	
	Stm32_Clock_Init(9);		//配置时钟，高速运行，最高速
	delay_init(72);				//某些特殊功能需要的初始化
	uart_init(72,9600);			//发送信息用的初始化
	
	ADC1_init();
	TIM2_ADC_Init(7200-1, 5000);
  	while(1)
	{
		
		

	}	 
} 






