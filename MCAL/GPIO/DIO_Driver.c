#include "../../UTILITIES/tm4c123gh6pm.h"
#include "../../UTILITIES/Bit_Utilities.h"
#include "DIO_Driver.h"

void DIO_vPORTINIT(unsigned char portname){
	switch(portname){
		case 'A':
		case 'a':
			SET_BIT(SYSCTL_RCGCGPIO_R,0);
			while(READ_BIT(SYSCTL_PRGPIO_R,0)==0);
			GPIO_PORTA_LOCK_R |= 0x4c4f434b;
			GPIO_PORTA_CR_R |= 0xFF;
			GPIO_PORTA_DEN_R |= 0xFF;
			GPIO_PORTA_AMSEL_R &= ~0xFF;
			break;
		case 'B':
		case 'b':
			SET_BIT(SYSCTL_RCGCGPIO_R,1);
			while(READ_BIT(SYSCTL_PRGPIO_R,1)==0);
			GPIO_PORTB_LOCK_R |= 0x4c4f434b;
			GPIO_PORTB_CR_R |= 0xFF;
			GPIO_PORTB_DEN_R |= 0xFF;
			GPIO_PORTB_AMSEL_R &= ~0xFF;
			break;
		case 'C':
		case 'c':
			SET_BIT(SYSCTL_RCGCGPIO_R,2);
			while(READ_BIT(SYSCTL_PRGPIO_R,2)==0);
			GPIO_PORTC_LOCK_R |= 0x4c4f434b;
			GPIO_PORTC_CR_R |= 0xFF;
			GPIO_PORTC_DEN_R |= 0xFF;
			GPIO_PORTC_AMSEL_R &= ~0xFF;
			break;
		case 'D':
		case 'd':
			SET_BIT(SYSCTL_RCGCGPIO_R,3);
			while(READ_BIT(SYSCTL_PRGPIO_R,3)==0);
			GPIO_PORTD_LOCK_R |= 0x4c4f434b;
			GPIO_PORTD_CR_R |= 0xFF;
			GPIO_PORTD_DEN_R |= 0xFF;
			GPIO_PORTD_AMSEL_R &= ~0xFF;
			break;
		case 'E':
		case 'e':
			SET_BIT(SYSCTL_RCGCGPIO_R,4);
			while(READ_BIT(SYSCTL_PRGPIO_R,4)==0);
			GPIO_PORTE_LOCK_R |= 0x4c4f434b;
			GPIO_PORTE_CR_R |= 0xFF;
			GPIO_PORTE_DEN_R |= 0xFF;
			GPIO_PORTE_AMSEL_R &= ~0xFF;
			break;
		case 'F':
		case 'f':
			SET_BIT(SYSCTL_RCGCGPIO_R,5);
			while(READ_BIT(SYSCTL_PRGPIO_R,5)==0);
			GPIO_PORTF_LOCK_R |= 0x4c4f434b;
			GPIO_PORTF_CR_R |= 0xFF;
			GPIO_PORTF_DEN_R |= 0xFF;
			GPIO_PORTF_AMSEL_R &= ~0xFF;
			GPIO_PORTF_PUR_R    = 0x11;
			break;
	}
}
void DIO_vSETPINDIR(unsigned char portname , unsigned char pin , unsigned char dir){
	switch (portname){
		case'A':
		case'a':
			if (dir == 1 )
				SET_BIT(GPIO_PORTA_DIR_R, pin);
			else
				CLR_BIT(GPIO_PORTA_DIR_R, pin);
			break;
		case'B':
		case'b':
			if (dir == 1 )
				SET_BIT(GPIO_PORTB_DIR_R, pin);
			else
				CLR_BIT(GPIO_PORTB_DIR_R, pin);
			break;
		case'C':
		case'c':
			if (dir == 1 )
				SET_BIT(GPIO_PORTC_DIR_R, pin);
			else
				CLR_BIT(GPIO_PORTC_DIR_R, pin);
			break;
		case'D':
		case'd':
			if (dir == 1 )
				SET_BIT(GPIO_PORTD_DIR_R, pin);
			else
				CLR_BIT(GPIO_PORTD_DIR_R, pin);
			break;
		case'E':
		case'e':
			if (dir == 1 )
				SET_BIT(GPIO_PORTE_DIR_R, pin);
			else
				CLR_BIT(GPIO_PORTE_DIR_R, pin);
			break;
		case'F':
		case'f':
			if (dir == 1 )
				SET_BIT(GPIO_PORTF_DIR_R, pin);
			else
				CLR_BIT(GPIO_PORTF_DIR_R, pin);
			break;
	}
}
void DIO_vWRITEPIN(unsigned char portname , unsigned char pin , unsigned char dir){
	switch (portname){
		case'A':
		case'a':
			if (dir == 1 )
				SET_BIT(GPIO_PORTA_DATA_R, pin);
			else
				CLR_BIT(GPIO_PORTA_DATA_R, pin);
			break;
		case'B':
		case'b':
			if (dir == 1 )
				SET_BIT(GPIO_PORTB_DATA_R, pin);
			else
				CLR_BIT(GPIO_PORTB_DATA_R, pin);
			break;
		case'C':
		case'c':
			if (dir == 1 )
				SET_BIT(GPIO_PORTC_DATA_R, pin);
			else
				CLR_BIT(GPIO_PORTC_DATA_R, pin);
			break;
		case'D':
		case'd':
			if (dir == 1 )
				SET_BIT(GPIO_PORTD_DATA_R, pin);
			else
				CLR_BIT(GPIO_PORTD_DATA_R, pin);
			break;
		case'E':
		case'e':
			if (dir == 1 )
				SET_BIT(GPIO_PORTE_DATA_R, pin);
			else
				CLR_BIT(GPIO_PORTE_DATA_R, pin);
			break;
		case'F':
		case'f':
			if (dir == 1 )
				SET_BIT(GPIO_PORTF_DATA_R, pin);
			else
				CLR_BIT(GPIO_PORTF_DATA_R, pin);
			break;
	}
}
void DIO_vTOGGLEPIN(unsigned char portname , unsigned char pin ){
	switch (portname){
		case'A':
		case'a':
			TOGGLE_BIT(GPIO_PORTA_DATA_R, pin);
			break;
		case'B':
		case'b':
			TOGGLE_BIT(GPIO_PORTB_DATA_R, pin);			
			break;
		case'C':
		case'c':
			TOGGLE_BIT(GPIO_PORTC_DATA_R, pin);
			break;
		case'D':
		case'd':
			TOGGLE_BIT(GPIO_PORTD_DATA_R, pin);
			break;
		case'E':
		case'e':
			TOGGLE_BIT(GPIO_PORTE_DATA_R, pin);
			break;
		case'F':
		case'f':
			TOGGLE_BIT(GPIO_PORTF_DATA_R, pin);
			break;
	}
}