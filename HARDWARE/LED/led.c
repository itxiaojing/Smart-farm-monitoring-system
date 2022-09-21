#include "led.h"
     
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);	 																										//使能PB端口时钟

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 																											//推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 																											//IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);	
 GPIO_SetBits(GPIOC, GPIO_Pin_13);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	 
 GPIO_SetBits(GPIOB,GPIO_Pin_7 | GPIO_Pin_8);
}


//板载提示灯开
void LED_White_ON(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}
//板载提示灯关
void LED_White_OFF(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}





