#include "eeprom.h"


/*************************** ITM **********************************************/
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000
#define BLOCK_NUMBER 0

//REQUIRED TWO FUNCTIONS TO WRITE AND READ ARRAYS IN EEPROM 

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







int main(void) {		
		uint8_t address =0;   //address(0-15)
		uint8_t block_number =0;  // block number (0-31)
		uint32_t j ;    // reciever
		eeprom_init();
		
		while(1){}
}
