#include "key4_4.h"
#include "delay.h"
#include "sys.h"
#include "led.h"
//ƽ̨��STM32F103
//ʵ�����ƣ�������I/O�������ʵ��  
//Author:GXNU_LPK_20512700***
//ʹ��˵������������������Ŷ��Ѿ��ú궨�嶨����ˣ���ֲֻ�����ʵ����Ҫ��key4_4.c���޸Ķ�Ӧ��ʱ�ӡ����źͶ˿ڼ��ɣ����඼�����޸ġ�
//����������õ�8�����ſ������ɲ���������ʵ����Ҫ�͸��˰����Լ����塣
int main(void)
{	
	 int num=0;
   uart_init(9600);             
   Key_Init();  				
   delay_init();	
	 LED_Init();	
	 printf("������I/O�ھ�����̲���\r\n");
    
	while(1)
	{			
		Key_Scan();
	  num = Key_Scan()+1;	
		if(num!=0)
		LED0=0;
		delay_ms(1000);
		LED0=1;

			
	}
}


