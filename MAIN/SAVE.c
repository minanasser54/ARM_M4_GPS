#include "SAVE.h"
#include <stdint.h>
#include "../MCAL/EEPROM/eeprom.h"
#include "../MCAL/UART0/UART0_PC.h"

static uint8_t blk =0;
static uint8_t addr =0;


void save_eeprom(float d1){
	uint32_t d2 = (uint32_t)(d1*10000); 
	if (blk < 32){
		   eeprom_write(d2,addr++, blk);
	if (addr == 16) {
        blk++;
        addr = 0; // Reset address to start of the block
  }
	}else{}
}


void fetch_eeprom(void){
	char i;
	char j;
	for(i=0;i<32;i++){
		for(j=0;j<16;j++){
			char buffer[11]; // Make sure this is large enough to hold the converted string
			if (eeprom_read(j,i) !=0){
			sprintf(buffer, "%lu", eeprom_read(j,i));
			printstr(buffer);
			printstr("\n");
		}
	}
}
	printstr("saved \n ");
}