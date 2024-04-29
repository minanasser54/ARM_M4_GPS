#include "eeprom.h"

void delay_n(int n)
{
	int i;
	for(i=0;i<n;i++)
	;
}

int eeprom_start(void)
{
	//	Before writing to any EEPROM registers, the clock to the EEPROM module must be enabled through
	//the EEPROM Run Mode Clock Gating Control (RCGCEEPROM) register (see page 356 of Tiva datasheet) and the
	//following initialization steps must be executed:
	SYSCTL_RCGCEEPROM_R = 0x01;
	
	//Insert delay (6 cycles plus function call overhead).
	delay_n(15);
	
	//Poll the WORKING bit in the EEPROM Done Status (EEDONE) register until it is clear, indicating
	//that the EEPROM has completed its power-on initialization. When WORKING=0, continue.
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING)
		;
	
	//Read the PRETRY and ERETRY bits in the EEPROM Support Control and Status (EESUPP)
	//register. If either of the bits are set, return an error, else continue.
		if((EEPROM_EESUPP_R & EEPROM_EESUPP_ERETRY) | (EEPROM_EESUPP_R & EEPROM_EESUPP_PRETRY))
		{
			return -1;
		}
		
	//Reset the EEPROM module using the EEPROM Software Reset (SREEPROM) register at
	//offset 0x558 in the System Control register space.
	SYSCTL_SREEPROM_R = SYSCTL_SREEPROM_R0;
		;
		;
		;
	SYSCTL_SREEPROM_R = 0;
	
	//Insert delay (6 cycles plus function call overhead).
	delay_n(15);
		
	//Poll the WORKING bit in the EEPROM Done Status (EEDONE) register to determine when it is
	//clear. When WORKING=0, continue.
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING)
		;
	
	//Read the PRETRY and ERETRY bits in the EESUPP register. If either of the bits are set, return
	//an error, else the EEPROM initialization is complete and software may use the peripheral as
	//normal.
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
	int flag=0;
	flag = eeprom_start();
	if(flag)
		;
	else
		eeprom_error_recovery();
}

void eeprom_write(uint32_t data,uint8_t addr,uint8_t blk)
{
	EEPROM_EEBLOCK_R = blk;//Block number
	EEPROM_EEOFFSET_R =  addr; //offset within the block
	EEPROM_EERDWR_R = data; //data written 
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
	delay_n(5);
}

int eeprom_read(uint8_t addr,uint8_t blk)
{
	int data;
	EEPROM_EEBLOCK_R = blk;//Block number
	EEPROM_EEOFFSET_R =  addr;
	data = EEPROM_EERDWR_R;
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
	delay_n(5);
	return data;
}
