#include "usart.h"


void Usart_init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;	
	NVIC_InitTypeDef NVIC_InitStructure;	
	//GPIOA和USART1时钟使能①	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3,ENABLE);//使能USART1时钟
	//USART_DeInit(USART1);  //复位串口2 ②
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //PA2复用为USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //PA3复用为USART2	
		//USART_DeInit(USART1);  //复位串口3 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //PB10复用为USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //PB11复用为USART3
	//USART2_TX /RX  PA.2 PA.3 ③
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度50MHz	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉	
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2，PA3	
		//USART3_TX /RX  PB.10 PB.11 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10与GPIOB11	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度50MHz	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉	
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PB10，PB11	
	//USART 初始化设置 ④
	USART_InitStructure.USART_BaudRate = 115200;//一般设置为9600;	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式	
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位	
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位	
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      //收发模式	
	USART_Init(USART2, &USART_InitStructure); //初始化串口
	//USART_Init(USART3, &USART_InitStructure); //初始化串口
	
	//USART_Cmd(USART2,ENABLE);
	//USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	

////	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
#if EN_USART2_RX   
//	 
//NVIC设置，使能中断 ⑤	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断	
	//Usart2 NVIC 配置	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级2	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;          //响应优先级2	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQ通道使能	
	NVIC_Init(&NVIC_InitStructure);     //根据指定的参数初始化VIC寄存器、	
#endif	
//#if EN_USART3_RX      //NVIC设置，使能中断 	
//	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断	
//	//Usart3 NVIC 配置	
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级2	
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;          //响应优先级2	
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQ通道使能	
//	NVIC_Init(&NVIC_InitStructure);     //根据指定的参数初始化VIC寄存器、
//#endif
       USART_Cmd(USART2, ENABLE);  //使能串口  ⑥
//     USART_Cmd(USART3, ENABLE);  //使能串口  ⑥
	
}

void Send_Char(u8 Data)
{
	USART_SendData(USART2,Data);
	// 等待发送完成一个字节
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) != SET);
}

void Send_Data(void)
{
	Send_Char(0x01);
	
	Send_Char(tmp_0&0x00FF);
	Send_Char(tmp_0>>8);
	
	Send_Char(tmp_1&0x00FF);
	Send_Char(tmp_1>>8);

	Send_Char(tmp_2&0x00FF);
	Send_Char(tmp_2>>8);
	Send_Char(0xC6);
}

//void USART2_IRQHandler(void)
//{
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//	{
//		USART_ClearFlag(USART2, USART_FLAG_RXNE);
//		Usart1buf[pointer++%USART2_BUF_SIZE] = USART_ReceiveData(USART1);
//		
//		// 在此写代码接收程序
//		if(1)
//		{
//		}	
//	}
//}
