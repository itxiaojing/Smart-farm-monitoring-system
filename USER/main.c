//Ӳ������
#include "main.h"


unsigned char temp_flag,ping_flag;
float MQ2_Initial_Value = 0.0f;
/*
************************************************************
*	�������ƣ�	Hardware_Init
*
*	�������ܣ�	Ӳ����ʼ��
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		��ʼ����Ƭ�������Լ�����豸
************************************************************
*/
void Hardware_Init(void)
{
  delay_init();
  NVIC_Configuration();
	TIM3_Int_Init(9999,7199);                       //��ʱ��3�����ڶ�ʱ��������
  Usart1_Init(115200);                          //��ʼ������1
	Usart2_Init(115200);                          //��ʼ������2 wifiģ���ʼ��
	LED_Init();																				//��ʼ��LED��
	T_Adc_Init();																//ADC��ʼ��������
	DHT11_Init();                      					 //��ʼ��DHT11
	Lsens_Init();                                 //��ʼ������
  ESP8266_Init();
  while(OneNet_DevLink());		              //����OneNET
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
//	�������ƣ�	main_send_data_show_task
//
//	�������ܣ�	�����������ݷ���
//
//	��ڲ�����	NO
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void main_send_data_show_task(void)
{                         //��ȡ����ֵ
	if(printf_flag)
	{
		s.soil_hum=Get_Adc_Average(1,10);
		DHT11_Read_Data(&s.temp,&s.hum);	                    //��ȡ��ʪ��ֵ	
	  s.ligh = Lsens_Get_Val();                        //��ȡ����ֵ
		UsartPrintf(USART_DEBUG,"\r\nTips:        �¶ȣ�%d    ʪ�ȣ�%d   ���գ�%d    ����ʪ�ȣ�%d\r\n",s.temp,s.hum,s.ligh,s.soil_hum); 
		printf_flag = 0;
	}
	if(SENG_FLAG)									//���ͼ��
	{
		OneNet_SendData();									//��������	
		ESP8266_Clear();
		SENG_FLAG = 0;
	}
}



void GET_Cmd(void)//��ȡָ��
{
	unsigned char *dataPtr = NULL;
	dataPtr = ESP8266_GetIPD(0);

	if(dataPtr != NULL)
	OneNet_RevPro(dataPtr);
}


