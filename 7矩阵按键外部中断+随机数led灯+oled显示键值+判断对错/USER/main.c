#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"//4x4���󰴼��ⲿ�ж�
#include "oled.h"
#include "random_generate.h"//���������
#include "beep.h" //����������



 int main(void)
 {		
	extern int KeyValue;
	extern int randomValue;
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڲ�����115200
 	LED_Init();		  		 //��ʼ����LED���ӵ�Ӳ���ӿ�
	OLED_Init();			   //��ʼ��OLED  
	OLED_Clear();  
	EXTIX_Init();		 	   //�ⲿ�жϳ�ʼ�
	Adc_Init();          //adc��ʼ��
	BEEP_Init();         	//��ʼ���������˿�


	KeyValue=17;
	led_output();//���led�����ʾ
	 
//	OLED_ShowCHinese(0,0,0);//��
//	OLED_ShowCHinese(18,0,1);//��
//	OLED_ShowCHinese(36,0,2);//԰
//	OLED_ShowCHinese(54,0,3);//��
//	OLED_ShowCHinese(72,0,4);//��
//	OLED_ShowCHinese(90,0,5);//��
//	OLED_ShowCHinese(108,0,6);//��
	


	while(1)
	{
//	OLED_Clear();
//		OLED_ShowCHinese(0,0,0);//��
//		OLED_ShowCHinese(18,0,1);//��
//		OLED_ShowCHinese(36,0,2);//԰
//		OLED_ShowCHinese(54,0,3);//�� 
//		OLED_ShowCHinese(72,0,4);//��
//		OLED_ShowCHinese(90,0,5);//��
//		OLED_ShowCHinese(108,0,6);//��
		
    if((KeyValue-1) == randomValue)
		{
				BEEP = 0;
				led_output();		
		}
		
		else
				BEEP = 1;
		
		delay_ms(50);

		
		OLED_ShowNum(0,2,(KeyValue-1),8,8);

	
	}
 }

