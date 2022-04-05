#include "key4_4.h"
#include "delay.h"
#include "sys.h"
#include "led.h"
//平台：STM32F103
//实验名称：不连续I/O矩阵键盘实验  
//Author:GXNU_LPK_20512700***
//使用说明：矩阵键盘所用引脚都已经用宏定义定义好了，移植只需根据实际需要在key4_4.c中修改对应的时钟、引脚和端口即可，其余都不用修改。
//矩阵键盘所用的8个引脚可连续可不连续，看实际需要和个人爱好自己定义。
int main(void)
{	
	 int num;
   uart_init(9600);             
   Key_Init();  				
   delay_init();				
	printf("不连续I/O口矩阵键盘测试\r\n");
    
	while(1)
	{			
    
	  num = Key_Scan();	
		if(num==0)
		LED0=1;
			
	}
}


