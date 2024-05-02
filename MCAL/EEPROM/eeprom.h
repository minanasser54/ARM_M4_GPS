#ifndef EEPROM_H
#define EEPROM_H
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 16
#define NUM_BLOCKS 32

void delay_n(int n);
void eeprom_init(void);
void eeprom_write(uint32_t data ,uint8_t addr,uint8_t blk);
int eeprom_read(uint8_t addr,uint8_t blk);
void store_array_to_eeprom(uint8_t *array1,uint8_t *array2, uint16_t array_size, uint8_t start_blk, uint8_t start_addr);
#endif
