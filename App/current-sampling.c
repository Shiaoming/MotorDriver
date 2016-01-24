/*******************************************************************************
文件名：current-sampling.c
功  能：电流抽样

*******************************************************************************/

#include "current-sampling.h"

void  Adc_Init(void)

{    
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
	ADC_InitTypeDef       ADC_InitStructure;
	
	
	
	//①开启ADC和GPIO相关时钟和初始化GPIO
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOA时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG |RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟
	
	
	
	//先初始化ADC1通道10-13 IO口
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//PA5 通道5
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化 
	
	
	
	// RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);        //ADC1复位
	
    // RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);     //复位结束    
	
	
	
	//②初始化通用配置
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay =
		
		ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	
	ADC_CommonInitStructure.ADC_DMAAccessMode =
		
		ADC_DMAAccessMode_Disabled; //DMA失能
	
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。
	
	//ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz
	
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	
	
	
	//③初始化ADC1相关参数
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式  
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//关闭连续转换
	
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	
	//禁止触发检测，使用软件触发
	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐      
	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中
	
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	
	
	
	//④开启ADC转换
	
	ADC_Cmd(ADC1, ENABLE);//开启AD转换器  
	
	
	
}                         
//获得ADC值

//ch:通道值 0~16: ch: @ref ADC_channels

//返回值:转换结果
u16 Get_Adc(u8 ch)  

{
	
	//设置指定ADC的规则组通道，一个序列，采样时间
	
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles);              
	
	ADC_SoftwareStartConv(ADC1);         //使能指定的ADC1的软件转换启动功能 
	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	
	return ADC_GetConversionValue(ADC1);     //返回最近一次ADC1规则组的转换结果
	
}
//获取通道ch的转换值，取times次,然后平均

//ch:通道编号  times:获取次数

//返回值:通道ch的times次转换结果平均值

u16 Get_Adc_Average(u8 ch,u8 times)

{

       u32 temp_val=0; u8 t;

       for(t=0;t<times;t++)

       {

              temp_val+=Get_Adc(ch);   
			 delay_us(5000);

       }

       return temp_val/times;

}

void delay_us(u32 us) 
{
	u32 temp;
      
	SysTick_Config(us*21);
	do
    
	{
	   
		temp = SysTick->CTRL;  //时间到了之后,该位将被硬件置1,但被查询后自动清0
    
	}
    
	while(temp & 0x01 && !(temp &(1<<16))); //查询
    
	SysTick->CTRL = 0x00;  //关闭计数器
    
	SysTick->VAL = 0x00;   //清空val
}


