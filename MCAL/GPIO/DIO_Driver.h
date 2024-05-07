#ifndef DIODriver
#define DIODriver

#include "../../UTILITIES/tm4c123gh6pm.h"
#include "../../UTILITIES/Bit_Utilities.h"

//*****************************************************************************
//
// Macros for PORTS
//
//*****************************************************************************
#define DIO_PORTA			0
#define DIO_PORTB			1
#define DIO_PORTC			2
#define DIO_PORTD			3
#define DIO_PORTE			4
#define DIO_PORTF			5
//*****************************************************************************
//
// Macros for PINS value
//
//*****************************************************************************
#define DIO_OUTPUT		    1
#define DIO_INPUT			0
#define DIO_HIGH			1
#define DIO_LOW				0
//*****************************************************************************

void DIO_vPORTINIT(unsigned char portname);

void DIO_vSETPINDIR(unsigned char portname , unsigned char pin , unsigned char dir);

void DIO_vWRITEPIN(unsigned char portname , unsigned char pin , unsigned char dir);


#endif

