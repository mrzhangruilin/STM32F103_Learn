#include "redray.h"

//红外光电对管初始化
void RedRayInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	//左前轮 PB0
	RCC_APB2PeriphClockCmd(SEARCH_FL_CLK , ENABLE);
	GPIO_InitStructure.GPIO_Pin = SEARCH_FL_PIN;//配置使能GPIO管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,输入上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度
	GPIO_Init(SEARCH_FL_GPIO , &GPIO_InitStructure); 	
	//右前轮 PB1
	RCC_APB2PeriphClockCmd(SEARCH_FR_CLK , ENABLE);
	GPIO_InitStructure.GPIO_Pin = SEARCH_FR_PIN;//配置使能GPIO管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,输入上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度
	GPIO_Init(SEARCH_FR_GPIO , &GPIO_InitStructure); 
	//左后轮 PB13
	RCC_APB2PeriphClockCmd(SEARCH_BL_CLK , ENABLE);
	GPIO_InitStructure.GPIO_Pin = SEARCH_BL_PIN;//配置使能GPIO管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,输入上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度
	GPIO_Init(SEARCH_BL_GPIO , &GPIO_InitStructure); 
	//右后轮 PB14
	RCC_APB2PeriphClockCmd(SEARCH_BR_CLK , ENABLE);
	GPIO_InitStructure.GPIO_Pin = SEARCH_BR_PIN;//配置使能GPIO管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,输入上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度
	GPIO_Init(SEARCH_BR_GPIO , &GPIO_InitStructure); 
}


