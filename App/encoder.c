/*******************************************************************************
文件名：encoder.c
功  能：码盘
说  明：TIM3，PA6，PA7    Motor_0
        TIM5，PA0，PA1    Motor_1
*******************************************************************************/
#include "encoder.h"
s16 tmp_0,tmp_1,tmp_2,tmp_3,gb_Y,gb_X;

float x_0=0,x_1=0;

u16 hValue_0,hValue_1,hValue_2,hValue_3;
s16 hValue_Y,hValue_X;
float Y_WalkDistance ,X_WalkDistance;
float Z_X_WalkDistance=0,Z_Y_WalkDistance=0;

void ENC_Init(void)
{    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 |RCC_APB1Periph_TIM5|RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM12,ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB |RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_TIM8|RCC_APB2Periph_TIM9, ENABLE);
	
	
	
	Encoder_0_Init();
	Encoder_1_Init();
	Encoder_2_Init();
	Encoder_3_Init();
	Encoder_X_Init();
	Encoder_Y_Init();
	//Encoder_Start();
}

void Encoder_X_Init(void)
{
	// 初始化结构体定义
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;

	// 初始化GPIO口
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ENC_X_A | ENC_X_B;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ENC_X_PORT, &GPIO_InitStructure);

	// 复用功能配置
	GPIO_PinAFConfig(ENC_X_PORT,ENC_X_A_PinSource,ENC_X_AF);
	GPIO_PinAFConfig(ENC_X_PORT,ENC_X_B_PinSource,ENC_X_AF);

	// 初始化定时器
	TIM_DeInit(ENC_X_TIM);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;//
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(ENC_X_TIM, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(ENC_X_TIM, TIM_EncoderMode_TI12,
							   TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 5;
	TIM_ICInit(ENC_TIM_1,&TIM_ICInitStructure);
	ENC_X_TIM->CNT = 0X7FFF;
	TIM_Cmd(ENC_X_TIM, ENABLE);
}

/*******************************************************************************
函 数 名：Encoder_Y_Init(void)
描    述：初始化Y方向的编码器
输入参数：NO
输出参数：NO
返 回 值：NO
*******************************************************************************/
void Encoder_Y_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
	
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ENC_Y_A | ENC_Y_B;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ENC_Y_PORT, &GPIO_InitStructure);

	// 复用功能配置
	GPIO_PinAFConfig(ENC_Y_PORT,ENC_Y_A_PinSource,ENC_Y_AF);
	GPIO_PinAFConfig(ENC_Y_PORT,ENC_Y_B_PinSource,ENC_Y_AF);

	TIM_DeInit(ENC_Y_TIM);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(ENC_Y_TIM, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(ENC_Y_TIM, TIM_EncoderMode_TI12,
							   TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 5;
	TIM_ICInit(ENC_TIM_1,&TIM_ICInitStructure);
	ENC_Y_TIM->CNT = 0X7FFF;
	TIM_Cmd(ENC_Y_TIM, ENABLE);
}

//0号电机码盘
void Encoder_0_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ENC_0_A;    //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ENC_PORT_0, &GPIO_InitStructure);

	
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ENC_0_B;    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ENC_PORT_00, &GPIO_InitStructure);

	GPIO_PinAFConfig(ENC_PORT_0,GPIO_PinSource5,GPIO_AF_TIM2);
	GPIO_PinAFConfig(ENC_PORT_00,GPIO_PinSource3,GPIO_AF_TIM2);
	
	TIM_DeInit(ENC_TIM_0);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
	TIM_TimeBaseStructure.TIM_Period = 65535;      
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(ENC_TIM_0, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(ENC_TIM_0, TIM_EncoderMode_TI12, 
							   TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	ENC_TIM_0->CNT= 0X7FFF; 
	TIM_Cmd(ENC_TIM_0, ENABLE);  
}


//1号电机码盘
void Encoder_1_Init(void)
{    
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ENC_1_A|ENC_1_B;    //PA0:TIM5_CH1 PA1:TIM5_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ENC_PORT_1, &GPIO_InitStructure);
	GPIO_PinAFConfig(ENC_PORT_1,GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_PinAFConfig(ENC_PORT_1,GPIO_PinSource13,GPIO_AF_TIM4);
	
	TIM_DeInit(ENC_TIM_1);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);    
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;   
	TIM_TimeBaseStructure.TIM_Period = 65535;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(ENC_TIM_1, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(ENC_TIM_1, TIM_EncoderMode_TI12, 
							    TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 5;
	TIM_ICInit(ENC_TIM_1,&TIM_ICInitStructure);
	ENC_TIM_1->CNT= 0X7FFF;                             
	TIM_Cmd(ENC_TIM_1, ENABLE);  
	
}
//2号电机码盘
void Encoder_2_Init(void)
{    
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ENC_2_A|ENC_2_B;    //PA0:TIM5_CH1 PA1:TIM5_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ENC_PORT_2, &GPIO_InitStructure);

	GPIO_PinAFConfig(ENC_PORT_2,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(ENC_PORT_2,GPIO_PinSource7,GPIO_AF_TIM3);
	
	TIM_DeInit(ENC_TIM_2);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);    
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;   
	TIM_TimeBaseStructure.TIM_Period = 65535;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(ENC_TIM_2, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(ENC_TIM_2, TIM_EncoderMode_TI12, 
							   TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	ENC_TIM_2->CNT= 0X7FFF;                             
	TIM_Cmd(ENC_TIM_2, ENABLE);  
}

//3号电机码盘
void Encoder_3_Init(void)
{    
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ENC_3_A|ENC_3_B;    //PC6:TIM8_CH1 PC7:TIM8_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ENC_PORT_3, &GPIO_InitStructure);

	GPIO_PinAFConfig(ENC_PORT_3,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(ENC_PORT_3,GPIO_PinSource1,GPIO_AF_TIM5);
	
	TIM_DeInit(ENC_TIM_3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);    
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;   
	TIM_TimeBaseStructure.TIM_Period = 65535;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(ENC_TIM_3, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(ENC_TIM_3, TIM_EncoderMode_TI12, 
							   TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	ENC_TIM_3->CNT= 0X7FFF;                              
	TIM_Cmd(ENC_TIM_3, ENABLE);  
}


void ENC_Read(void)
{
	// static s32 pre_0=0,pre_1=0,pre_2=0,pre_3=0;
	
	

	hValue_Y = ENC_Y_TIM->CNT;					//读取码盘值
	gb_Y = hValue_Y-0X7FFF;                                  	//计算增量，防止溢出
	ENC_Y_TIM->CNT = 0X7FFF;
	Y_WalkDistance = gb_Y*ENC_COEF;				//Y码盘行走的距离
	Z_Y_WalkDistance += gb_Y*ENC_COEF;			//Y码盘行走的距离累加总值
 
   

	hValue_X = ENC_X_TIM->CNT;					//读取码盘值
	gb_X = hValue_X-0X7FFF;                    	//计算增量，防止溢出
	ENC_X_TIM->CNT = 0X7FFF;
	X_WalkDistance = gb_X*ENC_COEF;				//X码盘行走的距离
	Z_X_WalkDistance += gb_X*ENC_COEF;			//X码盘行走的距离累加总值
        
        
//        x_tmp_pos=((gb_X-RX*angle_tmp)*cos(angle_pre-angle_y) + (gb_Y+RY*angle_tmp)*sin(angle_pre+angle_x))/cos(angle_pre+angle_x - angle_y); //cos()double型变量
//        y_tmp_pos=((gb_X-RX*angle_tmp)*sin(angle_pre-angle_y) - (gb_Y+RY*angle_tmp)*cos(angle_pre+angle_x))/cos(angle_pre+angle_x- angle_y);//编码angle_x器1000P/R，编码轮子直径5CM
//      
//        
//        x_now_pos = x_pre_pos + x_tmp_pos; 
//        y_now_pos = y_pre_pos + y_tmp_pos;
//	 
//        x_pre_pos = x_now_pos;
//        y_pre_pos = y_now_pos;
//	 
//	 
//	  x=x_now_pos*PI*50.913310359/2000;// - xold;//14zhou
//        y=y_now_pos*PI*50.913310359/2000;// - yold;
	
	hValue_0 = ENC_TIM_0->CNT;
	tmp_0 = hValue_0-0X7FFF; 
	ENC_TIM_0->CNT= 0X7FFF;
	//  tmp_0 =  hValue_0-pre_0 ;
	//pre_0 = hValue_0;
	
	//  x_0 += tmp_0*ENC_COEF_0;        //轮子行走距离
	
	hValue_1 = ENC_TIM_1->CNT;
	tmp_1 = hValue_1-0X7FFF; 
	ENC_TIM_1->CNT= 0X7FFF;
	// tmp_1 = pre_1-hValue_1;
	//   pre_1 = hValue_1;
	
	//   x_1 -= tmp_1*ENC_COEF_1;        //轮子行走距离
	
	hValue_2 = ENC_TIM_2->CNT;
	tmp_2 = hValue_2-0X7FFF; 
	ENC_TIM_2->CNT= 0X7FFF;
	//  tmp_0 =  hValue_0-pre_0 ;
	//pre_0 = hValue_0;
	
	//  x_2 += tmp_2*ENC_COEF_2;        //轮子行走距离
	
	hValue_3 = ENC_TIM_3->CNT;
	tmp_3 = hValue_3-0X7FFF; 
	ENC_TIM_3->CNT= 0X7FFF;
	//  tmp_0 =  hValue_0-pre_0 ;
	//pre_0 = hValue_0;
	
	// x_3 += tmp_0*ENC_COEF_3;        //轮子行走距离
	
	
}

void Encoder_Start(void)
{
	TIM3->CNT = 0x7fff;
}

int Encoder_Get_CNT(void)
{
	int cnt = 0;
	cnt = (TIM3->CNT)-0x7fff;
	TIM3->CNT = 0x7fff;
	return cnt;
}
