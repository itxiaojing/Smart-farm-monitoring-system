#ifndef _ESP8266_H_
#define _ESP8266_H_

#define REV_OK		0	//������ɱ�־
#define REV_WAIT	1	//����δ��ɱ�־


#define AT          "AT\r\n"	
#define CWMODE      "AT+CWMODE=3\r\n"		//STA+APģʽ
#define CWDHCP      "AT+CWDHCP=1,1\r\n"		//STA+APģʽ
#define RST         "AT+RST\r\n"
#define CIFSR       "AT+CIFSR\r\n"
//#define CWJAP       "AT+CWJAP=\"��ҵ�WiFi����\",\"��ҵ�WiFi����\"\r\n"	//ssid: onenet ���룺��
#define CWJAP       "AT+CWJAP=\"CAWL\",\"83249995\"\r\n"	//ssid: onenet ���룺��
#define CIPSTART    "AT+CIPSTART=\"TCP\",\"183.230.40.39\",6002\r\n"	//MQTT������ 183.230.40.39/876   
#define CIPMODE0    "AT+CIPMODE=0\r\n"		//��͸��ģʽ
#define CIPMODE1    "AT+CIPMODE=1\r\n"		//͸��ģʽ
#define CIPSEND     "AT+CIPSEND\r\n"   
#define Out_CIPSEND     "+++" 
#define CIPSTATUS   "AT+CIPSTATUS\r\n"		//����״̬��ѯ



void ESP8266_Init(void);

void ESP8266_Clear(void);

void ESP8266_SendData(unsigned char *data, unsigned short len);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);

void MQTT_Ping(void);
#endif
