#ifndef __HAL_LED_INTERFACE_H__
#define __HAL_LED_INTERFACE_H__


/********************************< MACROS for colours ********************************/
#define LED_RED  	 	1
#define LED_BLUE    2
#define LED_GREEN	  3
/**********************************< _SELECT_MC_PIN_ ***************************************/
#define LED_RED_PIN  	  1
#define LED_BLUE_PIN 		2
#define LED_GREEN_PIN	  3
/**********************************< SOME_Masks ***************************************/
#define PF123_mask             0x0E
#define PF_mask                0x20
/********************************< functions for LEDs *********************************/
/** \brief	The function LED_voidLedInit initializes the direction of three LEDs, namely a blue LED, a green LED, 
 *			and a red LED by configuring the corresponding pins of the microcontroller as output pins.
 *
 *			The function first calls DIO_voidInit function which initializes the microcontroller's general-purpose input/output (GPIO) pins, 
 *			specifically the ones associated with port F.
 *
 *			Then, the function configures the direction of each LED by calling DIO_u8SetPinDirection function three times, passing the port number (DIO_u8_PORTF) and the pin numbers (LED_BLUE_PIN, LED_GREEN_PIN, and LED_RED_PIN) as 
 *			arguments with the third argument being DIO_u8_OUTPUT to set the pins as output.
 *			This function is likely part of a larger program that controls the behavior of the LEDs.
 *
 * \param	void
 * \return	void
 *
 */ 
void LED_LedInit(void);

void LED_LedOn(unsigned char copy_u8LedColour);	    

void LED_LedOff(unsigned char copy_u8LedColour);	      

void LED_OffAll(void);



#endif //__HAL_LED_INTERFACE_H__
