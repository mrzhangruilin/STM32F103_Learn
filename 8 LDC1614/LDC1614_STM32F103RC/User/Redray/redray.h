#ifndef _REDRAY_H_
#define _REDRAY_H_

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
 
void RedRayInit(void);
 
//ѭ�����Թ�
//�Һ��� PB14
#define SEARCH_BR_PIN         GPIO_Pin_14
#define SEARCH_BR_GPIO        GPIOB
#define SEARCH_BR_CLK         RCC_APB2Periph_GPIOB
#define SEARCH_BR_IO          GPIO_ReadInputDataBit(SEARCH_BR_GPIO, SEARCH_BR_PIN)

//����� PB13
#define SEARCH_BL_PIN         GPIO_Pin_13
#define SEARCH_BL_GPIO        GPIOB
#define SEARCH_BL_CLK         RCC_APB2Periph_GPIOB
#define SEARCH_BL_IO          GPIO_ReadInputDataBit(SEARCH_BL_GPIO, SEARCH_BL_PIN)

//��ǰ�� PB1
#define SEARCH_FR_PIN         GPIO_Pin_1
#define SEARCH_FR_GPIO        GPIOB
#define SEARCH_FR_CLK         RCC_APB2Periph_GPIOB
#define SEARCH_FR_IO          GPIO_ReadInputDataBit(SEARCH_FR_GPIO, SEARCH_FR_PIN)
//��ǰ�� PB0
#define SEARCH_FL_PIN         GPIO_Pin_0
#define SEARCH_FL_GPIO        GPIOB
#define SEARCH_FL_CLK         RCC_APB2Periph_GPIOB
#define SEARCH_FL_IO          GPIO_ReadInputDataBit(SEARCH_FL_GPIO, SEARCH_FL_PIN)

#define BLACK_AREA 1
#define WHITE_AREA 0
#endif

