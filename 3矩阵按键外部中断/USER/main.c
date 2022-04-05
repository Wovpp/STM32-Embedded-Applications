#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"


 int main(void)
 {		
	extern 	int KeyValue;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口波特率115200
 	LED_Init();		  		//初始化与LED连接的硬件接口
	 

	EXTIX_Init();		 	//外部中断初始化

//	LED0=0;					//点亮LED0
	 KeyValue=0;

	while(1)
	{	   
		if(KeyValue == 11)
		LED0=0;	

		
	}
 }

