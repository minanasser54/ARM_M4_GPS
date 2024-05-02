#ifndef __GPS__
#define __GPS__


#define PI 3.141592654
#define EARTH_RADIUS 6371000

void GPS_read(void);
void GPS_format(void);
float getCurrentLongitude(void);
float getCurrentLatitude(void);
float getCurrentSpeed(void);


#endif
