#include "Tim.h"
#include "sys.h"


extern unsigned char temp_flag,ping_flag;

//void Tim1_Init(int arr,int psc)//500ms����һ��
//{ 
//   TIM_TimeBaseInitTypeDef TIM_Structure;               //���嶨ʱ���ṹ�����
//	 NVIC_InitTypeDef NVIC_TIM;                           //�����ж�Ƕ�׽ṹ�����
//	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  //�򿪶�ʱ��ʱ��
//	 
//	 TIM_Structure.TIM_Period = (arr-1) ;         //�����Զ���װ�ؼĴ�������ֵ  ���ʱ��TimeOut= (arr)*(psc)/Tic    ��λΪus
//   TIM_Structure.TIM_Prescaler = (psc-1);       //����Ԥ��Ƶֵ     
//   TIM_Structure.TIM_CounterMode = TIM_CounterMode_Up ;     //����ģʽ ��������
//	 TIM_Structure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ      Tic=72M/��TIM_ClockDivision+1��
//	 TIM_Structure.TIM_RepetitionCounter = 0; //�ظ������Ĵ���
//	
//	 TIM_TimeBaseInit(TIM1,&TIM_Structure);   //��ʼ����ʱ��1
//	
//	 NVIC_TIM.NVIC_IRQChannel = TIM1_UP_IRQn;  //��ʱ��1�����ϼ���ͨ��
//	 NVIC_TIM.NVIC_IRQChannelCmd = ENABLE ;    //ʹ��
//	 NVIC_TIM.NVIC_IRQChannelPreemptionPriority = 0 ;    //��ռ���ȼ�
//	 NVIC_TIM.NVIC_IRQChannelSubPriority = 0;            //��Ӧ���ȼ� 
//	
//	 NVIC_Init(&NVIC_TIM);                     //��ʼ���ṹ��
//	 
//	 TIM_ClearFlag(TIM1,TIM_FLAG_Update);      //������б�־λ  ��֤����״̬��ʼ�� 
//	 
//	 TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);  //�򿪼�ʱ��
//	
//	 TIM_Cmd(TIM1,ENABLE);      	  	 	       //��TIM1
//	
//	 
//}	

///*****��ʱ��1�ж���Ӧ����*****/
///*   ��Ҫ��ѯ�жϺ������� ��� startup_stm32f10x_hd.s�����ļ���ѯ��Ӧ���ж���Ӧ����*/
///*   ˵����TIM_ClearFlag()����������ö�ʱ�������б�־λ  
//          һ����ʱ���ı�־λ�����ܶ��� TIM_IT_Update TIM_IT_CC1 TIM_IT_CC2 TIM_IT_CC3 �� 
//          ���������þ�����ձ�־λ����TIM_ClearITPendingBit() ��ĳ����־λ������� �����û�м�����־λͬʱ���� ��������ʹ��Ч��Ӧ����һ����  */

//void TIM1_UP_IRQHandler (void)                
//{
//	static unsigned int temp_count,ping_count;

//	if(TIM_GetITStatus(TIM1,TIM_IT_Update) != RESET)   //����жϱ�־����1 ֤�����ж�
//	{
//	 
//		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);    // ��ձ�־λ��Ϊ��һ�ν����ж���׼��

//	 temp_count++;
//	 ping_count++;
//		
//	 if(temp_count == 2000)//20s
//	 {
//		 temp_flag=1;
//		 temp_count=0;
//	 } 
//	if(ping_count == 8000)//40s
//		 {
//			 ping_flag=1;
//			 ping_count=0;
//		 } 
//	}
//  
//}





