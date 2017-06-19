#include <stdio.h>
#include <math.c>

#define PI 3.141592653
#define dutorad(X) ((X)/180*PI)
#define radtodu(X) ((X)/PI*180)

double getGestGps();
double getHostGps();
double compaireDistance();
void move();
double calculateAngle();
int main(){
getHostGps();
getGestGps();

while(1){
	if((double distance = compaireDistance()) >= 2.5){
		move();
	}
	
}

typedef struct  getHostGps{
	h_lon = ;
	h_lat = ;

}*hostGps;
typedef struct  getGestGps{
	g_lon = ;
	g_lat = ;	
}*gestGps;

double getHostGps(){

}
double getGestGps(){

}
double compaireDistance(){

	g_lon = dutorad(gestGps.g_lon);
	g_lat = dutorad(gestGps.g_lat);
	h_lon = dutorad(hostGps.h_lon);
	h_lat = dutorad(hostGps.h_lat);

	double D_lat = g_lat - h_lat;
	double D_lon = g_lon - h_lon;

	double a = sin(D_lat/2) * sin(D_lat/2) +cos(h_lat) * cos(g_lat) * sin(D_lon/2) * sin(D_lon/2);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));

	double R = 6371e3;
	double distance = R * c;				//计算距离
	return distance; 

}
void move(){
	double moveAngle = calculateAngle();
	if(moveAngle < 180){
		int A_pulse = moveAngle/1;
		driver_dir(A_pulse,500,cw);  // 按500HZ频率顺时针发送脉冲
	}
	else{ 
		int A_pulse = (360 - moveAngle)/1;
		driver_dir(A_pulse,500,ccw); //逆时针发送脉冲
	}	     //角度脉冲数
	
	double moveDistance = compaireDistance();
	int D_pulse =					 //距离脉冲数	


}
double calculateAngle(){
	g_lon = dutorad(gestGps.g_lon);
	g_lat = dutorad(gestGps.g_lat);
	h_lon = dutorad(hostGps.h_lon);
	h_lat = dutorad(hostGps.h_lat);

	double D_lat = g_lat - h_lat;
	double D_lon = g_lon - h_lon;

	double y = sin(g_lon - h_lon) * cos(g_lat);
	double x = cos(h_lat)*sin(g_lat) - sin(h_lat) * cos(g_lat) * cos(g_lon - h_lon);

	double angle = radtodu(atan2(y,x))				//计算角度
	return angle;
}

