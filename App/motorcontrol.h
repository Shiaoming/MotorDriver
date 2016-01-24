#ifndef __MOTORCONTROL_H__
#define __MOTORCONTROL_H__
#include "includes.h"

extern s32 EXP_Angle;
typedef struct ST_PID
{
	float KP;
	float KI;
	float KD;
	float PreError;
	float LastError;
}ST_PID;
extern ST_PID Speed_PID_0;
extern ST_PID Speed_PID_1;
extern ST_PID Speed_PID_2;
extern ST_PID Speed_PID_3;
extern s32 Speed_exp_0;
extern s32 Speed_exp_1;
extern s32 Speed_exp_2;
extern s32 Speed_exp_3;
extern s32 Cal_PID_w;
#define Motor_out_max  5000
#define Motor_out_min -5000

void Motor_Control_0(s16 i);
void Motor_Control_1(s16 i);
void Motor_Control_2(s16 i);
void Motor_Control_3(s16 i);

float Cal_w(void);
float PIDjisuan(ST_PID *Speed_PID, float ThisError );

#endif
