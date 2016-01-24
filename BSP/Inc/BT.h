/**
  ******************************************************************************
  * @文件	BT.h
  * @日期	2015-1-26
  * @说明	蓝牙驱动
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
  *             PC12 -> TX , PD2 -> RX , PC11 -> BT_Status
  * 使用的外设：
  *             UART5
  ******************************************************************************
  */
#pragma once
#include "includes.h"

// 蓝牙时钟
#define		BT_UART			UART5
#define		BT_UART_NVIC	UART5_IRQn
#define		BT_Periph_RCC	RCC_APB1Periph_UART5
#define		BT_TX_GPIO_RCC	RCC_AHB1Periph_GPIOC
#define		BT_RX_GPIO_RCC	RCC_AHB1Periph_GPIOD
// 蓝牙所接的GPIO口
#define		BT_TX_GPIO		GPIOC
#define		BT_RX_GPIO		GPIOD
#define		BT_TX_PIN		GPIO_Pin_12
#define		BT_RX_PIN		GPIO_Pin_2
#define		BT_Status_PIN	GPIO_Pin_11
#define		BT_TX_PINSor	GPIO_PinSource12
#define		BT_RX_PINSor	GPIO_PinSource2


/** 
  * @说明 蓝牙状态定义
  */   
typedef enum
{ 
	BT_Mode_Noconnect		= 0x00, /*!<蓝牙未连接 */
	BT_Mode_Connected		= 0x01, /*!<蓝牙成功连接*/
}BTStatusTypeDef;

/** 
  * @说明 蓝牙发送结构体定义
  */   
typedef struct
{
	u8* BT_Tx_Buf;
	u8 BT_Tx_Pointer;
}BTTxTypeDef;

/** 
  * @说明 蓝牙接收结构体定义
  */   
typedef struct
{
	u8 BT_Rx_Buf[512];
	u8 BT_Rx_Pointer;
}BTRxTypeDef;

/** 
  * @说明 蓝牙结构体定义
  */   
typedef struct
{
	BTStatusTypeDef BTStatus;
	BTTxTypeDef 	BTTx;
	BTRxTypeDef 	BTRx;
}BTTypeDef;

extern BTTypeDef BT;

void BT_Init(void);
void RD_BT_Status(void);
void BT_Send_String(uint8_t *pData,char len);
