#include "led.h"
#include "random_generate.h"//生成随机数

//LED0 C13
//LED1 C14
//LED2 C15
//LED3 A0



//初始化为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE);	 //使能PC端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PC.13 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.13
 GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PC.13 输出高
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				 //LED0-->PC.14 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.14
 GPIO_SetBits(GPIOC,GPIO_Pin_14);						 //PC.14 输出高
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //LED0-->PC.15 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.15
 GPIO_SetBits(GPIOC,GPIO_Pin_15);						 //PC.15 输出高


 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //LED0-->PA.0 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.0
 GPIO_SetBits(GPIOA,GPIO_Pin_0);						 //PC.15 输出高

}


void led_output(void)  //流水灯输出函数
{
		int randomValue;	
		randomValue=random();
		LED0=~(randomValue&0x01);
	  LED1=~((randomValue>>1)&0x01);
	  LED2=~((randomValue>>2)&0x01);
	  LED3=~((randomValue>>3)&0x01);
	

}
 
