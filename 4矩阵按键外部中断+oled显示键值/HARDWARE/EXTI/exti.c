#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "oled.h"

int KeyValue;

//�У�A1 A2 A3 A4
//�У�B4 B5 B6 B7
//����Ϊ�ⲿ�ж�


//////////////////////////////////////////////////////////define
//8������ 4��Ϊ�� 4��Ϊ��
//������˿ڶ���
#define X1_GPIO_PORT GPIOA           
#define X2_GPIO_PORT GPIOA   
#define X3_GPIO_PORT GPIOA           
#define X4_GPIO_PORT GPIOA 
//������˿ڶ���
#define Y1_GPIO_PORT GPIOB           
#define Y2_GPIO_PORT GPIOB   
#define Y3_GPIO_PORT GPIOB           
#define Y4_GPIO_PORT GPIOB 

//��������Ŷ���
#define X1_GPIO_PIN GPIO_Pin_1
#define X2_GPIO_PIN GPIO_Pin_2
#define X3_GPIO_PIN GPIO_Pin_3
#define X4_GPIO_PIN GPIO_Pin_4

//���������Ŷ���
#define Y1_GPIO_PIN GPIO_Pin_4
#define Y2_GPIO_PIN GPIO_Pin_5
#define Y3_GPIO_PIN GPIO_Pin_6
#define Y4_GPIO_PIN GPIO_Pin_7

//�����ʱ�Ӷ���
#define X1_RCC RCC_APB2Periph_GPIOA
#define X2_RCC RCC_APB2Periph_GPIOA
#define X3_RCC RCC_APB2Periph_GPIOA
#define X4_RCC RCC_APB2Periph_GPIOA

//������ʱ�Ӷ���
#define Y1_RCC RCC_APB2Periph_GPIOB
#define Y2_RCC RCC_APB2Periph_GPIOB
#define Y3_RCC RCC_APB2Periph_GPIOB
#define Y4_RCC RCC_APB2Periph_GPIOB

//��ֲ����ֻ��Ҫ�޸�����Ķ˿ں����ź�ʱ�Ӽ��ɣ�����Ĵ��벻���޸ġ�
//����������õ�8�����ſ������ɲ���������ʵ����Ҫ�͸��˰����Լ����塣

////////////////////////////////////////////////////////////////////////////////////////



void Matrix_KEY_Init(void)
{ 
	 GPIO_InitTypeDef GPIO_InitStructure;   
   RCC_APB2PeriphClockCmd(X1_RCC|X2_RCC|X3_RCC|X4_RCC|Y1_RCC|Y2_RCC|Y3_RCC|Y4_RCC|RCC_APB2Periph_AFIO, ENABLE);
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	
/**************************************4��״̬ ��������***********************************/
   GPIO_InitStructure.GPIO_Pin   =  X1_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IPU;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(X1_GPIO_PORT, &GPIO_InitStructure);	
   
   GPIO_InitStructure.GPIO_Pin   =  X2_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IPU;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(X2_GPIO_PORT, &GPIO_InitStructure);	
   
   GPIO_InitStructure.GPIO_Pin   =  X3_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IPU;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(X3_GPIO_PORT, &GPIO_InitStructure);	
	
	 GPIO_InitStructure.GPIO_Pin   =  X4_GPIO_PIN;   
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IPU;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(X4_GPIO_PORT, &GPIO_InitStructure);		
	
	
	
/*****************************4��״̬ �������*********************************************/
   GPIO_InitStructure.GPIO_Pin   =  Y1_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(Y1_GPIO_PORT, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin   =  Y2_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(Y2_GPIO_PORT, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin   =  Y3_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(Y3_GPIO_PORT, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin   =  Y4_GPIO_PIN ; 
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz; 
   GPIO_Init(Y4_GPIO_PORT, &GPIO_InitStructure);
   

	 
//	 ���õ�
	 	GPIO_ResetBits (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits (Y4_GPIO_PORT,Y4_GPIO_PIN);
		
		GPIO_SetBits   (X1_GPIO_PORT,X1_GPIO_PIN);
		GPIO_SetBits   (X2_GPIO_PORT,X2_GPIO_PIN);
		GPIO_SetBits   (X3_GPIO_PORT,X3_GPIO_PIN);
		GPIO_SetBits   (X4_GPIO_PORT,X4_GPIO_PIN);
}


//�ⲿ�жϹرպ���
void EXTI_disable(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 | EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);
}


//�ⲿ�жϿ�������
void EXTI_enable(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 | EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}


//�ⲿ�жϳ�ʼ��
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;

	  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
		Matrix_KEY_Init();	 //	�����˿ڳ�ʼ��

    //GPIOA.1 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOA.2	  �ж����Լ��жϳ�ʼ������ �����ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOA.3  �ж����Լ��жϳ�ʼ������  �����ش���	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOA.4	  �ж����Լ��жϳ�ʼ������  �����ش���	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���



  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}

//�ⲿ�ж�1�������    �����һ���ж�
void EXTI1_IRQHandler(void)
{
	delay_ms(50);
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)	 	 
	{	
		EXTI_disable();
		
		//���ø�,ɨ����		
		GPIO_SetBits (X1_GPIO_PORT,X1_GPIO_PIN);
		
		//��һ�а���
		GPIO_ResetBits  (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 1;			
			}
			
		//�ڶ��а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits  (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 2;	
			}

		//�����а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits  (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 3;
			}

		//�����а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits  (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 4;			
			}
			
		GPIO_ResetBits (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits (Y4_GPIO_PORT,Y4_GPIO_PIN);
			
		GPIO_SetBits   (X1_GPIO_PORT,X1_GPIO_PIN);
		GPIO_SetBits   (X2_GPIO_PORT,X2_GPIO_PIN);
		GPIO_SetBits   (X3_GPIO_PORT,X3_GPIO_PIN);
		GPIO_SetBits   (X4_GPIO_PORT,X4_GPIO_PIN);
			
		EXTI_enable();                      //�ⲿ�ж�ʹ��
		EXTI_ClearITPendingBit(EXTI_Line1); //���LINE1�ϵ��жϱ�־λ  
	}

}

