#ifndef	__BSP_AT24C02_H_
#define	__BSP_AT24C02_H_

#include "bsp_i2c.h"


void AT24C02_WriteByte(u8 addr, u8 dataAdd, unsigned char *data, u8 len);		//дAT24C02һ���ֽ�,addr����λ��ַ
void AT24C02_ReadByte(u8 addr, u8 dataAdd, unsigned char *data, u8 len);		//��AT24C02���һ���ֽڣ�addr����λ��ַ
#endif
