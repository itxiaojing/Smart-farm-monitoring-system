#ifndef __TSENSOR_H
#define __TSENSOR_H	
#include "stm32f10x.h"


    
extern float temp_avrg;
extern u8 shidu1;;
   
short Get_Temprate(void);			//��ȡ�ڲ��¶ȴ������¶�ֵ
void T_Adc_Init(void); //ADCͨ����ʼ��
u16  T_Get_Adc(u8 ch); //���ĳ��ͨ��ֵ  
u16  T_Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ��10�β�����ƽ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);
u16 Water_Get_Vol(void);
 
void Adc2_Init(void);
u16 Get_Adc2(u8 ch);  

void Adc3_Init(void); 				//ADC3��ʼ��
u16  Get_Adc3(u8 ch); 				//���ADC3ĳ��ͨ��ֵ  

#endif 
