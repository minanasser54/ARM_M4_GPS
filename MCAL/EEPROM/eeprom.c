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
    int flag = 0;
    
    // Initialize EEPROM
    flag = eeprom_start();
    
    // Check initialization status
    if (flag) {
        printf ("EEPROM initialized successfully.\n\n");
    } else {
        printf("Error: Failed to initialize EEPROM. Performing error recovery...\n");
        // Perform error recovery
        eeprom_error_recovery();
        
        // Attempt initialization again
        flag = eeprom_start();
        if (flag) {
            printf("EEPROM initialized after error recovery.\n");
        } else {
            printf("Error: EEPROM initialization failed even after error recovery.\n");
            // Handle further error recovery or exit program
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


void store_array_to_eeprom(uint8_t *array1,uint8_t *array2, uint16_t array_size, uint8_t start_blk, uint8_t start_addr) {
    uint16_t i;
		uint16_t arr1[10];
		uint16_t arr2[10];
	uint8_t current_blk = start_blk;
    uint8_t current_addr = start_addr;

    for (i = 0; i < array_size; i++) {
        printf("Writing Integer %u to address %u in block %u and Floating Point %u to address %u in block %u\n\n"
			, array1[i],current_addr, current_blk,array2[i],current_addr, current_blk+1);
        eeprom_write(array1[i],current_addr, current_blk);
      printf("Reading Integer from address %u in block %u\n", current_addr, current_blk);
				arr1[i]=eeprom_read(current_addr, current_blk);
				printf("Integer : %d\n", arr1[i]);  
			eeprom_write(array2[i],current_addr, current_blk+1);   
printf("Reading Floating Point from address %u in block %u\n", current_addr, current_blk+1);
        arr2[i] = eeprom_read(current_addr, current_blk+1);
        printf("Float : %d\n\n", arr2[i]);			
			// Increment address for next element of the array
        current_addr++;
        
        // Check if current address exceeds block size
        if (current_addr >= BLOCK_SIZE) {
            current_blk++; // Move to next block
            current_addr = 0; // Reset address to start of the block
            if (current_blk >= NUM_BLOCKS) {
                // Handle EEPROM overflow if needed
                break;
            }
        }
    }
    printf("\n");

}


