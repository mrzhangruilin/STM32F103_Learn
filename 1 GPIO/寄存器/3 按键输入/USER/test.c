#include "stm32f10x.h" 

int main(void)
{ 
 RCC->APB2ENR |= 1<<2;    //使能GPIOA的时钟
 GPIOA->CRL &= 0;     //清空控制PA0的端口位
 GPIOA->CRL |= 0x88881111;   //配置PA0为通用推挽输出，速度为10M，PA4口为上下拉输入
 GPIOA->ODR |= 0xFF;     //PA4配置为上拉输入
 
   while(1)
 {
  if(GPIOA->IDR &(1<<4)) //PAin(4)==0判断是否按下
  {
	GPIOA->ODR |= (1<<0);  //置1
  }else
  {
	  GPIOA->ODR &= ~(1<<0);  //置零
   
  }
  if(GPIOA->IDR &(1<<5)) //判断是否按下
  {
	GPIOA->ODR |= (1<<1);  //置1
  }else
  {
	  GPIOA->ODR &= ~(1<<1);  //置零
   
  }
  if(GPIOA->IDR &(1<<6)) //判断是否按下
  {
   GPIOA->ODR |= (1<<2);  //置1
  }else
  {
	  GPIOA->ODR &= ~(1<<2);  //置零
   
  }
  if(GPIOA->IDR &(1<<7)) //判断是否按下
  {
    GPIOA->ODR |= (1<<3);  //置1	
  }else
  {
	  GPIOA->ODR &= ~(1<<3);  //置零
  
  }
 } 
} 





