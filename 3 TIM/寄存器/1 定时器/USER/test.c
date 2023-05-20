#include "stm32f10x.h" 
#include "sys.h"
#include "MY_LED.H"

void TIM2_init(void)
{
	RCC->APB1ENR |= (1<<0);	//TIM2��ͨ�ö�ʱ��
	
	TIM2->ARR = 10000;	//�Զ���װ�ؼĴ���������5000��
	TIM2->PSC = 7199;	//Ԥ��Ƶ������
	TIM2->DIER |= 1<<0;	//��������ж�
	TIM2->CR1 |= 0x01;	//ʹ�ܶ�ʱ��2
	MY_NVIC_Init(0,0,TIM2_IRQn,0);
}

int main(void)
{	
	Stm32_Clock_Init(9);			//ѡ������ⲿ���񾭹�PLL���໷9��Ƶ֮����Ϊϵͳʱ��
	TIM2_init();

  while(1)
	{
		//��������
	}	 
} 


//�жϺ����������жϵ�ʱ��ִ�У�˭�����ж�˭ȥִ��
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0x01)//����ж�
	{
		PAout(0) = !PAout(0);
		TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
	}				   
	
}




