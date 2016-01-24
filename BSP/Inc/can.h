#include "includes.h"

#define CAN_ID_DRIVER_RESET_ALL      0x00 //广播
#define CAN_ID_DRIVER_RESET_NUM01    0x10
#define CAN_ID_DRIVER_RESET_NUM02    0x20
#define CAN_ID_DRIVER_RESET_NUM03    0x30
#define CAN_ID_DRIVER_RESET_NUM04    0x40
#define CAN_ID_DRIVER_RESET_NUM05    0x50
#define CAN_ID_DRIVER_RESET_NUM06    0x60
#define CAN_ID_DRIVER_RESET_NUM07    0x70
#define CAN_ID_DRIVER_RESET_NUM08    0x80
#define CAN_ID_DRIVER_RESET_NUM09    0x90
#define CAN_ID_DRIVER_RESET_NUM10    0xA0
#define CAN_ID_DRIVER_RESET_NUM11    0xB0
#define CAN_ID_DRIVER_RESET_NUM12    0xC0
#define CAN_ID_DRIVER_RESET_NUM13    0xD0
#define CAN_ID_DRIVER_RESET_NUM14    0xE0
#define CAN_ID_DRIVER_RESET_NUM15    0xF0

#define CAN_ID_MODE_CHOICE_ALL       0x01 //广播
#define CAN_ID_MODE_CHOICE_NUM01     0x11
#define CAN_ID_MODE_CHOICE_NUM02     0x21
#define CAN_ID_MODE_CHOICE_NUM03     0x31
#define CAN_ID_MODE_CHOICE_NUM04     0x41
#define CAN_ID_MODE_CHOICE_NUM05     0x51
#define CAN_ID_MODE_CHOICE_NUM06     0x61
#define CAN_ID_MODE_CHOICE_NUM07     0x71
#define CAN_ID_MODE_CHOICE_NUM08     0x81
#define CAN_ID_MODE_CHOICE_NUM09     0x91
#define CAN_ID_MODE_CHOICE_NUM10     0xA1
#define CAN_ID_MODE_CHOICE_NUM11     0xB1
#define CAN_ID_MODE_CHOICE_NUM12     0xC1
#define CAN_ID_MODE_CHOICE_NUM13     0xD1
#define CAN_ID_MODE_CHOICE_NUM14     0xE1
#define CAN_ID_MODE_CHOICE_NUM15     0xF1

#define CAN_ID_PWM_MODE_ALL          0x02 //广播
#define CAN_ID_PWM_MODE_NUM01        0x12
#define CAN_ID_PWM_MODE_NUM02        0x22
#define CAN_ID_PWM_MODE_NUM03        0x32
#define CAN_ID_PWM_MODE_NUM04        0x42
#define CAN_ID_PWM_MODE_NUM05        0x52
#define CAN_ID_PWM_MODE_NUM06        0x62
#define CAN_ID_PWM_MODE_NUM07        0x72
#define CAN_ID_PWM_MODE_NUM08        0x82
#define CAN_ID_PWM_MODE_NUM09        0x92
#define CAN_ID_PWM_MODE_NUM10        0xA2
#define CAN_ID_PWM_MODE_NUM11        0xB2
#define CAN_ID_PWM_MODE_NUM12        0xC2
#define CAN_ID_PWM_MODE_NUM13        0xD2
#define CAN_ID_PWM_MODE_NUM14        0xE2
#define CAN_ID_PWM_MODE_NUM15        0xF2

#define CAN_ID_CURRENT_MODE_ALL      0x03
#define CAN_ID_CURRENT_MODE_NUM01    0x13
#define CAN_ID_CURRENT_MODE_NUM02    0x23
#define CAN_ID_CURRENT_MODE_NUM03    0x33
#define CAN_ID_CURRENT_MODE_NUM04    0x43
#define CAN_ID_CURRENT_MODE_NUM05    0x53
#define CAN_ID_CURRENT_MODE_NUM06    0x63
#define CAN_ID_CURRENT_MODE_NUM07    0x73
#define CAN_ID_CURRENT_MODE_NUM08    0x83
#define CAN_ID_CURRENT_MODE_NUM09    0x93
#define CAN_ID_CURRENT_MODE_NUM10    0xA3
#define CAN_ID_CURRENT_MODE_NUM11    0xB3
#define CAN_ID_CURRENT_MODE_NUM12    0xC3
#define CAN_ID_CURRENT_MODE_NUM13    0xD3
#define CAN_ID_CURRENT_MODE_NUM14    0xE3
#define CAN_ID_CURRENT_MODE_NUM15    0xF3

