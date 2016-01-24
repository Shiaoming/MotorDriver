/**
  ******************************************************************************
  * @文件	main.c
  * @日期	2015-1-26
  * @说明	手柄程序
  ******************************************************************************
  * 北京交通大学-通信1208-赵小铭
  *
  * 说明:	IAR版本:7.20.2.7314
  *      	库文件版本:标准库 V1.3.0
  * 文件缩进:	Tab Size:4
  * 自动缩进:	Body:4
  * 详细说明见Documents中Readme.txt
  ******************************************************************************
  * 功能描述：
  *           
  ******************************************************************************
  */
#include "includes.h"

int time = 2;
float32_t da1;
float32_t da2;
int m=0;
u16 adcx;  
float t1,t2,t3;
float infrared_data;
u8 senddata;
float a,b,distance,angle;

u32 PIDloopcount;

void delay_ms(unsigned int t)
{
	int volatile tmp1;
	int i;
	for(i = 0;i < 8400;i++)
	{
		tmp1 = t;
		while(tmp1--);
	}
}

void main(void)
{
	// 中断分组的配置
	NVIC_Config();
	ENC_Init();
	Motor_Init();
	CAN_init();
	BEEP_Config();
    LED_Config();
    Timer_Configuration(); 
	
	while(1)
	{
	  if (CAN_rx_success_flag_2 == 1)
	  {
		CAN2_DATA();
		CAN_rx_success_flag_2 =0;
	  }

	  if(PIDloopcount % 1000 < 500)
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
	  else
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	}
}

