#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"


//void USART1_IRQHandler(void)		//USART1接收中断处理函数
//{
//	u8 data;
//	data = USART1->DR;		//读取接收到的数据
//	USART1->DR = data;      
//}

void usart1_init(u32 pclk2,u32 bound)
{
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	
	//时钟使能
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB2ENR|=1<<14;  //使能串口1时钟
	//引脚配置
	GPIOA->CRH&=0XFFFFF00F;//IO状态设置
	GPIOA->CRH|=0X000008B0;//IO状态设置
	GPIOA->ODR|=(1<<10);	//RX上拉
	
	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位	 
	
	USART1->BRR=mantissa; // 波特率设置
	USART1->CR1|=0X200C;  //1位停止,无校验位.
	
	USART1->CR1|=1<<5;					//接收缓冲区非空中断使能
	MY_NVIC_Init(0,0,USART1_IRQn,0);	//组2，最低优先级 
	
}

void usart1_sendbyte(uint8_t byte)
{
	while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成  
	USART1->DR = byte;      	//写DR,串口1将发送数据
}



int main(void)
{			
	Stm32_Clock_Init(9);	//9倍频，72Mhz
	delay_init(72);
	usart1_init(72,9600);	//usart1初始化
	
	delay_ms(100);
  	while(1)
	{
		usart1_sendbyte(0x41);
	}	 
} 






