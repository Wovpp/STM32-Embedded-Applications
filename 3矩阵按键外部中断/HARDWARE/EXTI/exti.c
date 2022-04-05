#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"

int KeyValue;

//行：A1 A2 A3 A4
//列：B4 B5 B6 B7
//行设为外部中断


//////////////////////////////////////////////////////////define
//8个引脚 4个为行 4个为列
//行输出端口定义
#define X1_GPIO_PORT GPIOA           
#define X2_GPIO_PORT GPIOA   
#define X3_GPIO_PORT GPIOA           
#define X4_GPIO_PORT GPIOA 
//列输入端口定义
#define Y1_GPIO_PORT GPIOB           
#define Y2_GPIO_PORT GPIOB   
#define Y3_GPIO_PORT GPIOB           
#define Y4_GPIO_PORT GPIOB 

//行输出引脚定义
#define X1_GPIO_PIN GPIO_Pin_1
#define X2_GPIO_PIN GPIO_Pin_2
#define X3_GPIO_PIN GPIO_Pin_3
#define X4_GPIO_PIN GPIO_Pin_4

//列输入引脚定义
#define Y1_GPIO_PIN GPIO_Pin_4
#define Y2_GPIO_PIN GPIO_Pin_5
#define Y3_GPIO_PIN GPIO_Pin_6
#define Y4_GPIO_PIN GPIO_Pin_7

//行输出时钟定义
#define X1_RCC RCC_APB2Periph_GPIOA
#define X2_RCC RCC_APB2Periph_GPIOA
#define X3_RCC RCC_APB2Periph_GPIOA
#define X4_RCC RCC_APB2Periph_GPIOA

//列输入时钟定义
#define Y1_RCC RCC_APB2Periph_GPIOB
#define Y2_RCC RCC_APB2Periph_GPIOB
#define Y3_RCC RCC_APB2Periph_GPIOB
#define Y4_RCC RCC_APB2Periph_GPIOB

//移植代码只需要修改上面的端口和引脚和时钟即可，下面的代码不用修改。
//矩阵键盘所用的8个引脚可连续可不连续，看实际需要和个人爱好自己定义。

////////////////////////////////////////////////////////////////////////////////////////



void Matrix_KEY_Init(void)
{ 
	 GPIO_InitTypeDef GPIO_InitStructure;   
   RCC_APB2PeriphClockCmd(X1_RCC|X2_RCC|X3_RCC|X4_RCC|Y1_RCC|Y2_RCC|Y3_RCC|Y4_RCC|RCC_APB2Periph_AFIO, ENABLE);
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	
/**************************************4行状态 上拉输入***********************************/
   GPIO_InitStructure.GPIO_Pin   =  X1_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IPU;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(X1_GPIO_PORT, &GPIO_InitStructure);	
   
   GPIO_InitStructure.GPIO_Pin   =  X2_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IPU;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(X2_GPIO_PORT, &GPIO_InitStructure);	
   
   GPIO_InitStructure.GPIO_Pin   =  X3_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IPU;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(X3_GPIO_PORT, &GPIO_InitStructure);	
	
	 GPIO_InitStructure.GPIO_Pin   =  X4_GPIO_PIN;   
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IPU;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(X4_GPIO_PORT, &GPIO_InitStructure);		
	
	
	
/*****************************4列状态 推挽输出*********************************************/
   GPIO_InitStructure.GPIO_Pin   =  Y1_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(Y1_GPIO_PORT, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin   =  Y2_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(Y2_GPIO_PORT, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin   =  Y3_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
   GPIO_Init(Y3_GPIO_PORT, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin   =  Y4_GPIO_PIN ; 
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz; 
   GPIO_Init(Y4_GPIO_PORT, &GPIO_InitStructure);
   

	 
//	 列置低
	 	GPIO_ResetBits (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits (Y4_GPIO_PORT,Y4_GPIO_PIN);
		
		GPIO_SetBits   (X1_GPIO_PORT,X1_GPIO_PIN);
		GPIO_SetBits   (X2_GPIO_PORT,X2_GPIO_PIN);
		GPIO_SetBits   (X3_GPIO_PORT,X3_GPIO_PIN);
		GPIO_SetBits   (X4_GPIO_PORT,X4_GPIO_PIN);
}


//外部中断关闭函数
void EXTI_disable(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 | EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);
}


//外部中断开启函数
void EXTI_enable(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 | EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}


//外部中断初始化
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;

	  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
		Matrix_KEY_Init();	 //	按键端口初始化

    //GPIOA.1 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOA.2	  中断线以及中断初始化配置 上升沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOA.3  中断线以及中断初始化配置  上升沿触发	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOA.4	  中断线以及中断初始化配置  上升沿触发	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器



  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

}

//外部中断1服务程序    进入第一行中断
void EXTI1_IRQHandler(void)
{
	delay_ms(50);
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)	 	 
	{	
		EXTI_disable();
		
		//行置高,扫描列		
		GPIO_SetBits (X1_GPIO_PORT,X1_GPIO_PIN);
		
		//第一列按下
		GPIO_ResetBits  (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )); //等待按键松开
				KeyValue = 1;				
			}
			
		//第二列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits  (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )); //等待按键松开
				KeyValue = 2;				
			}

		//第三列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits  (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )); //等待按键松开
				KeyValue = 3;				
			}

		//第四列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits  (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X1_GPIO_PORT, X1_GPIO_PIN )); //等待按键松开
				KeyValue = 4;				
			}
			
		GPIO_ResetBits (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits (Y4_GPIO_PORT,Y4_GPIO_PIN);
			
		GPIO_SetBits   (X1_GPIO_PORT,X1_GPIO_PIN);
		GPIO_SetBits   (X2_GPIO_PORT,X2_GPIO_PIN);
		GPIO_SetBits   (X3_GPIO_PORT,X3_GPIO_PIN);
		GPIO_SetBits   (X4_GPIO_PORT,X4_GPIO_PIN);
			
		EXTI_enable();                      //外部中断使能
		EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE1上的中断标志位  
	}

}

