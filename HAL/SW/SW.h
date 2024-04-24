
#ifndef __SW__
#define __SW__



#define  SW1      0x10
#define  SW2      0x01
#define  PORTF     'F'



void            SW_Init(unsigned char S);
unsigned char   SW_Read(unsigned char S);
bool            SW_ispressed(unsigned char S);





#endif