//�ⲿ�ж�2�������     ����ڶ����ж�
void EXTI2_IRQHandler(void)
{
	delay_ms(50);
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)	 	 
	{	
		EXTI_disable();
		
		//���ø�,ɨ����		
		GPIO_SetBits (X2_GPIO_PORT,X2_GPIO_PIN);
		
		//��һ�а���
		GPIO_ResetBits  (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 5;			
			}
			
		//�ڶ��а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits  (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 6;			
			}

		//�����а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits  (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 7;				
			}

		//�����а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits  (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 8;				
			}
			
		GPIO_ResetBits (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits (Y4_GPIO_PORT,Y4_GPIO_PIN);
			
		GPIO_SetBits   (X1_GPIO_PORT,X1_GPIO_PIN);
		GPIO_SetBits   (X2_GPIO_PORT,X2_GPIO_PIN);
		GPIO_SetBits   (X3_GPIO_PORT,X3_GPIO_PIN);
		GPIO_SetBits   (X4_GPIO_PORT,X4_GPIO_PIN);
			
		EXTI_enable();                      //�ⲿ�ж�ʹ��
		EXTI_ClearITPendingBit(EXTI_Line2); //���LINE2�ϵ��жϱ�־λ  
	}
}


//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(50);
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)	 	 
	{	
		EXTI_disable();
		
		//���ø�,ɨ����		
		GPIO_SetBits (X3_GPIO_PORT,X3_GPIO_PIN);
		
		//��һ�а���
		GPIO_ResetBits  (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 9;				
			}
			
		//�ڶ��а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits  (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 10;				
			}

		//�����а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits  (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 11;				
			}

		//�����а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits  (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 12;				
			}
			
		GPIO_ResetBits (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits (Y4_GPIO_PORT,Y4_GPIO_PIN);
			
		GPIO_SetBits   (X1_GPIO_PORT,X1_GPIO_PIN);
		GPIO_SetBits   (X2_GPIO_PORT,X2_GPIO_PIN);
		GPIO_SetBits   (X3_GPIO_PORT,X3_GPIO_PIN);
		GPIO_SetBits   (X4_GPIO_PORT,X4_GPIO_PIN);
			
		EXTI_enable();                      //�ⲿ�ж�ʹ��
		EXTI_ClearITPendingBit(EXTI_Line3); //���LINE2�ϵ��жϱ�־λ  
	}
}

//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	delay_ms(50);
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)	 	 
	{	
		EXTI_disable();
		
		//���ø�,ɨ����		
		GPIO_SetBits (X4_GPIO_PORT,X4_GPIO_PIN);
		
		//��һ�а���
		GPIO_ResetBits  (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 13;				
			}
			
		//�ڶ��а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits  (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 14;				
			}

		//�����а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits  (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 15;				
			}

		//�����а���
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits  (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )); //�ȴ������ɿ�
				KeyValue = 16;				
			}
			
		GPIO_ResetBits (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits (Y4_GPIO_PORT,Y4_GPIO_PIN);
			
		GPIO_SetBits   (X1_GPIO_PORT,X1_GPIO_PIN);
		GPIO_SetBits   (X2_GPIO_PORT,X2_GPIO_PIN);
		GPIO_SetBits   (X3_GPIO_PORT,X3_GPIO_PIN);
		GPIO_SetBits   (X4_GPIO_PORT,X4_GPIO_PIN);
			
		EXTI_enable();                      //�ⲿ�ж�ʹ��
		EXTI_ClearITPendingBit(EXTI_Line4); //���LINE2�ϵ��жϱ�־λ  
	}
}
 