//外部中断2服务程序     进入第二行中断
void EXTI2_IRQHandler(void)
{
	delay_ms(50);
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)	 	 
	{	
		EXTI_disable();
		
		//行置高,扫描列		
		GPIO_SetBits (X2_GPIO_PORT,X2_GPIO_PIN);
		
		//第一列按下
		GPIO_ResetBits  (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )); //等待按键松开
				KeyValue = 5;				
			}
			
		//第二列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits  (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )); //等待按键松开
				KeyValue = 6;				
			}

		//第三列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits  (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )); //等待按键松开
				KeyValue = 7;				
			}

		//第四列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits  (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X2_GPIO_PORT, X2_GPIO_PIN )); //等待按键松开
				KeyValue = 8;				
			}
			
		GPIO_ResetBits (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits (Y4_GPIO_PORT,Y4_GPIO_PIN);
			
		GPIO_SetBits   (X1_GPIO_PORT,X1_GPIO_PIN);
		GPIO_SetBits   (X2_GPIO_PORT,X2_GPIO_PIN);
		GPIO_SetBits   (X3_GPIO_PORT,X3_GPIO_PIN);
		GPIO_SetBits   (X4_GPIO_PORT,X4_GPIO_PIN);
			
		EXTI_enable();                      //外部中断使能
		EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE2上的中断标志位  
	}
}


//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(50);
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)	 	 
	{	
		EXTI_disable();
		
		//行置高,扫描列		
		GPIO_SetBits (X3_GPIO_PORT,X3_GPIO_PIN);
		
		//第一列按下
		GPIO_ResetBits  (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )); //等待按键松开
				KeyValue = 9;				
			}
			
		//第二列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits  (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )); //等待按键松开
				KeyValue = 10;				
			}

		//第三列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits  (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )); //等待按键松开
				KeyValue = 11;				
			}

		//第四列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits  (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X3_GPIO_PORT, X3_GPIO_PIN )); //等待按键松开
				KeyValue = 12;				
			}
			
		GPIO_ResetBits (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits (Y4_GPIO_PORT,Y4_GPIO_PIN);
			
		GPIO_SetBits   (X1_GPIO_PORT,X1_GPIO_PIN);
		GPIO_SetBits   (X2_GPIO_PORT,X2_GPIO_PIN);
		GPIO_SetBits   (X3_GPIO_PORT,X3_GPIO_PIN);
		GPIO_SetBits   (X4_GPIO_PORT,X4_GPIO_PIN);
			
		EXTI_enable();                      //外部中断使能
		EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE2上的中断标志位  
	}
}

//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	delay_ms(50);
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)	 	 
	{	
		EXTI_disable();
		
		//行置高,扫描列		
		GPIO_SetBits (X4_GPIO_PORT,X4_GPIO_PIN);
		
		//第一列按下
		GPIO_ResetBits  (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )); //等待按键松开
				KeyValue = 13;				
			}
			
		//第二列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits  (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )); //等待按键松开
				KeyValue = 14;				
			}

		//第三列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits  (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_SetBits    (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )); //等待按键松开
				KeyValue = 15;				
			}

		//第四列按下
		GPIO_SetBits    (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_SetBits    (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_SetBits    (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits  (Y4_GPIO_PORT,Y4_GPIO_PIN);	
		
			if(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )==0)
			{
				while(GPIO_ReadInputDataBit ( X4_GPIO_PORT, X4_GPIO_PIN )); //等待按键松开
				KeyValue = 16;				
			}
			
		GPIO_ResetBits (Y1_GPIO_PORT,Y1_GPIO_PIN);
		GPIO_ResetBits (Y2_GPIO_PORT,Y2_GPIO_PIN);
		GPIO_ResetBits (Y3_GPIO_PORT,Y3_GPIO_PIN);
		GPIO_ResetBits (Y4_GPIO_PORT,Y4_GPIO_PIN);
			
		GPIO_SetBits   (X1_GPIO_PORT,X1_GPIO_PIN);
		GPIO_SetBits   (X2_GPIO_PORT,X2_GPIO_PIN);
		GPIO_SetBits   (X3_GPIO_PORT,X3_GPIO_PIN);
		GPIO_SetBits   (X4_GPIO_PORT,X4_GPIO_PIN);
			
		EXTI_enable();                      //外部中断使能
		EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE2上的中断标志位  
	}
}
 
