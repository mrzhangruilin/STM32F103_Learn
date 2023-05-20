#ifndef __MY_LED_H
#define __MY_LED_H 		

#include "stm32f10x.h" 

void MY_LED_Init(void);
#define LED_on		LED1_on;LED2_on;LED3_on;LED4_on
#define LED1_on		PAout(0)=0
#define LED2_on		PAout(1)=0
#define LED3_on		PAout(2)=0
#define LED4_on		PAout(3)=0

#define LED_off		LED1_off;LED2_off;LED3_off;LED4_off
#define LED1_off	PAout(0)=1
#define LED2_off	PAout(1)=1
#define LED3_off	PAout(2)=1
#define LED4_off	PAout(3)=1



#endif
