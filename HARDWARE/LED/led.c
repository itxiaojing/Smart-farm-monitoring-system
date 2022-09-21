#include "led.h"
     
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);	 																										//ʹ��PB�˿�ʱ��

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 																											//�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 																											//IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);	
 GPIO_SetBits(GPIOC, GPIO_Pin_13);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	 
 GPIO_SetBits(GPIOB,GPIO_Pin_7 | GPIO_Pin_8);
}


//������ʾ�ƿ�
void LED_White_ON(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}
//������ʾ�ƹ�
void LED_White_OFF(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}





