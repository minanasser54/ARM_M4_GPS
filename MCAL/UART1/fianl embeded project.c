#include "tm4c123gh6pm.h"
//#include "STD_TYPES.h"
#include "stdint.h"
#include "string.h"
//#include "Bit_Utilities.h"
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
 GPIO_PORTE_AFSEL_R |= 0X030;
 GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & ~0xff) | (GPIO_PCTL_PE4_U5RX  | GPIO_PCTL_PE5_U5TX);
 GPIO_PORTE_DEN_R |=0x030;	
}
//GPIO_PCTL_PB0_U1RX      0x00000001
//GPIO_PCTL_PB1_U1TX      0x00000010

int UART5_ReadAvailable(void){
	return ((UART5_FR_R&UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}

char UART5_read(){
  while(UART5_ReadAvailable() !=1);
	return UART5_DR_R & 0xFF;
}

void UART5_write(char c){
 while ((UART5_FR_R&UART_FR_TXFF)!=0);
 UART5_DR_R = c;
	
}

void getCommand(char *str, int maxLen){
  char c;
	int i;
	for ( i=0; i<maxLen; i++){
		c=UART5_read();
		if(c== '\n' || c=='\r' )break;
		else str[i] = c;
		UART5_write(c);
	}
}
void RGBLED_Init(void){
SYSCTL_RCGCGPIO_R |= 0x20;             
while((SYSCTL_PRGPIO_R & 0x20)==0){};  
GPIO_PORTF_DIR_R |= 0x0E;              
GPIO_PORTF_AFSEL_R &= ~(0x0E);        
GPIO_PORTF_PCTL_R &= ~(0x0000FFF0);    
GPIO_PORTF_DEN_R |= 0x0E;             
GPIO_PORTF_AMSEL_R &= ~(0x0E);        
GPIO_PORTF_DATA_R &= ~(0x0E);         
}

void RGB_set(uint8_t mask){
  mask &= 0x0E;
  GPIO_PORTF_DATA_R |= mask;
}
void RGB_clear(uint8_t mask){
  mask &= 0x0E;
  GPIO_PORTF_DATA_R &= ~mask;
}


uint8_t UART5_Available(){
  return ((UART5_FR_R &UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}




void printstr(char *str){
  while(*str){
    UART5_write(*str);
    str++;
  }
}




int main(){
  const uint8_t bufferLen = 9;
  char command[bufferLen]={0};
  UART5Init();
  RGBLED_Init();
  while(1){
    printstr("Enter Command:\n");
    getCommand(command,bufferLen);
    if(strcmp(command, "RedOn")==0){
      RGB_set(0x02);
    }
    else if(strcmp(command, "RedOff")==0){
      RGB_clear(0x02);
    }
    else if(strcmp(command, "BlueOn")==0){
      RGB_set(0x04);
    }
    else if(strcmp(command, "BlueOff")==0){
      RGB_clear(0x04);
    }
    else if(strcmp(command, "GreenOn")==0){
      RGB_set(0x08);
    }
    else if(strcmp(command, "GreenOff")==0){
      RGB_clear(0x08);
    }
    else{
      RGB_clear(0x0E);
    }
    memset(command,0,bufferLen);
    UART5_write('\n');  
  }
}