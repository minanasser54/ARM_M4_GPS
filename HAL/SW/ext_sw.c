#include <stdbool.h>
#include <stdio.h>

#include "../../MCAL/GPIO/DIO_Driver.h"
#include "../../UTILITIES/Bit_Utilities.h"
#include "../../UTILITIES/tm4c123gh6pm.h"
#include "ext_sw.h"

void ex_sw_init(void){
	
	DIO_vPORTINIT(PORTA);
	DIO_vSETPINDIR(PORTA,4,0);
	GPIO_PORTA_AFSEL_R &= ~ext_sw_mask;
	GPIO_PORTA_PCTL_R &= ~0x000F0000;
	GPIO_PORTA_PUR_R |= ext_sw_mask;
	
}

unsigned char   ex_SW_Read(void){
	
	return GPIO_PORTA_DATA_R & ext_sw_mask;
}
