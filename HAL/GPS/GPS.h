#ifndef __GPS__
#define __GPS__

#define PI 3.141592654
#define EARTH_RADIUS 6371000

char*  GPS_read(void);
void GPS_format(void);
char* getCurrentLongitude(void);
char* getCurrentLatitude(void);
char* getCurrentSpeed(void);


#endif
