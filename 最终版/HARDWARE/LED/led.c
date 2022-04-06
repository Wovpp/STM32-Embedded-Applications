#include "led.h"
#include "random_generate.h"//���������

//LED0 C13
//LED1 C14
//LED2 C15
//LED3 A0

int randomValue;

//��ʼ��Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PC�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PC.13 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.13
 GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PC.13 �����
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				 //LED0-->PC.14 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.14
 GPIO_SetBits(GPIOC,GPIO_Pin_14);						 //PC.14 �����
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //LED0-->PC.15 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.15
 GPIO_SetBits(GPIOC,GPIO_Pin_15);						 //PC.15 �����


 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //LED0-->PA.0 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.0
 GPIO_SetBits(GPIOA,GPIO_Pin_0);						 //PC.15 �����

}


void led_output(void)  //��ˮ���������
{
			
		randomValue=random();
		LED0=~(randomValue&0x01);
	  LED1=~((randomValue>>1)&0x01);
	  LED2=~((randomValue>>2)&0x01);
	  LED3=~((randomValue>>3)&0x01);
	

}
 
