#ifndef _ONENET_H_
#define _ONENET_H_

//单片机头文件
#include "sys.h" 
#include "stm32f10x.h"

#define true 1
#define false 0

typedef struct
{
	u8 set_mode;
	u8 temp;
	u8 hum;
	u8 ligh;
	u8 soil_hum;
	int mq2_somke;
	u8 led_state;
	u8 mq2_flag;
	u8 fan_state;
	u8 temp_up_value;
	u8 hum_up_value;
	u8 ligh_up_value;
	u8 open_alarm_state;
	u8 hcsr501_flag;
	u8 open_hcsr501;
	u8 beep_state;
	int mq2_up_value;
//	float MQ2_Initial_Value;
}Send;

extern Send s;

_Bool OneNet_DevLink(void);

void OneNet_SendData(void);

void OneNet_RevPro(unsigned char *cmd);




#endif
