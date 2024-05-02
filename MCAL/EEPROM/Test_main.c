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

	// TEST FOR WRITE AND READ FOR SINGLE ELEMENT 
		
		uint32_t x=10 ;   // Data
		uint8_t address =0;   //address(0-15)
		uint8_t block_number =0;  // block number (0-31)
		uint32_t j ;    // reciever
		eeprom_init();   // EEPROM initalization 
		eeprom_write( x , address , block_number); 
		j=eeprom_read(address, block_number);
		printf("j = %u", j );
	
	// TEST FOR STORING AND RECIEVING ARRAY 
		
		uint8_t my_arrayINT[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};   // ARRAY FOR INTEGER VALUES
    uint8_t my_arrayFLT[] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};  // ARRAY FOR FLOAT VALUES
		eeprom_init();
		store_array_to_eeprom(my_arrayINT , my_arrayFLT , 10 /* ARRAY SIZE */  , 0 , 0 );
    
		return 0 ;
		while(1){}
}


/************************************************
Write to memory
To write to EEPROM you need to provide block number (0 - 31) and address (0 - 15) along with data. For example to store 10 at the beginning of block number 1, we can call the write funnction as follows.

  eeprom_write(10,0,1);

Read from memory
To read from EEPROM you need to provide block number (0 - 31) and address (0 - 15). Data stored at the location is then returned. For example to read data from address number 5 of block 2, we can call the read function as follows. The returned data is stored in 'value' variable.

  data = eeprom_read(5,2);
*/