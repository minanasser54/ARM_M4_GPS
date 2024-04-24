
#include <stdbool.h>
#include <stdio.h>

#include "../../MCAL/GPIO/DIO_Driver.h"
#include "../../UTILITIES/Bit_Utilities.h"
#include "../../UTILITIES/tm4c123gh6pm.h"
#include "SW.h"



unsigned char button_in;
unsigned char button_prev = 0x10;



void SW_Init(unsigned char S)
{
    switch (S)
    {
    case SW1:
        DIO_vPORTINIT(PORTF);
        DIO_vSETPINDIR(PORTF,4,0);
        break;
    case SW2:
        DIO_vPORTINIT(PORTF);
        DIO_vSETPINDIR(PORTF,0,0);
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
