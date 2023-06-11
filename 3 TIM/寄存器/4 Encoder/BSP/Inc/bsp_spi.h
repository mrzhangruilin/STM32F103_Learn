#ifndef __BSP_SPI_H_
#define	__BSP_SPI_H_

#include "stm32f10x.h"                  // Device header
#include "sys.h"

#define SPI_NSS_0 PAout(4)=0
#define SPI_NSS_1 PAout(4)=1

void SPI_Init(void);
u8 SPI_ReadWriteByte(u8 data);

#endif

