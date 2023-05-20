#ifndef	__BSP_AT24C02_H_
#define	__BSP_AT24C02_H_

#include "bsp_i2c.h"

#define AT24C02_ADDR    0x50

void AT24C02_WriteByte(uint8_t addr, uint8_t dataAdd, unsigned char *data, uint8_t len);    //дAT24C02һ���ֽ�,addr����λ��ַ
void AT24C02_ReadByte(uint8_t addr, uint8_t dataAdd, unsigned char *data, uint8_t len);		//��AT24C02���һ���ֽڣ�addr����λ��ַ


#endif
