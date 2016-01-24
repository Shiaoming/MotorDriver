#include "includes.h"

extern u32 temp_val[20];

void ADC_Configuration(void);
 u16 Get_Adc(u8 ch);
 
extern float Get_Adc_Average(u8 ch,u8 times);
void delay_us(u32 us);