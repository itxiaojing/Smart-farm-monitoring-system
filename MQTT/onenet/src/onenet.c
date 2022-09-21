
//单片机头文件
#include "stm32f10x.h"

//网络设备
#include "esp8266.h"

#include "adc.h"
#include "main.h"

//协议文件
#include "onenet.h"
#include "mqttkit.h"

//硬件驱动
#include "usart.h"
#include "delay.h"


//C库
#include <string.h>
#include <stdio.h>

Send s;
//#define PROID		"你的产品ID"

//#define AUTH_INFO	"你的鉴权信息"

//#define DEVID		"你的设备ID"

#define PROID		"467713"

#define AUTH_INFO	"T001"

#define DEVID		"852848710"

extern unsigned char esp8266_buf[128];

u8 key;
u8 fan,bump,led; 

//==========================================================
//	函数名称：	OneNet_DevLink
//
//	函数功能：	与onenet创建连接
//
//	入口参数：	无
//
//	返回参数：	1-成功	0-失败
//
//	说明：		与onenet平台建立连接
//==========================================================
_Bool OneNet_DevLink(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};					//协议包

	unsigned char *dataPtr;
	
	_Bool status = 1;
	
	UsartPrintf(USART_DEBUG,"OneNET_DevLink\r\n");
	UsartPrintf(USART_DEBUG,"PROID: %s,	AUIF: %s,	DEVID:%s\r\n", PROID, AUTH_INFO, DEVID);
	
	if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 512, 0, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
	{
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//上传平台
		
		dataPtr = ESP8266_GetIPD(250);									//等待平台响应
		if(dataPtr != NULL)
		{
			if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
			{
				switch(MQTT_UnPacketConnectAck(dataPtr))
				{
					case 0:UsartPrintf(USART_DEBUG, "Tips:	连接成功\r\n");status = 0;break;
					
					case 1:UsartPrintf(USART_DEBUG, "WARN:	连接失败：协议错误\r\n");break;
					case 2:UsartPrintf(USART_DEBUG, "WARN:	连接失败：非法的clientid\r\n");break;
					case 3:UsartPrintf(USART_DEBUG, "WARN:	连接失败：服务器失败\r\n");break;
					case 4:UsartPrintf(USART_DEBUG, "WARN:	连接失败：用户名或密码错误\r\n");break;
					case 5:UsartPrintf(USART_DEBUG, "WARN:	连接失败：非法链接(比如token非法)\r\n");break;
					
					default:UsartPrintf(USART_DEBUG, "ERR:	连接失败：未知错误\r\n");break;
				}
			}
		}
		
		MQTT_DeleteBuffer(&mqttPacket);								//删包
		ESP8266_Clear();	
	}
	else
		UsartPrintf(USART_DEBUG, "WARN:	MQTT_PacketConnect Failed\r\n");
	
	return status;
	
}

unsigned char OneNet_FillBuf(char *buf)//Type3   CJson格式
{
	char text[512];
	
	memset(text, 0, sizeof(text));

	strcpy(buf, "{");
	
	memset(text, 0, sizeof(text));                           //将text清零
	sprintf(text, "\"farm_temp\":%d,",s.temp);             //控制精度并打印到text中
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
//	函数名称：	OneNet_SendData
//
//	函数功能：	上传数据到平台
//
//	入口参数：	type：发送数据的格式
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_SendData(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};												//协议包
	
	char buf[512];
	
	short body_len = 0, i = 0;
	
	UsartPrintf(USART_DEBUG,"Tips:	OneNet_SendData-MQTT\r\n");
	
	memset(buf, 0, sizeof(buf));
	
	body_len = OneNet_FillBuf(buf);	//封装数据为CJson格式并获取数据长度
	UsartPrintf(USART_DEBUG, "%s\r\n",buf);//将发送的数据打印出来
	if(body_len)
	{
		if(MQTT_PacketSaveData(DEVID, body_len, NULL, 3, &mqttPacket) == 0)							//封包，设置为格式3
		{
			for(; i < body_len; i++)
				mqttPacket._data[mqttPacket._len++] = buf[i];
			
			ESP8266_SendData(mqttPacket._data, mqttPacket._len);									//上传数据到平台
			UsartPrintf(USART_DEBUG, "Send %d Bytes\r\n", mqttPacket._len);
			
			MQTT_DeleteBuffer(&mqttPacket);															//删包
		}
		else
			UsartPrintf(USART_DEBUG,"WARN:	MQTT_NewBuffer Failed\r\n");
	}
	
}

//==========================================================
//	函数名称：	OneNet_RevPro
//
//	函数功能：	平台返回数据检测
//
//	入口参数：	dataPtr：平台返回的数据
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};								//协议包
	
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
		case MQTT_PKT_CMD:															//命令下发
			
			result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len);	//解出topic和消息体
			if(result == 0)
			{
				UsartPrintf(USART_DEBUG,"cmdid: %s, req: %s, req_len: %d\r\n", cmdid_topic, req_payload, req_len);
				
				if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)	//命令回复组包
				{
					UsartPrintf(USART_DEBUG,"Tips:	Send CmdResp\r\n");
					
					ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//回复命令
					MQTT_DeleteBuffer(&mqttPacket);									//删包
				}
			}
		
		break;
			
		case MQTT_PKT_PUBACK:														//发送Publish消息，平台回复的Ack
		
			if(MQTT_UnPacketPublishAck(cmd) == 0)
				UsartPrintf(USART_DEBUG,"Tips:	MQTT Publish Send OK\r\n");
			
		break;
		
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();									//清空缓存
	
	if(result == -1)
		return;
	
//	dataPtr = strchr(req_payload, '}');					//搜索'}'
	dataPtr = strchr(req_payload, ':');					//搜索'}'

	if(dataPtr != NULL && result != -1)					//如果找到了
	{
		
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//判断是否是下发的命令控制数据
		{
			numBuf[num++] = *dataPtr++;
		}
		while(*dataPtr > '9')		//判断是否是下发的命令控制数据
		{
			numBuf[num++] = *dataPtr++;
		}
		
		num = atoi((const char *)numBuf);				//转为数值形式
		
//		if(strstr((char *)req_payload,"SET_MQ"))
//		{
//			strncpy(onenet_rx,(char *)req_payload + 7,4);
//			s.mq2_up_value = atoi(onenet_rx);			 
//			UsartPrintf(USART_DEBUG,"Tiips：				接收到烟雾阈值: %d\r\n", s.mq2_up_value);
//			ESP8266_Clear();	
//		}
//		else if(strstr((char *)req_payload,"SET_LX"))
//		{
//			strncpy(onenet_rx,(char *)req_payload + 7,4);
//			s.ligh_up_value = atoi(onenet_rx);	
//			UsartPrintf(USART_DEBUG,"Tiips：				接收到光照阈值: %d\r\n", s.ligh_up_value);
//			ESP8266_Clear();	
//		}
//		else if(strstr((char *)req_payload,"SET_TEMP"))
//		{
//			strncpy(onenet_rx,(char *)req_payload + 9,4);
//			s.temp_up_value = atoi(onenet_rx);	
//			UsartPrintf(USART_DEBUG,"Tiips：				接收到温度阈值: %d\r\n", s.temp_up_value);
//			ESP8266_Clear();	
//		}
//		else if(strstr((char *)req_payload,"SET_HUMX"))
//		{
//			strncpy(onenet_rx,(char *)req_payload + 8,4);
//			s.hum_up_value = atoi(onenet_rx);	
//			UsartPrintf(USART_DEBUG,"Tiips：				接收到湿度照阈值: %d\r\n", s.hum_up_value);
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

