#ifndef _BRAKE_H__
#define _BRAKE_H__


#include "main.h"
#include "show.h"
/**** ∫Í∂®“Â ******/
#define SYSTEMSTATUS_WAIT       0
#define SYSTEMSTATUS_ADD        1
#define SYSTEMSTATUS_DEL        2

#define SR_TEST_NUM             50
#define SR_TEST_THRESHOLD       25

void AT24C02_Clear(uint8_t data);
void AT24C02_Read(void);
void AT24C02_Read_N(uint8_t n);
void print_Card(uint8_t *cardid);

uint8_t RC522_Read(uint8_t SelectedSnr[4]);


uint8_t Card_Check(uint8_t *cardId);
uint8_t Card_Save(uint8_t *cardId);
uint8_t Card_Read(uint8_t index , uint8_t cardId[4]);
uint8_t Card_Del(uint8_t index);
uint8_t Check_SR(void);
void Brake_Switch(uint8_t state);
void Door_Open(void);

#endif

