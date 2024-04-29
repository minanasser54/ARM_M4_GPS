#ifndef __UART5__
#define __UART5__
#include "stdint.h"

void UART5Init();
int UART5_ReadAvailable(void);
char UART5_read();
void UART5_write(char c);
void U5_getCommand(char *str, int maxLen);
uint8_t UART5_Available(void);
void U5_printstr(char *str);

#endif 
