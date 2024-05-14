#include "eeprom.h"
#include <stdint.h>
#include <stdio.h>
#include "../../MCAL/GPIO/DIO_Driver.h"
#include "../../UTILITIES/Bit_Utilities.h"
#include "../../UTILITIES/tm4c123gh6pm.h"

void delay_n(int n)
{
	int i;
	for(i=0;i<n;i++)
	;
}

int eeprom_start(void)
{
	SYSCTL_RCGCEEPROM_R = 0x01;
	delay_n(15);
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
		if((EEPROM_EESUPP_R & EEPROM_EESUPP_ERETRY) | (EEPROM_EESUPP_R & EEPROM_EESUPP_PRETRY))
		{
			return -1;
		}
	SYSCTL_SREEPROM_R = SYSCTL_SREEPROM_R0;
	SYSCTL_SREEPROM_R = 0;
	delay_n(15);
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
		if((EEPROM_EESUPP_R & EEPROM_EESUPP_ERETRY) | (EEPROM_EESUPP_R & EEPROM_EESUPP_PRETRY))
		{
			return -1;
		}
		return 1;
}
void eeprom_error_recovery(void)
{
	EEPROM_EESUPP_R = EEPROM_EESUPP_START;
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
}
void eeprom_init(void)
{
		
    int flag = 0;   
    flag = eeprom_start();
    if (flag) {
    } else {
        eeprom_error_recovery();
        flag = eeprom_start();
        if (flag) {
					
        } else {

        }
    }

}
void eeprom_write(uint32_t data,uint8_t addr,uint8_t blk)
{
	EEPROM_EEBLOCK_R = blk;//Block number
	EEPROM_EEOFFSET_R =  addr; //offset within the block
	EEPROM_EERDWR_R = data; //data written 
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
	delay_n(5);
}
void eeprom_clear(void){
	char i;
	char j;
	for(i=1;i<=32;i++){
					for(j=1;j<=16;j++){
						eeprom_write(0,j,i);
	}
	}}
uint32_t eeprom_read(uint8_t addr,uint8_t blk)
{
	uint32_t data;
	EEPROM_EEBLOCK_R = blk;//Block number
	EEPROM_EEOFFSET_R =  addr;
	data = EEPROM_EERDWR_R;
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
	delay_n(5);
	return data;
}