#ifndef _MAIN_H_
#define _MAIN_H_
#include "sys.h" 

//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//�����豸����
#include "esp8266.h"

//Ӳ������
#include "sys.h"
#include "timer.h"
#include "delay.h"
#include "usart.h"
#include "onenet.h"
#include "main.h"
#include "Tim.h"
#include "led.h"
#include "adc.h"
#include "dht11.h"
#include "lsens.h"
#include "beep.h"
#include "Relay.h"

//C��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFLEN 1024      //���黺���С

void main_send_data_show_task(void);
void set_threshold_value_task(void);
void mq2_data_show_task(void);
void GET_Cmd(void);
void beep_on_ring(void);
void beep_on_hscr05_ring(void);
void hcsr501_data_show_task(void);


#endif 

