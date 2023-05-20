#ifndef _BSP_SPI_H__
#define	_BSP_SPI_H__

#include "stm32f10x.h"                  // Device header

//引脚  复用    SPI1
//RST   PA1     PA1
//MISO  PA4     PA6
//MOSI  PA5     PA7
//SCK   PA6     PA5
//NSS   PA7     PA4
#define SPI_RST_PIN                    GPIO_Pin_1
#define SPI_RST_PORT                   GPIOA
#define SPI_RST_CLK                    RCC_APB2Periph_GPIOA  
        
#define SPI_MISO_PIN                   GPIO_Pin_6
#define SPI_MISO_PORT                  GPIOA
#define SPI_MISO_CLK                   RCC_APB2Periph_GPIOA  
        
#define SPI_MOSI_PIN                   GPIO_Pin_7
#define SPI_MOSI_PORT                  GPIOA
#define SPI_MOSI_CLK                   RCC_APB2Periph_GPIOA  
        
#define SPI_SCK_PIN                    GPIO_Pin_5 
#define SPI_SCK_PORT                   GPIOA
#define SPI_SCK_CLK                    RCC_APB2Periph_GPIOA 
        
#define SPI_NSS_PIN                    GPIO_Pin_4  
#define SPI_NSS_PORT                   GPIOA
#define SPI_NSS_CLK                    RCC_APB2Periph_GPIOA 

#define RST_H                            GPIO_SetBits(SPI_RST_PORT, SPI_RST_PIN)
#define RST_L                            GPIO_ResetBits(SPI_RST_PORT, SPI_RST_PIN)
#define MOSI_H                           GPIO_SetBits(SPI_MOSI_PORT, SPI_MOSI_PIN)
#define MOSI_L                           GPIO_ResetBits(SPI_MOSI_PORT, SPI_MOSI_PIN)
#define SCK_H                            GPIO_SetBits(SPI_SCK_PORT, SPI_SCK_PIN)
#define SCK_L                            GPIO_ResetBits(SPI_SCK_PORT, SPI_SCK_PIN)
#define NSS_H                            GPIO_SetBits(SPI_NSS_PORT, SPI_NSS_PIN)
#define NSS_L                            GPIO_ResetBits(SPI_NSS_PORT, SPI_NSS_PIN)
#define READ_MISO                        GPIO_ReadInputDataBit(SPI_MISO_PORT, SPI_MISO_PIN)

void SPI_GPIO_Init(void);
unsigned char SPI_ReadWriteByte(unsigned char byte);
void SPI_NSS_Set(void);
void SPI_NSS_ReSet(void);
#endif


