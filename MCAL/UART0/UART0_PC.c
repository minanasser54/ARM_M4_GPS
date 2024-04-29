#include "../../UTILITIES/tm4c123gh6pm.h"
#include "string.h"
#include "UART0_PC.H"

void UART0_INIT(){
 SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
 SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

UART0_CTL_R &= ~ UART_CTL_UARTEN;
UART0_IBRD_R = 104;  
UART0_FBRD_R = 11;
UART0_LCRH_R |= (UART_LCRH_WLEN_8 | UART_LCRH_FEN)  ;
UART0_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
  
GPIO_PORTA_AFSEL_R |= GPIO_PA10_M ;
GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R &= ~0xFF)|(GPIO_PCTL_PA1_U0TX|GPIO_PCTL_PA0_U0RX);
GPIO_PORTA_DEN_R |= GPIO_PA10_M ;
GPIO_PORTA_AMSEL_R &= ~GPIO_PA10_M ;  
}

uint8_t UART0_Available(void){
  return ((UART0_FR_R &UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}
char UART0_read(void){
   while(UART0_Available() !=1){};
    return (char) (UART0_DR_R & 0xFF);
    }

void UART0_write(char data){
  while((UART0_FR_R & UART_FR_TXFF)==UART_FR_TXFF){};
    UART0_DR_R = data;
}

void getCommand(char *str,uint8_t maxLen){
  char c;
  int8_t i;
  for(i =0;i<maxLen;i++){
    c = UART0_read();
    if(c=='\n' || c=='\r'){ break;
    }
    else str[i]=c;
    UART0_write(c);
    
  }
  
}
void printstr(char *str){
  while(*str){
    UART0_write(*str);
    str++;
  }
}

