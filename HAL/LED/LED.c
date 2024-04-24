/**< UTIL */
#include "../../UTILITIES/Bit_Utilities.h"
#include "../../UTILITIES/tm4c123gh6pm.h"
/**< LED_HAL */
#include "../../HAL/LED/LED_interface.h"

void LED_LedInit (void){
		SYSCTL_RCGCGPIO_R |= PF_mask;
		while ((SYSCTL_PRGPIO_R & PF_mask) == 0){};
		GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY ;
		GPIO_PORTF_CR_R |= PF123_mask;
		GPIO_PORTF_AMSEL_R &= ~PF123_mask;
		GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
		GPIO_PORTF_AFSEL_R &= ~PF123_mask;
		GPIO_PORTF_DIR_R |= PF123_mask;
		GPIO_PORTF_DEN_R |= PF123_mask;
		GPIO_PORTF_DATA_R &= ~PF123_mask;
}

void LED_LedOn(unsigned char copy_LedColour) {
    switch (copy_LedColour) {
        case LED_BLUE:
            GPIO_PORTF_DATA_R |= (1 << LED_BLUE_PIN);
            break;
        case LED_GREEN:
            GPIO_PORTF_DATA_R |= (1 << LED_GREEN_PIN);
            break;
        case LED_RED:            
            GPIO_PORTF_DATA_R |= (1 << LED_RED_PIN);
            break;
        default:
            // Error state 
            break;
    }
}

void LED_LedOff(unsigned char copy_LedColour) {
    switch (copy_LedColour) {
        case LED_BLUE:
            GPIO_PORTF_DATA_R &= ~(1 << LED_BLUE_PIN);
            break;
        case LED_GREEN:
            GPIO_PORTF_DATA_R &= ~(1 << LED_GREEN_PIN);
            break;
        case LED_RED:
            GPIO_PORTF_DATA_R &= ~(1 << LED_RED_PIN);
            break;
        default:
            // Error state 
            break;
    }
}

void LED_OffAll(void) {
    GPIO_PORTF_DATA_R &= ~((1 << LED_RED_PIN) | (1 << LED_BLUE_PIN) | (1 << LED_GREEN_PIN));
}
