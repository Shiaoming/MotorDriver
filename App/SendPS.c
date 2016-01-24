/**
  ******************************************************************************
  * @文件	SendPS.c
  * @日期	2015-1-26
  ******************************************************************************
  * 北京交通大学-通信1208-赵小铭
  *
  * 说明:	IAR版本:7.20.2.7314
  *      	库文件版本:标准库 V1.3.0
  * 文件缩进:	Tab Size:4
  * 自动缩进:	Body:4
  ******************************************************************************
  * 功能描述：
  *           读取手柄数据，通过蓝牙发送给底盘
  ******************************************************************************
  */
#include "includes.h"

u8 head_end[]={0x55};
u8 A2D[]={0x41};
u8 FF_Flag = 1;
u8 count = 0;//发送停止信号的计数值

void Get_Data_Send(void)
{
	// 获取手柄数据
	Get_PS_Data();
	
	// 判断手柄处于哪种模式
	switch(CONL.PS->PS_Data[0])
	{
		// 数字模式
		case Digital_Mode:
			PS_Digital_Mode();
			// 判断数据是否有效(有按键按下)，当FF_Flag=1时也会进，
			// 目的是为了在按键松开后多发送几次停止数据，防止底盘漏接收帧
			if(FF_Flag||(CONL.PS->PS_Data[2] != 0xff)||(CONL.PS->PS_Data[3] != 0xff))
			{
				// 发送有效数据
				BT_Send_String(CONL.PS->PS_Data,1);// 包头
				BT_Send_String(CONL.PS->PS_Data+2,2);// 有效数据
				// 发送包尾
				BT_Send_String(head_end,1);
				
				// count用于发送停止数据计数，FF_Flag为标志位
				if((count < 10)&&(CONL.PS->PS_Data[2] == 0xff)\
					&&(CONL.PS->PS_Data[3] == 0xff))//没有有效数据，清标志位
				{
					count++;
					if(count >= 10)
						FF_Flag = 0;
				}
				else
				{
					FF_Flag = 1;
					count = 0;
				}
			}
			break;
		// 模拟模式，与数字模式类似，不在赘述
		case Analog_Red:
			PS_Analog_Red();
			
			if(((CONL.PS->PS_Data[3] & R1) != 0))
			{
				if(FF_Flag||(CONL.PS->PS_Data[2] != 0xff)||\
				   (CONL.PS->PS_Data[3] != 0xff))// 有有效数据
				{
					BT_Send_String(A2D,1);
					BT_Send_String(CONL.PS->PS_Data+2,2);
					BT_Send_String(head_end,1);
					if((count < 10)&&(CONL.PS->PS_Data[2] == 0xff)\
						&&(CONL.PS->PS_Data[3] == 0xff))
					{
						count++;
						if(count >= 10)
							FF_Flag = 0;
					}
					else
					{
						FF_Flag = 1;
						count = 0;
					}
				}
			}
			else
			{
				BT_Send_String(CONL.PS->PS_Data,1);
				BT_Send_String(CONL.PS->PS_Data+2,6);
				BT_Send_String(head_end,1);
			}
			break;
		default:
		break;
	}
}
