
#include "SW.h"



unsigned char button_in;
unsigned char button_prev = 0x10;


DIO_vPORTINIT("F");
DIO_vSETPINDIR("F",4,0);


unsigned char SW1_Input(void)
{
    return GPIO_PORTF_DATA_R &0x10;
}

bool SW1_ispressed(void)
{
    button_in = SW1_Input();                        
    if (button_prev != 0x10 && button_in == 0x10)   //rising edge
        return true;
    else 
        return false;

    button_prev = button_in;

}
