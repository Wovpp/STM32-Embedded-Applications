#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"


 int main(void)
 {		
	extern 	int KeyValue;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڲ�����115200
 	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	 

	EXTIX_Init();		 	//�ⲿ�жϳ�ʼ��

//	LED0=0;					//����LED0
	 KeyValue=0;

	while(1)
	{	   
		if(KeyValue == 11)
		LED0=0;	

		
	}
 }

