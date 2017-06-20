#include <stdio.h>
#include <math.h>

#define PI 3.141592653
#define dutorad(X) ((X)/180*PI)
#define radtodu(X) ((X)/PI*180)

double getGestGps(void);
double getHostGps(void);

double compaireDistance(void);
double calculateAngle(void);

void autoFollow(void);
void move(void);

