#ifndef	__BSP_AT24C02_H_
#define	__BSP_AT24C02_H_

#include "bsp_i2c.h"


void AT24C02_WriteByte(u8 addr, u8 dataAdd, unsigned char *data, u8 len);		//写AT24C02一个字节,addr是七位地址
void AT24C02_ReadByte(u8 addr, u8 dataAdd, unsigned char *data, u8 len);		//从AT24C02里读一个字节，addr是七位地址
#endif
