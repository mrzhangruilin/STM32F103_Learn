#include "stm32f10x.h" 
#include "MY_LED.h"
#include "MY_timer.h"
#include "delay.h"

int main(void)
{			
	int dir=0,i=0;
	Stm32_Clock_Init(9);
	delay_init(72);
	TIM2_PWM_Init();
	
  	while(1)
	{
		//i存放着占空比
		
		if(i>200){dir=1;}	//dir-0向上增，dir-1向下减
		if(i==0){dir=0;}
		if(dir){i-=1;}else{i+=1;}
		TIM2->CCR1 = i;
		TIM2->CCR2 = i;
		delay_ms(5);
	}	 
} 






