#include "stdint.h"

#ifndef __UART0__
#define __UART0__ 

#define GPIO_PA10_M 0X03

void UART0_INIT(void);
uint8_t UART0_Available(void);
char UART0_read(void);
void UART0_write(char data);
void getCommand(char *str,uint8_t maxLen);
void printstr(char *str);
	



#endif
