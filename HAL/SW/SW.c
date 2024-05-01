#include "../../UTILITIES/Bit_Utilities.h"
#include "../../UTILITIES/tm4c123gh6pm.h"
#include "SW.h"



unsigned char button_in;
unsigned char button_prev;



void PORTF_Init(void)
{
  SET_BIT(SYSCTL_RCGCGPIO_R,5);
	while(READ_BIT(SYSCTL_PRGPIO_R,5)==0);
	GPIO_PORTF_LOCK_R   |= 0x4c4f434b;
	GPIO_PORTF_CR_R     |= 0x11;
	GPIO_PORTF_DEN_R    |= 0x11;
	GPIO_PORTF_AMSEL_R  &= ~0x11;
	GPIO_PORTF_PUR_R    = 0x11;	
}

void SW_Init(unsigned char S)
{
    switch (S)
    {
    case SW1:
        PORTF_Init();
        CLR_BIT(GPIO_PORTF_DIR_R, 4);
        break;
    case SW2:
        PORTF_Init();
        CLR_BIT(GPIO_PORTF_DIR_R, 0);
        break;
    
    default:
        break;
    }

}


unsigned char SW_Read(unsigned char S)
{
    switch (S)
    {
    case SW1:
    
        return GPIO_PORTF_DATA_R &SW1;
        break;
    case SW2:
        return GPIO_PORTF_DATA_R &SW2;
        break;
    
    default:
        break;
    }
}



bool SW_ispressed(unsigned char S)
{
    switch (S)
    {
    case SW1:
        button_in = SW_Read(SW1);                        
        if (button_prev != 0x10 && button_in == 0x10)   //rising edge
            return true;
        else 
            return false;
        button_prev = button_in;
        break;


    case SW2:
        button_in = SW_Read(SW2);                        
        if (button_prev != 0x01 && button_in == 0x01)   //rising edge
            return true;
        else 
            return false;
        button_prev = button_in;
        break;
    
    default:
        break;
    }




}