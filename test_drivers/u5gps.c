#include "../UTILITIES/Bit_Utilities.h"
#include "../UTILITIES/tm4c123gh6pm.h"
#include "../MCAL/UART0/UART0_PC.h"
#include "../MCAL/UART5/UART5.h"
#include "../MCAL/STK/SysTick.h"
#include "../HAL/GPS/GPS.h"
#include "LCD.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

int main(void){
	char data[5]="MINA";
	UART5Init();
	UART0_INIT();
	SysTick_Init();

	printstr("SCREEN ");	
	SysTick_Wait(100);

	while(1){
		printstr("INPUT : ");	
		printstr("\n");
		GPS_read();
		//GPS_format();
		printstr("\n");
	}
}

