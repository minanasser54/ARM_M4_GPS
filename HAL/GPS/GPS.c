#include "GPS.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "../../MCAL/UART5/UART5.h"
#include "../../MCAL/UART0/UART0_PC.h"
#include "../../MCAL/STK/Systick.h"
#include "../../UTILITIES/Conversion.h"
#include <stdio.h> 
#define MAX_BUFFER_SIZE 256

char GPS[80];
char latitude[11], longitude[12];
//, speed[5]
/**
 * Description :
 * Checking Correct Log
 * Reading it from UART5 and saving it in GPS array
 * $GNRMC,204520.00,A,5109.0262239,N,11401.8407338,W,0.004,102.3,130522,0.0,E,D*3B
 */

void readLineFromGPS(char* buffer, int maxLength) {
    int i = 0;
    char c;
    bool foundStart = false;
    bool foundEnd = false;
    while (i < maxLength - 1) {
        // Assuming UART read function is named uart_read_char()
        c = UART5_read();
				UART5_write(c);
        // Check for the start of a new sentence
        if (c == '$') {
            // Reset the buffer and index
            i = 0;
            buffer[i++] = c;
            foundStart = true;
            foundEnd = false;
        } else if (foundStart && c == '*') {
            // End of data, null-terminate the string
            buffer[i] = '\0';
            foundEnd = true;
        } else if (foundStart && !foundEnd) {
            // Add character to buffer
            buffer[i++] = c;
        }
        if (foundEnd && strncmp(buffer, "$GPRMC,", 7) == 0) {
            break; // Exit loop if GPRMC sentence
        }
        if (foundEnd) {
            i = 0; // Reset index if not a GPRMC sentence
            foundStart = false;
            foundEnd = false;
        }
    }
}
//, char* speed
void parseGPRMC(char* sentence, char* latitude, char* longitude) {
		int i ;
    char* token;
    token = strtok(sentence, ",");
    if (token == NULL || strcmp(token, "$GPRMC") != 0) {
        return; // Not a valid GPRMC sentence
    }
    // Skip tokens we are not interested in
    for ( i = 0; i < 3; i++) {
        token = strtok(NULL, ",");
        if (token == NULL) {
            return; // Sentence is too short
        }
    }
    // Copy the latitude
    strncpy(latitude, token, 10);
    if (strcmp(token, "N") != 0) {
        token = strtok(NULL, ",");
        if (token == NULL) {
            return; // Sentence is too short
        }
    }
    for ( i = 0; i < 1; i++) {
        token = strtok(NULL, ",");
        if (token == NULL) {
            return; // Sentence is too short
        }
    }
    // Copy the longitude
    strncpy(longitude, token, 11);
    // Copy the longitude direction (E/W)
    // Skip the token if it is 'E', otherwise skip the next token (which is the longitude direction)
    if (strcmp(token, "E") != 0) {
        token = strtok(NULL, ",");
        if (token == NULL) {
            return; // Sentence is too short
        }
    }
    // Skip more tokens
    for ( i = 0; i < 1; i++) {
        token = strtok(NULL, ",");
        if (token == NULL) {
            return; // Sentence is too short
        }
    }
    // Copy the speed
    //strncpy(speed, token, 5);
}

char* GPS_read(){
	char buffer[MAX_BUFFER_SIZE];
	readLineFromGPS(buffer, MAX_BUFFER_SIZE);
	SysTick_Wait(1);
	return buffer;
}

void GPS_format(void){
	 strncpy(GPS,GPS_read(),80);
					//printstr(GPS);
				//	parseGPRMC(GPS, latitude, longitude, speed);
					parseGPRMC(GPS, latitude, longitude);
//					printstr("\n");
//					printstr(latitude);
//					printstr("\n");
//					SysTick_Wait(1);
//					printstr(longitude);
//					printstr("\n");
//					SysTick_Wait(1);
//					printstr(speed);
//					printstr("\n");
}
char* getCurrentLongitude(){
return longitude;
}
char* getCurrentLatitude(){
return latitude;
}

//char* getCurrentSpeed(){
//return speed;
//}
