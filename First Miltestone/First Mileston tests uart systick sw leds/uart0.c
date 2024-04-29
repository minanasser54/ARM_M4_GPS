#include <stdio.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"

#define PF4                     (*((volatile unsigned long *)0x40025040))
#define PF3                     (*((volatile unsigned long *)0x40025020))
#define PF2                     (*((volatile unsigned long *)0x40025010))
#define PF1                     (*((volatile unsigned long *)0x40025008))
#define PF0                     (*((volatile unsigned long *)0x40025004))

#define PF123_mask             0x0E
#define PF04_mask              0x11
#define PF_mask                0x20
#define PF_SW1_mask 					 0x10
#define PF_SW2_mask 					 0x01

void SW1_Int (void){
SYSCTL_RCGCGPIO_R |= PF_mask;
while ((SYSCTL_PRGPIO_R & PF_mask) == 0){};
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY ;
GPIO_PORTF_CR_R |= PF_SW1_mask;
GPIO_PORTF_AMSEL_R &= ~PF_SW1_mask;
GPIO_PORTF_PCTL_R &= ~0x000F0000;
GPIO_PORTF_AFSEL_R &= ~PF_SW1_mask;
GPIO_PORTF_DIR_R &= ~PF_SW1_mask;
GPIO_PORTF_PUR_R |= PF_SW1_mask;
GPIO_PORTF_DEN_R |= PF_SW1_mask;
}
void SW2_Int (void){
SYSCTL_RCGCGPIO_R |= PF_mask;
while ((SYSCTL_PRGPIO_R & PF_mask) == 0){};
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY ;
GPIO_PORTF_CR_R |= PF_SW2_mask;
GPIO_PORTF_AMSEL_R &= ~PF_SW2_mask;
GPIO_PORTF_PCTL_R &= ~0x0000000F;
GPIO_PORTF_AFSEL_R &= ~PF_SW2_mask;
GPIO_PORTF_DIR_R &= ~PF_SW2_mask;
GPIO_PORTF_PUR_R |= PF_SW2_mask;
GPIO_PORTF_DEN_R |= PF_SW2_mask;
}
unsigned char SW1_Input (void){
return GPIO_PORTF_DATA_R &PF_SW1_mask;
}
unsigned char SW2_Input (void){
return GPIO_PORTF_DATA_R &PF_SW2_mask;
}

void UART0Init(){
 SYSCTL_RCGCUART_R |=SYSCTL_RCGCUART_R0;
 SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R0;
 UART0_CTL_R &= ~UART_CTL_UARTEN;
 UART0_IBRD_R = 104;
 UART0_FBRD_R = 11;
 UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
 UART0_CTL_R |= (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);
 GPIO_PORTA_AFSEL_R |= 0X03;
 GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xff) | (GPIO_PCTL_PA0_U0RX  | GPIO_PCTL_PA1_U0TX);
 GPIO_PORTA_DEN_R |=0x03;	
}

int UART0_ReadAvailable(void){
	return ((UART0_FR_R&UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}

char UART0_read(){
  while(UART0_ReadAvailable() !=1);
	return UART0_DR_R & 0xFF;
}

void UART0_write(char c){
 while ((UART0_FR_R&UART_FR_TXFF)!=0);
 UART0_DR_R = c;
	
}

void getCommand(char *str, int maxLen){
  char c;
	int i;
	for ( i=0; i<maxLen; i++){
		c=UART0_read();
		if(c== '\n' || c=='\r' )break;
		else str[i] = c;
		UART0_write(c);
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



void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock
}
// The delay parameter is in units of the 80 MHz core clock. (12.5 ns)
void SysTick_Wait(unsigned long delay){
  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
}
void SysTick_Wait_Sec(unsigned long delay){
	unsigned long i;
	for(i=0;i<delay;i++){
		SysTick_Wait(80000000);
	}
}

uint8_t UART0_Available(){
  return ((UART0_FR_R &UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}




void printstr(char *str){
  while(*str){
    UART0_write(*str);
    str++;
  }
}
void check_mode(int *ptr){
		if((!SW1_Input()) && SW2_Input()) {
			  *ptr=1;}
		if(SW1_Input() && (!SW2_Input())) {
			  *ptr=2;}}



int main(){
  const uint8_t bufferLen = 8;
  char command[bufferLen]={0};
	int mode =0;
	int *p = & mode;
  UART0Init();
  RGBLED_Init();
	SysTick_Init();
	SysTick_Wait_Sec(10);
	SW1_Int();
	SW2_Int();
	printstr("HELLO this code tests uart switches systick and leds \n");
	printstr("mode zero stand by  use switches to enter mode 1 or 2");
	
  while(1){
		check_mode(p);
		if (mode==1){
		int dst;
		printstr("entered mode 1 increasing dst \n ");
		printstr("from 0  to  100 or reset \n ");
    printstr("Enter Current Distance:\n");
		
		getCommand(command,bufferLen);
		dst = atoi(command);
    if(dst >= 40){
			  RGB_clear(0x0E);
        RGB_set(0x02);
			if(dst >=90){
			  RGB_clear(0x0E);
				RGB_set(0x04);
			}
			if(dst ==100){
				RGB_clear(0x0E);
				RGB_set(0x08);
			}
    }else{
      RGB_clear(0x0E);
    }
    if(strcmp(command,"reset")==0){
      mode = 0;
    }
		memset(command,0,bufferLen);
    UART0_write('\n');
		}
	if (mode==2){
		int dst;
		printstr("entered mode 2  decreasing dst  \n ");
		printstr("from 0  to  100  or reset\n ");
    printstr("Enter Current Distance:\n");
		
    getCommand(command,bufferLen);
		dst = atoi(command);
    if(dst <= 60){
			RGB_clear(0x0E);
      RGB_set(0x02);
		if(dst <=10){
			RGB_clear(0x0E);
				RGB_set(0x04);
			}
		if(dst ==0){
				RGB_clear(0x0E);
				RGB_set(0x08);
			}
    }else{
      RGB_clear(0x0E);
    }
    if(strcmp(command,"reset")==0){
      mode = 0;
    }
    
		memset(command,0,bufferLen);
    UART0_write('\n');
		}
	}
}

