#include "redray.h"

//������Թܳ�ʼ��
void RedRayInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	//��ǰ�� PB0
	RCC_APB2PeriphClockCmd(SEARCH_FL_CLK , ENABLE);
	GPIO_InitStructure.GPIO_Pin = SEARCH_FL_PIN;//����ʹ��GPIO�ܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//����GPIOģʽ,��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(SEARCH_FL_GPIO , &GPIO_InitStructure); 	
	//��ǰ�� PB1
	RCC_APB2PeriphClockCmd(SEARCH_FR_CLK , ENABLE);
	GPIO_InitStructure.GPIO_Pin = SEARCH_FR_PIN;//����ʹ��GPIO�ܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//����GPIOģʽ,��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(SEARCH_FR_GPIO , &GPIO_InitStructure); 
	//����� PB13
	RCC_APB2PeriphClockCmd(SEARCH_BL_CLK , ENABLE);
	GPIO_InitStructure.GPIO_Pin = SEARCH_BL_PIN;//����ʹ��GPIO�ܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//����GPIOģʽ,��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(SEARCH_BL_GPIO , &GPIO_InitStructure); 
	//�Һ��� PB14
	RCC_APB2PeriphClockCmd(SEARCH_BR_CLK , ENABLE);
	GPIO_InitStructure.GPIO_Pin = SEARCH_BR_PIN;//����ʹ��GPIO�ܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//����GPIOģʽ,��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(SEARCH_BR_GPIO , &GPIO_InitStructure); 
}


