#ifndef __TSENSOR_H
#define __TSENSOR_H	
#include "stm32f10x.h"


    
extern float temp_avrg;
extern u8 shidu1;;
   
short Get_Temprate(void);			//获取内部温度传感器温度值
void T_Adc_Init(void); //ADC通道初始化
u16  T_Get_Adc(u8 ch); //获得某个通道值  
u16  T_Get_Adc_Average(u8 ch,u8 times);//得到某个通道10次采样的平均值 
u16 Get_Adc_Average(u8 ch,u8 times);
u16 Water_Get_Vol(void);
 
void Adc2_Init(void);
u16 Get_Adc2(u8 ch);  

void Adc3_Init(void); 				//ADC3初始化
u16  Get_Adc3(u8 ch); 				//获得ADC3某个通道值  

#endif 
