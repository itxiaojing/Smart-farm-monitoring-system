#ifndef _MAIN_H_
#define _MAIN_H_
#include "sys.h" 

//单片机头文件
#include "stm32f10x.h"

//网络设备驱动
#include "esp8266.h"

//硬件驱动
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

//C库
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFLEN 1024      //数组缓存大小

void main_send_data_show_task(void);
void set_threshold_value_task(void);
void mq2_data_show_task(void);
void GET_Cmd(void);
void beep_on_ring(void);
void beep_on_hscr05_ring(void);
void hcsr501_data_show_task(void);


#endif 

