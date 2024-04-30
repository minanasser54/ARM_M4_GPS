#ifndef MAINfun_H
#define MAINfun_H

#include "tm4c123gh6pm.h"


void mainProgram(void);

float ToDeg(float Num);

float ToRad(float DegNum);

float Distance(float currentA , float currentB , float destA ,float destB);

char swich2check(void);

bool isDestination(void);

void   StoreINarray(float Long ,float Lat);

bool SWex_ispressed(void);

#endif