#define CAN_ID_SPEED_MODE_ALL        0x04 //广播
#define CAN_ID_SPEED_MODE_NUM01      0x14
#define CAN_ID_SPEED_MODE_NUM02      0x24
#define CAN_ID_SPEED_MODE_NUM03      0x34
#define CAN_ID_SPEED_MODE_NUM04      0x44
#define CAN_ID_SPEED_MODE_NUM05      0x54
#define CAN_ID_SPEED_MODE_NUM06      0x64
#define CAN_ID_SPEED_MODE_NUM07      0x74
#define CAN_ID_SPEED_MODE_NUM08      0x84
#define CAN_ID_SPEED_MODE_NUM09      0x94
#define CAN_ID_SPEED_MODE_NUM10      0xA4
#define CAN_ID_SPEED_MODE_NUM11      0xB4
#define CAN_ID_SPEED_MODE_NUM12      0xC4
#define CAN_ID_SPEED_MODE_NUM13      0xD4
#define CAN_ID_SPEED_MODE_NUM14      0xE4
#define CAN_ID_SPEED_MODE_NUM15      0xF4

#define CAN_ID_LOCATION_MODE_ALL     0x05 //广播
#define CAN_ID_LOCATION_MODE_NUM01   0x15
#define CAN_ID_LOCATION_MODE_NUM02   0x25
#define CAN_ID_LOCATION_MODE_NUM03   0x35
#define CAN_ID_LOCATION_MODE_NUM04   0x45
#define CAN_ID_LOCATION_MODE_NUM05   0x55
#define CAN_ID_LOCATION_MODE_NUM06   0x65
#define CAN_ID_LOCATION_MODE_NUM07   0x75
#define CAN_ID_LOCATION_MODE_NUM08   0x85
#define CAN_ID_LOCATION_MODE_NUM09   0x95
#define CAN_ID_LOCATION_MODE_NUM10   0xA5
#define CAN_ID_LOCATION_MODE_NUM11   0xB5
#define CAN_ID_LOCATION_MODE_NUM12   0xC5
#define CAN_ID_LOCATION_MODE_NUM13   0xD5
#define CAN_ID_LOCATION_MODE_NUM14   0xE5
#define CAN_ID_LOCATION_MODE_NUM15   0xF5

#define ENTER_PWM_MODE               0x11
#define ENTER_CURRENT_MODE           0x22
#define ENTER_SPEED_MODE             0x33
#define ENTER_LOCATION_MODE          0x44


//extern u8 buf[8];
//extern u8 buffer_red_front[48];
//extern u8 buffer_blue_front[48];
//extern u8 buffer_red_behind[48];
//extern u8 buffer_blue_behind[48];
extern unsigned char CAN_rx_success_flag_2;

extern void CAN_init(void);
//extern u8 CAN1_Send_Msg(u8* msg,u8 len);
//u16 data_sort_front(int i);
//u16 data_sort_behind(int i);
//extern void  buffer_sort(void);
extern void CAN2_DATA();
u8 CAN2_Send_Msg(void);
//void RoboModule_Driver_Reset(unsigned char CAN_ID);
//void RoboModule_Driver_Mode_Chioce(unsigned char CAN_ID,unsigned char ENTER_X_MODE);
//void RoboModule_Driver_PWM_Mode_Set(unsigned char CAN_ID,short PWM_Value);
//void RoboModule_Driver_Current_Mode_Set(unsigned char CAN_ID,short Current_Value);
//void RoboModule_Driver_Speed_Mode_Set(unsigned char CAN_ID,short PWM_Value,short Speed_Value);
//void RoboModule_Driver_Location_Mode_Set(unsigned char CAN_ID,short PWM_Value,short Speed_Value,int Location_Value);
//void RoboModule_Config(unsigned char CAN_ID,unsigned char time);


