#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"//4x4¾ØÕó°´¼üÍâ²¿ÖĞ¶Ï
#include "oled.h"
#include "random_generate.h"//Éú³ÉËæ»úÊı
#include "beep.h" //·äÃùÆ÷Çı¶¯



 int main(void)
 {		
	extern int KeyValue;
	extern int randomValue;
	 
	delay_init();	    	 //ÑÓÊ±º¯Êı³õÊ¼»¯	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //ÉèÖÃNVICÖĞ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	uart_init(115200);	 //´®¿Ú²¨ÌØÂÊ115200
 	LED_Init();		  		 //³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼ş½Ó¿Ú
	OLED_Init();			   //³õÊ¼»¯OLED  
	OLED_Clear();  
	EXTIX_Init();		 	   //Íâ²¿ÖĞ¶Ï³õÊ¼»
	Adc_Init();          //adc³õÊ¼»¯
	BEEP_Init();         	//³õÊ¼»¯·äÃùÆ÷¶Ë¿Ú


	KeyValue=17;
	led_output();//Êä³öledËæ»úÏÔÊ¾
	 
//	OLED_ShowCHinese(0,0,0);//ÖĞ
//	OLED_ShowCHinese(18,0,1);//¾°
//	OLED_ShowCHinese(36,0,2);//Ô°
//	OLED_ShowCHinese(54,0,3);//µç
//	OLED_ShowCHinese(72,0,4);//×Ó
//	OLED_ShowCHinese(90,0,5);//¿Æ
//	OLED_ShowCHinese(108,0,6);//¼¼
	


	while(1)
	{
//	OLED_Clear();
//		OLED_ShowCHinese(0,0,0);//ÖĞ
//		OLED_ShowCHinese(18,0,1);//¾°
//		OLED_ShowCHinese(36,0,2);//Ô°
//		OLED_ShowCHinese(54,0,3);//µç 
//		OLED_ShowCHinese(72,0,4);//×Ó
//		OLED_ShowCHinese(90,0,5);//¿Æ
//		OLED_ShowCHinese(108,0,6);//¼¼
		
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

