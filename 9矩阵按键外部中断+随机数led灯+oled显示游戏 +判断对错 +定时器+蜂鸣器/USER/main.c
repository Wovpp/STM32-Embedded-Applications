#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"//4x4¾ØÕó°´¼üÍâ²¿ÖĞ¶Ï
#include "oled.h"
#include "random_generate.h"//Éú³ÉËæ»úÊı
#include "beep.h" //·äÃùÆ÷Çı¶¯
#include "timer.h"



 int main(void)
 {		
	extern int KeyValue;
	extern int randomValue;
	extern int score;
	int i;  //Ñ­»·±äÁ¿
	 
	delay_init();	    	 //ÑÓÊ±º¯Êı³õÊ¼»¯	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //ÉèÖÃNVICÖĞ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	uart_init(115200);	 //´®¿Ú²¨ÌØÂÊ115200
 	LED_Init();		  		 //³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼ş½Ó¿Ú
	OLED_Init();			   //³õÊ¼»¯OLED  
	OLED_Clear();  
	EXTIX_Init();		 	   //Íâ²¿ÖĞ¶Ï³õÊ¼»
	Adc_Init();          //adc³õÊ¼»¯
	BEEP_Init();         	//³õÊ¼»¯·äÃùÆ÷¶Ë¿Ú
	 
	TIM3_Int_Init(29999,71999);//1KhzµÄ¼ÆÊıÆµÂÊ£¬¼ÆÊıµ½29999Îª30s


	KeyValue=17;
	led_output();//Êä³öledËæ»úÏÔÊ¾

	while(1)
	{

		OLED_ShowCHinese(0,0,0);//±È
		OLED_ShowCHinese(16,0,0);//±È
		OLED_ShowCHinese(32,0,1);//Ë­
		OLED_ShowCHinese(48,0,2);//µÄ 
		OLED_ShowCHinese(64,0,3);//·´
		OLED_ShowCHinese(80,0,4);//Ó¦
		OLED_ShowCHinese(96,0,5);//¿ì
		OLED_ShowCHinese(112,0,6);//¼
		
    if((KeyValue-1) == randomValue)
		{
		//·äÃùÆ÷Ïì
			for(i=0;i<20;i++)
			{
			BEEP = 0;
			delay_us(200);
			BEEP = 1;
			delay_us(200);			
			}
			BEEP_LED = 0;
			delay_ms(50);
			BEEP_LED = 1;
			score++;
			led_output();		
		}	
		delay_ms(50);

		
		OLED_ShowString(0,2,"score:",7);
		OLED_ShowNum(50,2,score,8,8);
		OLED_ShowString(0,4,"time:   30s",10);
		OLED_ShowString(0,6,"KEY: ",5);
		OLED_ShowNum(50,6,(KeyValue-1),8,8);
	
	}
 }

