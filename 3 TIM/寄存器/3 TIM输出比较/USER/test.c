#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"
#include "MY_timer.h"



int main(void)
{	
	int i=0,dir=0;		//0-¼Ó£¬1-¼õ
	Stm32_Clock_Init(9);
	delay_init(72);
	TIM2_PWM_Init();
	
	
	
  	while(1)
	{
		if(dir)
		{
			i -= 1;
		}else
		{
			i +=1;
		}
		
		if(i>=200)
		{
			dir = 1;
		}else if(i<=0)
		{
			dir = 0;
		}
		
		TIM2->CCR1 = i;
		delay_ms(90);
	}	 
} 






