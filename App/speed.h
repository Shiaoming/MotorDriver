
#include "includes.h"


#ifndef SPEED_H
#define SPEED_H

#define LL1  535.0  //ÐÂµ×ÅÌ³ß´ç  
#define LL2  464.0
#define R   50.0
//#define PI  3.14159


extern void WSpeed(float vx,float vy,float wz);
 void SetSpeed_0();
 void SetSpeed();
extern float vx,vy,wz;

typedef struct
{
	s16 speed0,speed1,speed2,speed3;
}RobotWspeed;

extern RobotWspeed robotw; 

#endif