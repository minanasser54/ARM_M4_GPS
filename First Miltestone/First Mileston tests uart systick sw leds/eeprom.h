#ifndef EEPROM_H
#define EEPROM_H
#include "tm4c123gh6pm.h"

void delay_n(int n);
void eeprom_init(void);
void eeprom_write(uint32_t data,uint8_t addr,uint8_t blk);
int eeprom_read(uint8_t addr,uint8_t blk);

#endif
