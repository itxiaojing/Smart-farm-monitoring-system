
//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//�����豸
#include "esp8266.h"

#include "adc.h"
#include "main.h"

//Э���ļ�
#include "onenet.h"
#include "mqttkit.h"

//Ӳ������
#include "usart.h"
#include "delay.h"


//C��
#include <string.h>
#include <stdio.h>

Send s;
//#define PROID		"��Ĳ�ƷID"

//#define AUTH_INFO	"��ļ�Ȩ��Ϣ"

//#define DEVID		"����豸ID"

#define PROID		"467713"

#define AUTH_INFO	"T001"

#define DEVID		"852848710"

extern unsigned char esp8266_buf[128];

u8 key;
u8 fan,bump,led; 

//==========================================================
//	�������ƣ�	OneNet_DevLink
//
//	�������ܣ�	��onenet��������
//
//	��ڲ�����	��
//
//	���ز�����	1-�ɹ�	0-ʧ��
//
//	˵����		��onenetƽ̨��������
//==========================================================
_Bool OneNet_DevLink(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};					//Э���

	unsigned char *dataPtr;
	
	_Bool status = 1;
	
	UsartPrintf(USART_DEBUG,"OneNET_DevLink\r\n");
	UsartPrintf(USART_DEBUG,"PROID: %s,	AUIF: %s,	DEVID:%s\r\n", PROID, AUTH_INFO, DEVID);
	
	if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 512, 0, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
	{
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//�ϴ�ƽ̨
		
		dataPtr = ESP8266_GetIPD(250);									//�ȴ�ƽ̨��Ӧ
		if(dataPtr != NULL)
		{
			if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
			{
				switch(MQTT_UnPacketConnectAck(dataPtr))
				{
					case 0:UsartPrintf(USART_DEBUG, "Tips:	���ӳɹ�\r\n");status = 0;break;
					
					case 1:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�Э�����\r\n");break;
					case 2:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��Ƿ���clientid\r\n");break;
					case 3:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�������ʧ��\r\n");break;
					case 4:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��û������������\r\n");break;
					case 5:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��Ƿ�����(����token�Ƿ�)\r\n");break;
					
					default:UsartPrintf(USART_DEBUG, "ERR:	����ʧ�ܣ�δ֪����\r\n");break;
				}
			}
		}
		
		MQTT_DeleteBuffer(&mqttPacket);								//ɾ��
		ESP8266_Clear();	
	}
	else
		UsartPrintf(USART_DEBUG, "WARN:	MQTT_PacketConnect Failed\r\n");
	
	return status;
	
}

unsigned char OneNet_FillBuf(char *buf)//Type3   CJson��ʽ
{
	char text[512];
	
	memset(text, 0, sizeof(text));

	strcpy(buf, "{");
	
	memset(text, 0, sizeof(text));                           //��text����
	sprintf(text, "\"farm_temp\":%d,",s.temp);             //���ƾ��Ȳ���ӡ��text��
	strcat(buf, text);  
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"farm_hum\":%d,", s.hum);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"farm_light\":%d,", s.ligh);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"farm_soil\":%d", s.soil_hum);
	strcat(buf, text);
//	
//	memset(text, 0, sizeof(text));
//	sprintf(text, "\"wifi_temp_up_value\":%d,", s.temp_up_value);
//	strcat(buf, text);
//	
//	memset(text, 0, sizeof(text));
//	sprintf(text, "\"wifi_hum_up_value\":%d,", s.hum_up_value);
//	strcat(buf, text);
//	
//	memset(text, 0, sizeof(text));
//	sprintf(text, "\"wifi_light_up_value\":%d,", s.ligh_up_value);
//	strcat(buf, text);
//	
//	memset(text, 0, sizeof(text));
//	sprintf(text, "\"wifi_mq2_up_value\":%d",s.mq2_up_value);
//	strcat(buf, text);
	
	strcat(buf, "}");
	
	return strlen(buf);

}

//==========================================================
//	�������ƣ�	OneNet_SendData
//
//	�������ܣ�	�ϴ����ݵ�ƽ̨
//
//	��ڲ�����	type���������ݵĸ�ʽ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_SendData(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};												//Э���
	
	char buf[512];
	
	short body_len = 0, i = 0;
	
	UsartPrintf(USART_DEBUG,"Tips:	OneNet_SendData-MQTT\r\n");
	
	memset(buf, 0, sizeof(buf));
	
	body_len = OneNet_FillBuf(buf);	//��װ����ΪCJson��ʽ����ȡ���ݳ���
	UsartPrintf(USART_DEBUG, "%s\r\n",buf);//�����͵����ݴ�ӡ����
	if(body_len)
	{
		if(MQTT_PacketSaveData(DEVID, body_len, NULL, 3, &mqttPacket) == 0)							//���������Ϊ��ʽ3
		{
			for(; i < body_len; i++)
				mqttPacket._data[mqttPacket._len++] = buf[i];
			
			ESP8266_SendData(mqttPacket._data, mqttPacket._len);									//�ϴ����ݵ�ƽ̨
			UsartPrintf(USART_DEBUG, "Send %d Bytes\r\n", mqttPacket._len);
			
			MQTT_DeleteBuffer(&mqttPacket);															//ɾ��
		}
		else
			UsartPrintf(USART_DEBUG,"WARN:	MQTT_NewBuffer Failed\r\n");
	}
	
}

