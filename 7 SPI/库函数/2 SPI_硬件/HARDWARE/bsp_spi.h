#ifndef _BSP_SPI_H__
#define	_BSP_SPI_H__

#include "stm32f10x.h"                  // Device header

#define SPIx                SPI1
#define SPI_Clock           RCC_APB2Periph_SPI1
#define SPI_GPIO_Clock      RCC_APB2Periph_GPIOA

/* SCK/MOSI/MISO都配置为复用推挽输出，NSS由软件控制配置为普通的推挽输出 */
#define SPI_SCK_GPIO_PORT           GPIOA
#define SPI_SCK_GPIO_MODE           GPIO_Mode_AF_PP
#define SPI_SCK_GPIO_SPEED          GPIO_Speed_50MHz
#define SPI_SCK_GPIO_PIN            GPIO_Pin_5

#define SPI_MOSI_GPIO_PORT          GPIOA
#define SPI_MOSI_GPIO_MODE          GPIO_Mode_AF_PP
#define SPI_MOSI_GPIO_SPEED         GPIO_Speed_50MHz
#define SPI_MOSI_GPIO_PIN           GPIO_Pin_7

#define SPI_MISO_GPIO_PORT          GPIOA
#define SPI_MISO_GPIO_MODE          GPIO_Mode_AF_PP
#define SPI_MISO_GPIO_SPEED         GPIO_Speed_50MHz
#define SPI_MISO_GPIO_PIN           GPIO_Pin_6

#define SPI_NSS_GPIO_PORT          GPIOA
#define SPI_NSS_GPIO_MODE          GPIO_Mode_Out_PP
#define SPI_NSS_GPIO_SPEED         GPIO_Speed_50MHz
#define SPI_NSS_GPIO_PIN           GPIO_Pin_4         //因为串行FLASH的CS引脚是PA4，SPI的NSS要和串行的一致

#define SPI_RST_GPIO_PORT          GPIOA
#define SPI_RST_GPIO_MODE          GPIO_Mode_Out_PP
#define SPI_RST_GPIO_SPEED         GPIO_Speed_50MHz
#define SPI_RST_GPIO_PIN           GPIO_Pin_0

/* 配置SPI信息 */
#define SPIx_BaudRatePrescaler     SPI_BaudRatePrescaler_4//四分频，SPI1挂载在APB2上，四分频后波特率为18MHz
#define SPIx_CPHA                  SPI_CPHA_2Edge//偶数边沿采样
#define SPIx_CPOL                  SPI_CPOL_High//空闲时SCK高电平
#define SPIx_CRCPolynomial         7//不使用CRC功能，所以无所谓
#define SPIx_DataSize              SPI_DataSize_8b//数据帧格式为8位
#define SPIx_Direction             SPI_Direction_2Lines_FullDuplex
#define SPIx_FirstBit              SPI_FirstBit_MSB//高位先行
#define SPIx_Mode                  SPI_Mode_Master//主机模式
#define SPIx_NSS                   SPI_NSS_Soft//软件模拟

#define RST_H   GPIO_SetBits(GPIOA , GPIO_Pin_0)
#define RST_L   GPIO_ResetBits(GPIOA , GPIO_Pin_0)

void SPI1_Init(void);
unsigned char SPI_ReadWriteByte(unsigned char byte);
void SPI_NSS_Set(void);
void SPI_NSS_ReSet(void);
#endif


