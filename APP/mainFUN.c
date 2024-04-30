
#include <math.h>
#define PI=3.14159265359;
#define EARTH_RADIUS=6371000 //in meter
#define PRESSED=0 //negative logic

float destLongitude=0;
float destLatitude= 0;
char i=0;
public float distance=0; // will be stored
char swich2=0; //use to check and increase
float lon_lat[];


void mainProgram(){
  	float currentLongitude=getCurrentLongitude();
	float currentLatitude=getCurrentLatitude();

	StoreINarray(currentLongitude,currentLatitude);

if(destLongitude!=0 && destLatitude!=0)
{
	for (int i=0;i<swich2check();i++)
{
	 LED_LedInit( LED_BLUE );
	 SysTick_Wait_Sec(10); //10s delay
	 LED_LedOff( LED_BLUE );
	 SysTick_Wait_Sec(10); //10s delay


}
    distance+=distance(currentLongitude, currentLatitude ,destLongitude  ,destLatitude); //data from gps
    LCD_floating(distance); //display distance num on LCD 
  }


    destLongitude =currentLongitude;
    destLatitude =currentLatitude;


}



float ToDeg(float Num)
{
int degree =(int) Num/100;
float minutes =Num-(float)degree*100;
return(degree+(minutes/60));
}



float ToRad(float DegNum)
{
    return DegNum*PI/180;
}


float Distance(float currentA , float currentB , float destA ,float destB){
    float currentA_RAD = ToRad(ToDeg(currentA));
    float currentB_RAD = ToRad(ToDeg(currentB));
    float destA_RAD = ToRad(ToDeg(destA));
    float destB_RAD = ToRad(ToDeg(destB));

    //Difference

    float aDiff=destA_RAD-currentA_RAD;
    float bDiff=destB_RAD-currentB_RAD;

    //Distance b lat

    float a=pow(sin(bDiff/2),2)+cos(currentB_RAD)*cos(destB_RAD)*pow(sin(aDiff/2),2);
    double Dis=2*atan2(sqrt(a),sqrt(1-a));


return EARTH_RADIUS*Dis;
}





char swich2check(){
    if(swich2>=4)
        swich2=0;

if ( SW_ispressed(SW2))
    swich2++;
    return swich2;
}


bool isDestination(void)
{
    return (finalCurrentA==currentLongitude &&finalCurrentB==currentLatitude ) true ,false;
}




void   StoreINarray(float Long ,float Lat);
{
        lon_lat[i++]=Long;
        lon_lat[i++]= Lat;
        lon_lat[i++]=0;

}


bool SWex_ispressed(void){
	return if(SW_Read()=="1") false:true;

}



