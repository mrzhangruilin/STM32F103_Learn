#include "stm32f10x.h" 
#include "sys.h"
#include "MY_LED.H"

void TIM2_init(void)
{
	RCC->APB1ENR |= (1<<0);	//TIM2，通用定时器
	
	TIM2->ARR = 10000;	//自动重装载寄存器，计数5000次
	TIM2->PSC = 7199;	//预分频器设置
	TIM2->DIER |= 1<<0;	//允许更新中断
	TIM2->CR1 |= 0x01;	//使能定时器2
	MY_NVIC_Init(0,0,TIM2_IRQn,0);
}

int main(void)
{	
	Stm32_Clock_Init(9);			//选择高速外部晶振经过PLL锁相环9倍频之后作为系统时钟
	TIM2_init();

  while(1)
	{
		//其他事情
	}	 
} 


//中断函数，产生中断的时候执行，谁产生中断谁去执行
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0x01)//溢出中断
	{
		PAout(0) = !PAout(0);
		TIM2->SR&=~(1<<0);//清除中断标志位 	    
	}				   
	
}




