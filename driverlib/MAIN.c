#include <stdint.h>
#include <stdbool.h>
#include "eeprom.h"
#include "inc/tm4c123gh6pm.h"
#include <stdio.h>
/*************************** ITM **********************************************/
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000



struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;
int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}
/****************************************************************************/
int main(void){
	EEPROMInit();
	EEPROMMassErase();
	uint32_t pui32Data[10];
	uint32_t pui32Read[10];
	int i;
	
	pui32Data[0]=5555;
	pui32Data[1]=1111;
	pui32Data[2]=2222;
	pui32Data[3]=3333;
	
	EEPROMProgram(pui32Data, 0x400, sizeof(pui32Data));
	
	
	EEPROMRead(pui32Read, 0x400, sizeof(pui32Read));
		for (i =0 ; i<(sizeof(pui32Read));i++){
		if (pui32Read[i]>0){
				printf("%d",pui32Read[i]);
  			printf("\n");
		}
	}
}