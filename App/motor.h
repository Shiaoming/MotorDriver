
#ifndef __MOTOR_H
#define __MOTOR_H

#include "includes.h"

void Motor_Init(void);
#define abs(x) ((x)>0? (x):(-(x)))
#define MOTOR_TIMER1     TIM1 
#define MOTOR_TIMER2     TIM8
//#define MOTOR_DIR_PORT      GPIOC
//PWM宏定义
#define M0_PWM_1         MOTOR_TIMER1->CCR1
#define M1_PWM_1         MOTOR_TIMER1->CCR2
#define M2_PWM_1         MOTOR_TIMER1->CCR3
#define M3_PWM_1         MOTOR_TIMER1->CCR4

#define M0_PWM_2         MOTOR_TIMER2->CCR1
#define M1_PWM_2         MOTOR_TIMER2->CCR2
#define M2_PWM_2         MOTOR_TIMER2->CCR3
#define M3_PWM_2         MOTOR_TIMER2->CCR4


//停止宏定义
#define MOTOR_0_STOP()      GPIO_ResetBits(GPIOC,GPIO_Pin_11); 
#define MOTOR_1_STOP()      GPIO_ResetBits(GPIOC,GPIO_Pin_12);
#define MOTOR_2_STOP()      GPIO_ResetBits(GPIOE,GPIO_Pin_12);
#define MOTOR_3_STOP()      GPIO_ResetBits(GPIOC,GPIO_Pin_14);

void Move_Motor_0(int v);
void Move_Motor_1(int v);
void Move_Motor_2(int v);
void Move_Motor_3(int v);


/*pwm最大最小值定义
#define MOTOR_WALK_MIN_PWM        600
#define MOTOR_WALK_MAX_PWM        2800//1300
#define MOTOR_LIFT_UP_MIN_PWM     1000
#define MOTOR_LIFT_UP_MAX_PWM     3100//2000
#define MOTOR_LIFT_DOWN_MIN_PWM   500
#define MOTOR_LIFT_DOWN_MAX_PWM   600
*/


#endif/*__MOTOR_H*/  
