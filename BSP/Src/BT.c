/**
  ******************************************************************************
  * @文件	BT.c
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

#include "includes.h"

// 蓝牙结构体定义
BTTypeDef BT;

/*******************************************************************************
函 数 名：BT_Struct_Init(void)
描    述：初始化蓝牙模块结构体
*******************************************************************************/
void BT_Struct_Init(void)
{	
	BT.BTStatus = BT_Mode_Noconnect;
	BT.BTTx.BT_Tx_Pointer = 0;
	BT.BTRx.BT_Rx_Pointer = 0;
}

/*******************************************************************************
函 数 名：BT_Init(void)
描    述：初始化蓝牙模块(GPIO、UART5、结构体)
*******************************************************************************/
void BT_Init(void)
{	
	USART_InitTypeDef UART5_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// C、D口时钟
	RCC_AHB1PeriphClockCmd(BT_TX_GPIO_RCC, ENABLE);
	RCC_AHB1PeriphClockCmd(BT_RX_GPIO_RCC, ENABLE);
	// PC12 -> TX
	GPIO_InitStructure.GPIO_Pin = BT_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(BT_TX_GPIO,&GPIO_InitStructure);
	// PD2 -> RX
	GPIO_InitStructure.GPIO_Pin = BT_RX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(BT_RX_GPIO,&GPIO_InitStructure);
	// PC11 -> BT_Status
	GPIO_InitStructure.GPIO_Pin = BT_Status_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//因为连接成功是高电平
	GPIO_Init(BT_TX_GPIO,&GPIO_InitStructure);
	// 复用功能配置
	GPIO_PinAFConfig(BT_TX_GPIO,BT_TX_PINSor,GPIO_AF_UART5);
	GPIO_PinAFConfig(BT_RX_GPIO,BT_RX_PINSor,GPIO_AF_UART5);
	// UART5时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	// UART5中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	// UART5初始化
	USART_DeInit(UART5);
	UART5_InitStructure.USART_BaudRate = 115200;
	UART5_InitStructure.USART_WordLength = USART_WordLength_8b;
	UART5_InitStructure.USART_StopBits = USART_StopBits_1;
	UART5_InitStructure.USART_Parity = USART_Parity_No;
	UART5_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	UART5_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(UART5,&UART5_InitStructure);
	USART_Cmd(UART5,ENABLE);
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
	// 结构体初始化
	BT_Struct_Init();
	// 蓝牙状态
	RD_BT_Status();
}

/*******************************************************************************
函 数 名：RD_BT_Status(void)
描    述：读取蓝牙状态，更新到全局结构体
*******************************************************************************/
void RD_BT_Status(void)
{
	if(GPIO_ReadInputDataBit(BT_TX_GPIO,BT_Status_PIN) == SET)
		BT.BTStatus = BT_Mode_Connected;
	else
		BT.BTStatus = BT_Mode_Noconnect;
}
/*******************************************************************************
函 数 名：BT_Send_Char(u8 Char)
描    述：通过蓝牙发送一个字符
输入参数：
          pData：字符串首地址
          len：字符串长度
*******************************************************************************/
void BT_Send_Char(u8 Char)
{
	USART_SendData(BT_UART,Char);
	// 等待发送完成一个字节
	while(USART_GetFlagStatus(BT_UART,USART_FLAG_TXE) != SET);
}
/*******************************************************************************
函 数 名：BT_Send_String(uint8_t *pData,char len)
描    述：通过蓝牙发送一个长度为len的字符串(暂时未使用结构体数据)
输入参数：
          pData：字符串首地址
          len：字符串长度
*******************************************************************************/
void BT_Send_String(uint8_t *pData,char len)
{
	while(len--)
	{
		BT_Send_Char(*pData);
		// 指针加一
		pData++;
	}
}
/*******************************************************************************
函 数 名：UART5_IRQHandler(void)
描    述：蓝牙串口接收中断
*******************************************************************************/
void UART5_IRQHandler(void)
{ 
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{
		BT.BTRx.BT_Rx_Buf[BT.BTRx.BT_Rx_Pointer] = USART_ReceiveData(UART5);
	}
}