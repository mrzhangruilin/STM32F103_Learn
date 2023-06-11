#include "usart.h"	  

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 

/**
	*	重定向fputc函数

*/
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成  
	USART1->DR = (u8) ch;      	//写DR,串口1将发送数据
	return ch;
}
#endif 
//////////////////////////////////////////////////////////////////


#if EN_USART1_RX   //如果使能了接收

//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  
void USART1_IRQHandler(void)
{
	u8 res;	

	if(USART1->SR&(1<<5))	//接收到数据
	{	 
		res = USART1->DR;			/* 读取DR寄存器之后自动清除标志位 */
	}

} 
#endif

/**
*function:	初始化串口1
*para：			pclk：串口1的时钟，bound串口1波特率
*/
void Usart1_Init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);	//得到USARTDIV
	mantissa=temp;				 									//得到整数部分
	fraction=(temp-mantissa)*16; 						//得到小数部分	 
	mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   									//使能PORTA口时钟  
	RCC->APB2ENR|=1<<14;  									//使能串口时钟 
	GPIOA->CRH&=0XFFFFF00F;									//IO状态设置
	GPIOA->CRH|=0X000008B0;									//IO状态设置 
	RCC->APB2RSTR|=1<<14;   								//复位串口1
	RCC->APB2RSTR&=~(1<<14);								//停止复位	   	   
	//波特率设置
 	USART1->BRR=mantissa; 									//波特率设置	 
	USART1->CR1|=0X200C;  									//1位停止,无校验位.
#if EN_USART1_RX		  									//如果使能了接收
	//使能接收中断 
	USART1->CR1|=1<<5;    									//接收缓冲区非空中断使能	    	
	MY_NVIC_Init(3,3,USART1_IRQn,2);						//组2，最低优先级 
#endif
}
