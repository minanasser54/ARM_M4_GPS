#include <stdio.h>
#include <stdlib.h>
#include "../UTILITIES/tm4c123gh6pm.h"
#include "../MCAL/GPIO/DIO_Driver.h"
#include "../MCAL/eeprom/eeprom.h"
#include "../UTILITIES/Bit_Utilities.h"
#include "mainFUN.h"
#include "../MCAL/STK/SysTick.h"
#include "../MCAL/UART0/UART0_PC.h"
#include "../MCAL/UART5/UART5.h"
#include "../HAL/SW/SW.h"
#include "../HAL/SW/ext_SW.h"
#include "../HAL/GPS/GPS.h"
#include "../HAL/LED/LED_interface.h"

//destination of asu foe
extern char i;
extern float destLongitude;
extern float destLatitude;
extern char swich2;
extern float distance; // will be stored
extern float lon_lat[99];
extern int* ptr; 
int main(void){


DIO_vPORTINIT(DIO_PORTA);
DIO_vPORTINIT(DIO_PORTB);
DIO_vPORTINIT(DIO_PORTC);
DIO_vPORTINIT(DIO_PORTD);
DIO_vPORTINIT(DIO_PORTE);
DIO_vPORTINIT(DIO_PORTF);			


ex_sw_init();
eeprom_init();
UART0_INIT();
UART5Init();
SysTick_Init();
LED_LedInit();
SW_Init(SW1);
SW_Init(SW2);
//LCD_init();

ptr = (int*)calloc(1,0); 
if (ptr == NULL) { 
        printf("Memory not allocated.\n"); 
         
    } 
    else { 
        printf("Memory successfully allocated using "
               "calloc.\n"); 
    } 

while(1)
{
	char i;
	bool EEPROMisDone=false;
	for (i=0;i<swich2check();i++)
{
	 LED_LedOn(LED_BLUE);
	 SysTick_Wait(200); //2s delay
	 LED_LedOff( LED_BLUE );
	 SysTick_Wait(200); //2s delay
}
    if(swich2check()==1){
          distance=0;
			
			do{
            
				     mainProgram();
            }while(distance<=100);
   }


    else if(swich2check()==2){
           distance=0; 
			do{
             mainProgram();
            }while(!SW_ispressed( SW1 ));
    }


    else if(swich2check()==3){
			 distance=0; 
            do{
	     
             mainProgram();
            }while(isDestination());
    }


    else if(swich2check()==4){
			 distance=0; 
          do{
		
             mainProgram();
            }while(~(distance<=100 || !SW_ispressed( SW1 ) ||isDestination()));
    }

    distance=0;
    i=0;
		LED_LedOn(LED_GREEN);


		

    if (SWex_ispressed())
    {
		unsigned int i;
    for (i = 0; i < sizeof(ptr); i++){
			eeprom_write(ptr[i],i,1);  //EEPROM FILE IS NOT UPLOADED YET
		}
		
      LED_LedOn(LED_RED);
      EEPROMisDone=true;
	}

if((UART0_read()=='U') &  EEPROMisDone){
		unsigned int i;
		for(i=0;i<sizeof(ptr);i++){
        UART0_write((char)ptr[i]);
    }
}

if(true){
unsigned int j;
for (j = 0; j < sizeof(lon_lat); j++){
	lon_lat[j] = 0;
 }
}
	LED_OffAll();
	//LCD_clearScreen();
   }
}
