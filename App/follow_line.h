#include "includes.h"

extern u8 buf[8];
extern u8 buffer_red_front[48];
extern u8 buffer_blue_front[48];
extern u8 buffer_red_behind[48];
extern u8 buffer_blue_behind[48];

#define L 5
#define middle_number 24
#define L_distance 800

void otsuThreshold(u8* data_in,u8* dataout1,u8* dataout2);
extern void dis_angle(float* distance,float* angle );