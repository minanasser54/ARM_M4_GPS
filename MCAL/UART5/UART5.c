#include "../../UTILITIES/Bit_Utilities.h"
#include "../../UTILITIES/tm4c123gh6pm.h"
#include "UART5.h"
#include "stdint.h"
#include "string.h"

void UART5Init(){
 SYSCTL_RCGCUART_R |=SYSCTL_RCGCUART_R5;
 SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R4;
 UART5_CTL_R &= ~UART_CTL_UARTEN;
// SET BRD
//BR = 9600 bits/sec
//16*10^6/(16*9600) = 104.16667
 UART5_IBRD_R = 104;
 UART5_FBRD_R = 11;
 //UART5_CC_R = UART_CC_CS_SYSCLK;	
 UART5_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
 UART5_CTL_R |= (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);
 GPIO_PORTE_AFSEL_R |= 0X30;
 GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & ~0xff) | (GPIO_PCTL_PE4_U5RX  | GPIO_PCTL_PE5_U5TX);
 GPIO_PORTE_DEN_R |=0x30;	
}

int UART5_ReadAvailable(void){
	return ((UART5_FR_R&UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}

char UART5_read(){
  while(UART5_ReadAvailable() !=1);
	return  UART5_DR_R & 0xFF;
}

void UART5_write(char c){
 while ((UART5_FR_R&UART_FR_TXFF)!=0);
 UART5_DR_R = c;
	
}

void U5_getCommand(char *str, int maxLen){
  char c;
	int i;
	for ( i=0; i<maxLen; i++){
		c=UART5_read();
		if(c== '\n' || c=='\r' )break;
		else str[i] = c;
		UART5_write(c);
	}
}
uint8_t UART5_Available(void){
  return ((UART5_FR_R &UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}

void U5_printstr(char *str){
  while(*str){
    UART5_write(*str);
    str++;
  }
}
