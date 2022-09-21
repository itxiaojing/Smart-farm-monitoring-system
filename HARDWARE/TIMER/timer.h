#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define TIMER1_OFF_LED  1
#define TIMER2_SENG_DATA  1

extern u8  SENG_DATA,MQ2_DATA,LED_TIMER1;
extern int SENG_FLAG,MQ2_FLAG,LED_OFF_FlAG,printf_flag,beep_off_flag,beep_off_flag2;

void TIM1_Int_Init(u16 arr, u16 psc);
void TIM2_Int_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);

#endif

