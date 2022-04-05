#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"
#include "oled.h"


 int main(void)
 {		
	extern 	int KeyValue;
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڲ�����115200
 	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear();  
	EXTIX_Init();		 	//�ⲿ�жϳ�ʼ��


	 KeyValue=0;
	 
	 
	OLED_ShowCHinese(0,0,0);//��
	OLED_ShowCHinese(18,0,1);//��
	OLED_ShowCHinese(36,0,2);//԰
	OLED_ShowCHinese(54,0,3);//��
	OLED_ShowCHinese(72,0,4);//��
	OLED_ShowCHinese(90,0,5);//��
	OLED_ShowCHinese(108,0,6);//��

	while(1)
	{
//		OLED_Clear();
		OLED_ShowCHinese(0,0,0);//��
		OLED_ShowCHinese(18,0,1);//��
		OLED_ShowCHinese(36,0,2);//԰
		OLED_ShowCHinese(54,0,3);//�� 
		OLED_ShowCHinese(72,0,4);//��
		OLED_ShowCHinese(90,0,5);//��
		OLED_ShowCHinese(108,0,6);//��
		
		OLED_ShowNum(0,4,KeyValue,8,8);

		
	}
 }