//==========================================================
//	�������ƣ�	OneNet_RevPro
//
//	�������ܣ�	ƽ̨�������ݼ��
//
//	��ڲ�����	dataPtr��ƽ̨���ص�����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};								//Э���
	
	char *req_payload = NULL;
	char *cmdid_topic = NULL;
	
	unsigned short req_len = 0;
	
	unsigned char type = 0;
	
	short result = 0;

	char *dataPtr = NULL;
	char numBuf[10];
	int num = 0;
	char onenet_rx[20] = {0};
	
	
	type = MQTT_UnPacketRecv(cmd);
	switch(type)
	{
		case MQTT_PKT_CMD:															//�����·�
			
			result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len);	//���topic����Ϣ��
			if(result == 0)
			{
				UsartPrintf(USART_DEBUG,"cmdid: %s, req: %s, req_len: %d\r\n", cmdid_topic, req_payload, req_len);
				
				if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)	//����ظ����
				{
					UsartPrintf(USART_DEBUG,"Tips:	Send CmdResp\r\n");
					
					ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//�ظ�����
					MQTT_DeleteBuffer(&mqttPacket);									//ɾ��
				}
			}
		
		break;
			
		case MQTT_PKT_PUBACK:														//����Publish��Ϣ��ƽ̨�ظ���Ack
		
			if(MQTT_UnPacketPublishAck(cmd) == 0)
				UsartPrintf(USART_DEBUG,"Tips:	MQTT Publish Send OK\r\n");
			
		break;
		
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();									//��ջ���
	
	if(result == -1)
		return;
	
//	dataPtr = strchr(req_payload, '}');					//����'}'
	dataPtr = strchr(req_payload, ':');					//����'}'

	if(dataPtr != NULL && result != -1)					//����ҵ���
	{
		
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//�ж��Ƿ����·��������������
		{
			numBuf[num++] = *dataPtr++;
		}
		while(*dataPtr > '9')		//�ж��Ƿ����·��������������
		{
			numBuf[num++] = *dataPtr++;
		}
		
		num = atoi((const char *)numBuf);				//תΪ��ֵ��ʽ
		
//		if(strstr((char *)req_payload,"SET_MQ"))
//		{
//			strncpy(onenet_rx,(char *)req_payload + 7,4);
//			s.mq2_up_value = atoi(onenet_rx);			 
//			UsartPrintf(USART_DEBUG,"Tiips��				���յ�������ֵ: %d\r\n", s.mq2_up_value);
//			ESP8266_Clear();	
//		}
//		else if(strstr((char *)req_payload,"SET_LX"))
//		{
//			strncpy(onenet_rx,(char *)req_payload + 7,4);
//			s.ligh_up_value = atoi(onenet_rx);	
//			UsartPrintf(USART_DEBUG,"Tiips��				���յ�������ֵ: %d\r\n", s.ligh_up_value);
//			ESP8266_Clear();	
//		}
//		else if(strstr((char *)req_payload,"SET_TEMP"))
//		{
//			strncpy(onenet_rx,(char *)req_payload + 9,4);
//			s.temp_up_value = atoi(onenet_rx);	
//			UsartPrintf(USART_DEBUG,"Tiips��				���յ��¶���ֵ: %d\r\n", s.temp_up_value);
//			ESP8266_Clear();	
//		}
//		else if(strstr((char *)req_payload,"SET_HUMX"))
//		{
//			strncpy(onenet_rx,(char *)req_payload + 8,4);
//			s.hum_up_value = atoi(onenet_rx);	
//			UsartPrintf(USART_DEBUG,"Tiips��				���յ�ʪ������ֵ: %d\r\n", s.hum_up_value);
//			ESP8266_Clear();	
//		}
//		else if(strstr((char *)req_payload,"led"))
//		{
//			if(num == 1)
//			{
//				s.set_mode = 1;
//				UsartPrintf(USART_DEBUG,"\r\nTips:	led=1\r\n");
//			}
//			else if(num == 0)
//			{
//				s.set_mode = 2;
//				UsartPrintf(USART_DEBUG,"\r\nTips:	led=0\r\n");
//			}
//		}
//		else if(strstr((char *)req_payload,"fan"))
//		{
//			if(num == 1)
//			{
//				s.set_mode = 3;
//				UsartPrintf(USART_DEBUG,"\r\nTips:	fan=1\r\n");
//			}
//			else if(num == 0)
//			{
//				s.set_mode = 4;
//				UsartPrintf(USART_DEBUG,"\r\nTips:	fan=0\r\n");
//			}
//		}

	}

	if(type == MQTT_PKT_CMD || type == MQTT_PKT_PUBLISH)
	{
		MQTT_FreeBuffer(cmdid_topic);
		MQTT_FreeBuffer(req_payload);
	}
	
	ESP8266_Clear();	

}

