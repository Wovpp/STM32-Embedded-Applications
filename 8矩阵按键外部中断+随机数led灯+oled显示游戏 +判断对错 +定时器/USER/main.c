#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"//4x4���󰴼��ⲿ�ж�
#include "oled.h"
#include "random_generate.h"//���������
#include "beep.h" //����������
#include "timer.h"



 int main(void)
 {		
	extern int KeyValue;
	extern int randomValue;
	extern int score;
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڲ�����115200
 	LED_Init();		  		 //��ʼ����LED���ӵ�Ӳ���ӿ�
	OLED_Init();			   //��ʼ��OLED  
	OLED_Clear();  
	EXTIX_Init();		 	   //�ⲿ�жϳ�ʼ�
	Adc_Init();          //adc��ʼ��
	BEEP_Init();         	//��ʼ���������˿�
	 
	TIM3_Int_Init(29999,71999);//1Khz�ļ���Ƶ�ʣ�������29999Ϊ30s


	KeyValue=17;
	led_output();//���led�����ʾ

	while(1)
	{

		OLED_ShowCHinese(0,0,0);//��
		OLED_ShowCHinese(16,0,0);//��
		OLED_ShowCHinese(32,0,1);//˭
		OLED_ShowCHinese(48,0,2);//�� 
		OLED_ShowCHinese(64,0,3);//��
		OLED_ShowCHinese(80,0,4);//Ӧ
		OLED_ShowCHinese(96,0,5);//��
		OLED_ShowCHinese(112,0,6);//�
		
    if((KeyValue-1) == randomValue)
		{
			//��������
//				BEEP = 0;
//				delay_ms(50);
//				BEEP = 1;
				score++;
				led_output();		
		}
//		else
//				BEEP = 1;
		
		delay_ms(50);

		
		OLED_ShowString(0,2,"score:",7);
		OLED_ShowNum(50,2,score,8,8);
		OLED_ShowString(0,4,"time:   30s",10);
		OLED_ShowString(0,6,"KEY: ",5);
		OLED_ShowNum(50,6,(KeyValue-1),8,8);
	
	}
 }

