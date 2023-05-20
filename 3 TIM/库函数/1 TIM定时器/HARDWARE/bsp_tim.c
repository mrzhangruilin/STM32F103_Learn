#include "bsp_tim.h"
#include "bsp_usart.h"

void TIM2_IRQHandler(void)
{
	printf("中断一次\n");
	TIM_ClearFlag(TIM2 , TIM_FLAG_Update);
	if(TIM_GetFlagStatus(TIM2 , TIM_FLAG_Update) == SET)
	{
		
	}
}

void TIM2_TimBaseInit(void)		//基本计数器模式
{
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	TIM_InternalClockConfig(TIM2);							//使用 TIM2 内部时钟
	
	//定义在定时器时钟(CK_INT)频率与数字滤波器(ETR，TIx)使用的采样频率之间的分频比例。
	TIM_TimBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimBaseInitStructure.TIM_Period = 5000-1;
	TIM_TimBaseInitStructure.TIM_Prescaler = 7199;
	TIM_TimBaseInitStructure.TIM_RepetitionCounter = 0;		//TIM1 和 TIM8用的
	TIM_TimeBaseInit(TIM2 , &TIM_TimBaseInitStructure);		
	
	TIM_ITConfig(TIM2 , TIM_IT_Update , ENABLE);			//使能更新中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2 , ENABLE);
}

