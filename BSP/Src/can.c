#include "can.h"


/*----CAN2_TX-----PB13----*/
/*----CAN2_RX-----PB12----*/


CanRxMsg rx2_message;
CanTxMsg Tx2_Message;

/*************************************************************************
                          CAN1_Configuration
描述：初始化CAN1配置为1M波特率
*************************************************************************/
void CAN_init(void)
{
    CAN_InitTypeDef        CAN;
    CAN_FilterInitTypeDef  CAN_filter;
    GPIO_InitTypeDef       GPIO;
    NVIC_InitTypeDef       nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1|RCC_APB1Periph_CAN2, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
	
    GPIO.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO.GPIO_Mode = GPIO_Mode_AF;
	GPIO.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO.GPIO_OType = GPIO_OType_PP;
	GPIO.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO);
    
	// 接收中断优先级
    nvic.NVIC_IRQChannel = CAN2_RX0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 2;
    nvic.NVIC_IRQChannelSubPriority = 2;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
    
	// 发送中断优先级
    nvic.NVIC_IRQChannel = CAN2_TX_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 2;
    nvic.NVIC_IRQChannelSubPriority = 3;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);    
    
    CAN_DeInit(CAN2);
    CAN_StructInit(&CAN);
    
    CAN.CAN_TTCM = DISABLE;
    CAN.CAN_ABOM = DISABLE;
    CAN.CAN_AWUM = DISABLE;
    CAN.CAN_NART = DISABLE;
    CAN.CAN_RFLM = DISABLE;
    CAN.CAN_TXFP = ENABLE;
    CAN.CAN_Mode = CAN_Mode_Normal;
    CAN.CAN_SJW  = CAN_SJW_1tq;
    CAN.CAN_BS1 = CAN_BS1_9tq;
    CAN.CAN_BS2 = CAN_BS2_4tq;
    CAN.CAN_Prescaler = 3;   //CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Init(CAN2, &CAN);

	CAN_filter.CAN_FilterNumber =14;
	CAN_filter.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_filter.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_filter.CAN_FilterIdHigh = 0x0000;
	CAN_filter.CAN_FilterIdLow = 0x0000;
	CAN_filter.CAN_FilterMaskIdHigh = 0x0000;
	CAN_filter.CAN_FilterMaskIdLow = 0x0000;
	CAN_filter.CAN_FilterFIFOAssignment = 0;
	CAN_filter.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_filter);
    
    CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN2,CAN_IT_TME,ENABLE);
}

unsigned char CAN_tx_success_flag_2 = 0;
unsigned char CAN_rx_success_flag_2 = 0;

/*************************************************************************
                          CAN2_TX_IRQHandler
描述：CAN2的发送中断函数
*************************************************************************/

void CAN2_TX_IRQHandler(void)
{ 

    if (CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET) 
	{
	   CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
       CAN_tx_success_flag_2=1;
    }

}
/*************************************************************************
                          CAN1_RX0_IRQHandler
描述：CAN2的接收中断函数
*************************************************************************/
void CAN2_RX0_IRQHandler(void)
{


  
    
    if (CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET)
	{
        CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
        CAN_Receive(CAN2, CAN_FIFO0, &rx2_message);
        CAN_rx_success_flag_2 = 1;
        
    }
}


void CAN2_DATA()
{
  int j;
  int count_speed =0;
  int count_PWM =0;
  if((rx2_message.StdId & 0x7F0)== 0x090)
  {
    for (int i=0;i<8;i++)
    {
      if(rx2_message.Data[i]==0x55)  //速度模式
      {
        count_speed++;
      }
      else if(rx2_message.Data[i]==0xAA)  //PWM模式
      {
        count_PWM++;
      }
      else ;
//          if(rx2_message.Data[i]==0x0)   //失能模式
//      {
//        break;
//      }
    }
    if ((count_speed ==8)||(count_PWM == 8 ))
    {
      Tx2_Message.StdId =rx2_message.StdId&0x1f;
      
      for(j=0;j<8;j++)
      {
       Tx2_Message.Data[j]=rx2_message.Data[j];
      }
      CAN2_Send_Msg();
      
      count_speed = 0;
      count_PWM = 0;
    }
    else ;
  }
  else if((rx2_message.StdId & 0x7F0)== 0x080)
  {
      robotw.speed0 = ((s16)rx2_message.Data[0]<<8)|((s16)rx2_message.Data[1]);
      robotw.speed1 = ((s16)rx2_message.Data[2]<<8)|((s16)rx2_message.Data[3]);
      robotw.speed2 = ((s16)rx2_message.Data[4]<<8)|((s16)rx2_message.Data[5]);
      robotw.speed3 = ((s16)rx2_message.Data[6]<<8)|((s16)rx2_message.Data[7]);
 
  }
//  else if((rx2_message.StdId & 0xF0)== 0xA0)
//  {
//      robotw.speed2 = ((s32)rx2_message.Data[0]<<24)|((s32)rx2_message.Data[1]<<16)|((s32)rx2_message.Data[2]<<8)|(s32)rx2_message.Data[3];
//      robotw.speed3 = ((s32)rx2_message.Data[4]<<24)|((s32)rx2_message.Data[5]<<16)|((s32)rx2_message.Data[6]<<8)|(s32)rx2_message.Data[7];
//  }
  else ;
  SetSpeed();
  if(!robotw.speed0)
      GPIO_ResetBits(GPIOE,GPIO_Pin_0);
  else
      GPIO_SetBits(GPIOE,GPIO_Pin_0);
  
  if(!robotw.speed1)
      GPIO_ResetBits(GPIOA,GPIO_Pin_15);
  else
      GPIO_SetBits(GPIOA,GPIO_Pin_15);
  
  if(!robotw.speed2)
      GPIO_ResetBits(GPIOD,GPIO_Pin_8);
  else
      GPIO_SetBits(GPIOD,GPIO_Pin_8);
  
  if(!robotw.speed3)
      GPIO_ResetBits(GPIOC,GPIO_Pin_5);
  else
      GPIO_SetBits(GPIOC,GPIO_Pin_5);
}
/*************************************************************************
                          u8 CAN2_Send_Msg(u8* msg,u8 len)
描述：CAN2的发送函数
*************************************************************************/
u8 CAN2_Send_Msg(void)
{	
	u8 mbox;
	u16 i = 0;
    // u16 CAN_ID;
   // u8 msg[8];
	//Tx2_Message.StdId = CAN_ID;	 
	Tx2_Message.ExtId = 0x00;	 
	Tx2_Message.IDE = 0;		   
	Tx2_Message.RTR = 0;		  
	Tx2_Message.DLC = 8;							 
	//for(i=0;i<8;i++)
	//	Tx2_Message.Data[i] = msg[i];				          
	mbox = CAN_Transmit(CAN2, &Tx2_Message);   
	i=0;
	while((CAN_TransmitStatus(CAN2, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	
	if(i>=0XFFF)return 1;
	return 0;		
	
}

