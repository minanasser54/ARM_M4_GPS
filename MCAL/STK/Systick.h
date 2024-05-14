#ifndef __Systick__
#define __Systick__



void SysTick_Init(void);
void systick_wait_1s(void);
void systick_wait_1ms(void);
void delay_IN_ms(int total);
void delay_IN_s(int total);
void systick_wait_1MICROs(void);
void delay_IN_MICROs(int total);
void SysTick_Wait(unsigned long delay);


#endif 
