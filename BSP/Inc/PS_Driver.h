/**
  ******************************************************************************
  * @文件	PS_Dirver.c
  * @日期	2015-1-26
  * @说明	手柄驱动
  ******************************************************************************
  * 北京交通大学-通信1208-赵小铭
  *
  * 说明:	IAR版本:7.20.2.7314
  *      	库文件版本:标准库 V1.3.0
  * 文件缩进:	Tab Size:4
  * 自动缩进:	Body:4
  * 详细说明见Documents中Readme.txt
  ******************************************************************************
  * 使用的接口：
  *             DATA -> GPIOB3
  *             CMD -> GPIOB4
  *             ATT -> GPIOB5
  *             CLK -> GPIOB6
  *             ACK -> GPIOB7
  * 注：此PS手柄读取速度较慢，只能使用模拟SPI时序
  ******************************************************************************
  */
#pragma once
#include "includes.h"

// PS所接的GPIO口
#define		PS_GPIO_RCC		RCC_AHB1Periph_GPIOB
#define		PS_GPIO			GPIOB

// DATA
#define		PS_DATA_PIN		GPIO_Pin_3
#define		PS_DATA_RD()	GPIO_ReadInputDataBit(PS_GPIO,PS_DATA_PIN)

// CMD
#define		PS_CMD_PIN		GPIO_Pin_4
#define		PS_CMD_HIGH()	GPIO_SetBits(PS_GPIO,PS_CMD_PIN)
#define		PS_CMD_LOW()	GPIO_ResetBits(PS_GPIO,PS_CMD_PIN)

// ATT
#define		PS_ATT_PIN		GPIO_Pin_5
#define		PS_ATT_HIGH()	GPIO_SetBits(PS_GPIO,PS_ATT_PIN)
#define		PS_ATT_LOW()	GPIO_ResetBits(PS_GPIO,PS_ATT_PIN)

// CLK
#define		PS_CLK_PIN		GPIO_Pin_6
#define		PS_CLK_HIGH()	GPIO_SetBits(PS_GPIO,PS_CLK_PIN)
#define		PS_CLK_LOW()	GPIO_ResetBits(PS_GPIO,PS_CLK_PIN)

// ACK
#define		PS_ACK_PIN		GPIO_Pin_7
#define		PS_ACK_RD()		GPIO_ReadInputDataBit(PS_GPIO,PS_ACK_PIN)

// PS_Mode
#define		Digital_Mode	0x41
#define		Analog_Red		0x73

// Common Mode
#define		SLCT			0x01
#define		STRT			0x08
#define		UP				0x10
#define		RGHT			0x20
#define		DOWN			0x40
#define		LEFT			0x80
#define		L2				0x01
#define		R2				0x02
#define		L1				0x04
#define		R1				0x08
#define		Triangle	  	0x10
#define		Circular	  	0x20
#define		Cross		  	0x40
#define		Square		  	0x80

// Digital_Mode

// NegCon
#define		A				0x10
#define		B				0x20

// Analog_Red
#define		JOYR			0x02
#define		JOYL			0x04

/** 
  * @说明 手柄状态定义
  */   
typedef struct
{ 
	u8 PS_Data[9];		/*!<手柄数据*/
}PSTypeDef;

extern PSTypeDef PS;

// 函数接口的外部声明
extern void PS_Init(void);
extern void Get_PS_Data(void);

void PS_Digital_Mode(void);
void PS_Analog_Red(void);