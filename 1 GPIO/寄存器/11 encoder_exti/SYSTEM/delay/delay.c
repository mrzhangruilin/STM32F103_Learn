#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 


static u8  fac_us=0;							//us延时倍乘数			   
static u16 fac_ms=0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数
	
		   
/**
*function:	初始化滴答计时器
*para:			SYSCLK系统时钟，滴答计时器默认是SYSSLK的八分频
*/
void Delay_Init(u8 SYSCLK)
{
 	SysTick->CTRL&=~(1<<2);					//SYSTICK使用外部时钟源	 
	fac_us=SYSCLK/8;								//每个us需要的systick时钟数
	
	fac_ms=(u16)fac_us*1000;				//代表每个ms需要的systick时钟数   

}								    

//延时nus
//nus为要延时的us数.		    								   
void Delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//时间加载	  		 
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL=0x01 ;      				//开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL=0x00;      	 						//关闭计数器
	SysTick->VAL =0X00;       						//清空计数器	 
}

/**
*function：	毫秒延时
*para：			延时时长，单位毫秒
注意nms范围，SystTick->LOAD是24位寄存器，所以最大延时为:nms<=0xffffff*8*1000/SYSCLK
对72M条件下,nms<=1864 
*/
void Delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           			//清空计数器
	SysTick->CTRL=0x01 ;          			//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL=0x00;      	 						//关闭计数器
	SysTick->VAL =0X00;       						//清空计数器	  	    
} 





























