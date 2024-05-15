#include "../MCAL/GPIO/DIO_Driver.h"
#include "../MCAL/STK/Systick.h"
#include "../HAL/SW/SW.h"
#include "../HAL/SW/ext_sw.h"
#include "../HAL/GPS/GPS.h"
#include "../UTILITIES/Bit_Utilities.h"
#include "../UTILITIES/Conversion.h"
#include "../HAL/LED/LED_interface.h"
#include "../MCAL/UART0/UART0_PC.h"
#include "../MCAL/UART5/UART5.h"
#include "../MCAL/EEPROM/eeprom.h"
#include "../HAL/LCD/LCD.h"
#include "SAVE.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

float Distance(float currentA , float currentB , float destA ,float destB);
float ToRad(float DegNum);
float ToDeg(float Num);

char* floatToString(float num, char* buffer, int bufferSize) {
    if (bufferSize < 32) {
        return NULL; // Buffer size too small
    }
    sprintf(buffer, "%f", num);
    return buffer;
}
void check_mode(int *ptr){
		if(!SW_ispressed(SW1)){
			  *ptr=1;}
		if(!SW_ispressed(SW2)) {
			  *ptr=2;}}

int main(void){
	ex_sw_init();
	eeprom_init();
	UART0_INIT();
	UART5Init();
	SysTick_Init();
	LED_LedInit();
	SW_Init(SW1);
	SW_Init(SW2);
	LCD_INIT();
	LCD_CMD(clear_display);
	LCD_CMD(cursorBlink);
	int mode =0;
	int *p = & mode;
	while(1){
		check_mode(p);
		if (mode == 1){
		float distance=0.0;
		float dLon=0.0;
		float dLat=0.0;
		float cLon=0.0;
		float cLat=0.0;
				
		LED_OffAll();
		LED_LedOn(LED_RED);	
		LCD_CMD(clear_display);
		LCD_String("Accumulation Mode");
		delay_milli(2000);	
		do{			
				GPS_format();
				cLon=atof(getCurrentLongitude());
				cLat=atof(getCurrentLatitude());

				if(dLon!=0 && dLat!=0){
					LCD_CMD(clear_display);
					LCD_String("accumulating !!");
					distance+=Distance(cLon, cLat ,dLon  ,dLat); //data from gps 
					delay_milli(500);
					save_eeprom(cLon);
					delay_milli(500);
					save_eeprom(cLat);
					delay_milli(500);
					char str[32];
					LCD_CMD(clear_display);
					delay_milli(500);
					LCD_String("D= ");
					floatToString(distance, str, sizeof(str));
					LCD_String(str); //display distance num on LCD
					delay_milli(3000);				
					LCD_CMD(clear_display);
//										printstr("\n dis = ");
//										printstr(str);
//										printstr("\n");
				}
				if (cLon && cLat){
				dLon =cLon;
				dLat =cLat;
				}
							//printstr(" \n SS");
				SysTick_Wait(4000); 
							//printstr(" EE  \n");
				check_mode(p);
				if (!SW_ispressed(SW1) || mode!=1) break;
					 }while(distance<=100 );				 
			
			//LED_LedOff(LED_RED);
			LED_OffAll();
			LED_LedOn(LED_GREEN);
			SysTick_Wait(5000); 
			LED_OffAll();
			mode=0;
		}
		if (mode == 2){
			LED_OffAll();
			LED_LedOn(LED_GREEN);
			LED_LedOn(LED_RED);
			LCD_CMD(clear_display);
			LCD_String("Retrieving Mode");
			bool wait =true;
			
			do{
			wait=true;
			if((UART0_read()=='U')){
			wait=false;
			fetch_eeprom(); 
			eeprom_clear();
			}else{
			check_mode(p);}
			}while(wait && mode==2);
			mode=0;
			LCD_CMD(clear_display);
			LCD_String("Retrieving DONE");
			SysTick_Wait(3000); 
			LCD_CMD(clear_display);
			LED_OffAll();
		}
		
			
		//LED_OffAll();
		LED_LedOn(LED_BLUE);
		LCD_CMD(clear_display);
		LCD_String("sw1 acc sw2 retrive");
		SysTick_Wait(10000); 
   }
}

float ToDeg(float Num){
	int degree =(int) Num/100;
	float minutes =Num-(float)degree*100;
	return(degree+(minutes/60));
}

float ToRad(float DegNum){
    return (DegNum*(PI/180));
}
//float truncate(float copy_f32FloatValue)
//{
//    copy_f32FloatValue = floor(copy_f32FloatValue * 1000000) / (float)1000000.0;
//    return copy_f32FloatValue;
//}
//float trun(float copy_f32FloatValue)
//{
//    copy_f32FloatValue = floor(copy_f32FloatValue * 1000) / (float)1000.0;
//    return copy_f32FloatValue;
//}
float Distance(float currentA , float currentB , float destA ,float destB){
    float currentA_RAD = ToRad(ToDeg(currentA));
    float currentB_RAD = ToRad(ToDeg(currentB));
    float destA_RAD = ToRad(ToDeg(destA));
    float destB_RAD = ToRad(ToDeg(destB));
    float aDiff=destA_RAD-currentA_RAD;
    float bDiff=destB_RAD-currentB_RAD;
    float a=pow(sin(bDiff/2),2)+cos(currentB_RAD)*cos(destB_RAD)*pow(sin(aDiff/2),2);
    float Dis=2*atan2(sqrt(a),sqrt(1-a));
		return EARTH_RADIUS*Dis;
}
