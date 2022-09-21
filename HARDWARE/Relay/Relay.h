#ifndef __RELAY_H
#define __RELAY_H	 
#include "sys.h"


void Moto_Init(void);
void Motor_Ctrl_Direction_Angle(int direction, int angle);
void MotorStop(void);//ֹͣ
void MotoRccw(void); //��ת
void MotoRcw(void); //��ת
void Relay_Init(void);		//��ʼ��

void Fan_ON(void);
void Fan_OFF(void);

void Hoot_ON(void);
void Hoot_OFF(void);
		 				    
#endif
