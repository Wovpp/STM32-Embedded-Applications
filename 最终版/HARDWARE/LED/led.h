#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//LED0 C13
//LED1 C14
//LED2 C15
//LED3 A0								  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PCout(13)// PC13
#define LED1 PCout(14)// PC14
#define LED2 PCout(15)// PC15
#define LED3 PAout(0) // PA0


void LED_Init(void);//初始化
void led_output(void);//流水灯输出函数

		 				    
#endif
