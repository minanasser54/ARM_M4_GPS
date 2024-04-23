#ifndef DIODriver
#define DIODriver

#include "tm4c123gh6pm.h"
#include "bit_utility.h"

void DIO_vPORTINIT(unsigned char portname);

void DIO_vSETPINDIR(unsigned char portname , unsigned char pin , unsigned char dir);

void DIO_vWRITEPIN(unsigned char portname , unsigned char pin , unsigned char dir);


#endif

