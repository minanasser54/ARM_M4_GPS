#ifndef EEPROM_H
#define EEPROM_H
#include "../../MCAL/GPIO/DIO_Driver.h"
#include "../../UTILITIES/Bit_Utilities.h"
#include "../../UTILITIES/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 16
#define NUM_BLOCKS 32

void delay_n(int n);
void eeprom_init(void);
void eeprom_write(uint32_t data ,uint8_t addr,uint8_t blk);
uint32_t eeprom_read(uint8_t addr,uint8_t blk);
void eeprom_clear(void);
#endif
