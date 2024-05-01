/******************************< HAL ******************************/
/**< GPS */
#include "GPS.h"
/******************************< SYSTEM ****************************/
#include <stdlib.h>
#include <math.h>
#include <string.h>
/******************************< MCAL ******************************/
#include "../../MCAL/UART5/UART5.h"
/******************************< Global Variables *****************/
float currentLongitude,currentLatitude,currentSpeed;
char GPS_logName[]="$GPRMC,";
char GPS[80];
char* token;
char GPS_formated[12][20];

/******************************< Function Implementation ******************************/

/**
 * Description :
 * Checking Correct Log
 * Reading it from UART5 and saving it in GPS array
 * $GNRMC,204520.00,A,5109.0262239,N,11401.8407338,W,0.004,102.3,130522,0.0,E,D*3B
 */

void GPS_read(){
char correct_log=1;
char recievedChar;
char GPSarrayCounter=0;

do{	
char i;	
for(i=0;i<strlen(GPS_logName);i++){     //Checking Correct Log	
if(UART5_read()!=GPS_logName[i])
    correct_log=0;          
	 
}
}while(correct_log);

strcpy(GPS,"");

do{
recievedChar=UART5_read();
GPS[GPSarrayCounter++]=recievedChar;
}while(recievedChar!='*');

}

/**
 * Description :
 * Extracting Longitude, Latitude, Speed from GPS array
 * saving info in currentLongitude,currentLatitude,currentSpeed Variables;
 */


void GPS_format(){

char GPS_formated_counter=0;
token=strtok(GPS,",");

do{
strcpy(GPS_formated[GPS_formated_counter],token);
token=strtok(NULL,",");
GPS_formated_counter++;
}while(token!=NULL);



if(strcmp(GPS_formated[1],"A")==0){ //Checking data validity
	currentLongitude=(strcmp(GPS_formated[5],"E")==0)?atof(GPS_formated[4]):-atof(GPS_formated[4]);
  currentLatitude=(strcmp(GPS_formated[3],"N")==0)?atof(GPS_formated[2]):-atof(GPS_formated[2]);
	currentSpeed=atof(GPS_formated[6]);//if 0 don't take new points
}

}

/**
 * Description :
 * Returning Coordinates and CurrentSpeed;
 */

float getCurrentLongitude(){
return currentLongitude;
}

float getCurrentLatitude(){
return currentLatitude;
}

float getCurrentSpeed(){
return currentSpeed;
}
