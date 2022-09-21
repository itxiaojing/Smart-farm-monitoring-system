#ifndef __RELAY_H
#define __RELAY_H	 
#include "sys.h"


void Moto_Init(void);
void Motor_Ctrl_Direction_Angle(int direction, int angle);
void MotorStop(void);//停止
void MotoRccw(void); //正转
void MotoRcw(void); //反转
void Relay_Init(void);		//初始化

void Fan_ON(void);
void Fan_OFF(void);

void Hoot_ON(void);
void Hoot_OFF(void);
		 				    
#endif
