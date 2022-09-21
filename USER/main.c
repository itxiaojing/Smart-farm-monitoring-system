//硬件驱动
#include "main.h"


unsigned char temp_flag,ping_flag;
float MQ2_Initial_Value = 0.0f;
/*
************************************************************
*	函数名称：	Hardware_Init
*
*	函数功能：	硬件初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		初始化单片机功能以及外接设备
************************************************************
*/
void Hardware_Init(void)
{
  delay_init();
  NVIC_Configuration();
	TIM3_Int_Init(9999,7199);                       //定时器3，用于定时发送数据
  Usart1_Init(115200);                          //初始化串口1
	Usart2_Init(115200);                          //初始化串口2 wifi模块初始化
	LED_Init();																				//初始化LED灯
	T_Adc_Init();																//ADC初始化，烟雾
	DHT11_Init();                      					 //初始化DHT11
	Lsens_Init();                                 //初始化光敏
  ESP8266_Init();
  while(OneNet_DevLink());		              //接入OneNET
	LED_White_ON();
}

int main(void)
{
  Hardware_Init();

  while(1)
  {
		GET_Cmd();
	  main_send_data_show_task();
  }
}


//==========================================================
//	函数名称：	main_send_data_show_task
//
//	函数功能：	主函数的数据发送
//
//	入口参数：	NO
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void main_send_data_show_task(void)
{                         //读取光照值
	if(printf_flag)
	{
		s.soil_hum=Get_Adc_Average(1,10);
		DHT11_Read_Data(&s.temp,&s.hum);	                    //读取温湿度值	
	  s.ligh = Lsens_Get_Val();                        //获取光照值
		UsartPrintf(USART_DEBUG,"\r\nTips:        温度：%d    湿度：%d   光照：%d    土壤湿度：%d\r\n",s.temp,s.hum,s.ligh,s.soil_hum); 
		printf_flag = 0;
	}
	if(SENG_FLAG)									//发送间隔
	{
		OneNet_SendData();									//发送数据	
		ESP8266_Clear();
		SENG_FLAG = 0;
	}
}



void GET_Cmd(void)//获取指令
{
	unsigned char *dataPtr = NULL;
	dataPtr = ESP8266_GetIPD(0);

	if(dataPtr != NULL)
	OneNet_RevPro(dataPtr);
}


