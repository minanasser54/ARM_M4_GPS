#ifndef SW
#define SW
#include <stdbool.h>
#include <stdio.h>

#define  SW1   	0x10
#define  SW2   	0x01


void 					PORTF_Init(void);
void                    SW_Init(unsigned char S)
unsigned char           SW_Read(unsigned char S);
bool 					SW_ispressed(unsigned char);




#endif