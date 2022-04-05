#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"
#include "oled.h"
#include "random_generate.h"


 int main(void)
 {		
	extern int KeyValue;
	int randomValue;
	 
	delay_init();	    	 //—” ±∫Ø ˝≥ı ºªØ	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //…Ë÷√NVIC÷–∂œ∑÷◊È2:2Œª«¿’º”≈œ»º∂£¨2ŒªœÏ”¶”≈œ»º∂
	uart_init(115200);	 //¥Æø⁄≤®Ãÿ¬ 115200
 	LED_Init();		  		 //≥ı ºªØ”ÎLED¡¨Ω”µƒ”≤º˛Ω”ø⁄
	OLED_Init();			   //≥ı ºªØOLED  
	OLED_Clear();  
	EXTIX_Init();		 	   //Õ‚≤ø÷–∂œ≥ı ºª
	Adc_Init();          //adc≥ı ºªØ


	KeyValue=0;
	 
	 
	OLED_ShowCHinese(0,0,0);//÷–
	OLED_ShowCHinese(18,0,1);//æ∞
	OLED_ShowCHinese(36,0,2);//‘∞
	OLED_ShowCHinese(54,0,3);//µÁ
	OLED_ShowCHinese(72,0,4);//◊”
	OLED_ShowCHinese(90,0,5);//ø∆
	OLED_ShowCHinese(108,0,6);//ºº

	while(1)
	{
		randomValue=random();
//	OLED_Clear();
		OLED_ShowCHinese(0,0,0);//÷–
		OLED_ShowCHinese(18,0,1);//æ∞
		OLED_ShowCHinese(36,0,2);//‘∞
		OLED_ShowCHinese(54,0,3);//µÁ 
		OLED_ShowCHinese(72,0,4);//◊”
		OLED_ShowCHinese(90,0,5);//ø∆
		OLED_ShowCHinese(108,0,6);//ºº
		
		OLED_ShowNum(0,2,KeyValue,8,8);
		OLED_ShowNum(0,4,randomValue,8,8);

		
	}
 }

