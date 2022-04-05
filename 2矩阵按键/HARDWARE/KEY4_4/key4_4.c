/*
行  
		1		A11
		2		A12
		3		A15
		4		B13
列
		1		B4
		2		B5
		3		B6
		4		B7


*/


#include "key4_4.h"
#include "delay.h"
#include "sys.h"
//8个引脚 4个为行 4个为列
//行输出端口定义
#define X1_GPIO_PORT GPIOA           
#define X2_GPIO_PORT GPIOA   
#define X3_GPIO_PORT GPIOA           
#define X4_GPIO_PORT GPIOB 
//列输入端口定义
#define Y1_GPIO_PORT GPIOB           
#define Y2_GPIO_PORT GPIOB   
#define Y3_GPIO_PORT GPIOB           
#define Y4_GPIO_PORT GPIOB 

//行输出引脚定义
#define X1_GPIO_PIN GPIO_Pin_11
#define X2_GPIO_PIN GPIO_Pin_12
#define X3_GPIO_PIN GPIO_Pin_15
#define X4_GPIO_PIN GPIO_Pin_3

//列输入引脚定义
#define Y1_GPIO_PIN GPIO_Pin_4
#define Y2_GPIO_PIN GPIO_Pin_5
#define Y3_GPIO_PIN GPIO_Pin_6
#define Y4_GPIO_PIN GPIO_Pin_7

//行输出时钟定义
#define X1_RCC RCC_APB2Periph_GPIOA
#define X2_RCC RCC_APB2Periph_GPIOA
#define X3_RCC RCC_APB2Periph_GPIOA
#define X4_RCC RCC_APB2Periph_GPIOB

//列输入时钟定义
#define Y1_RCC RCC_APB2Periph_GPIOB
#define Y2_RCC RCC_APB2Periph_GPIOB
#define Y3_RCC RCC_APB2Periph_GPIOB
#define Y4_RCC RCC_APB2Periph_GPIOB

//移植代码只需要修改上面的端口和引脚和时钟即可，下面的代码不用修改。
//矩阵键盘所用的8个引脚可连续可不连续，看实际需要和个人爱好自己定义。

unsigned char Y1,Y2,Y3,Y4;
void Key_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;   
   RCC_APB2PeriphClockCmd(X1_RCC|X2_RCC|X3_RCC|X4_RCC|Y1_RCC|Y2_RCC|Y3_RCC|Y4_RCC|RCC_APB2Periph_AFIO, ENABLE);
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	
/*****************************4行输入*********************************************/
   GPIO_InitStructure.GPIO_Pin =  X1_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(X1_GPIO_PORT, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin =  X2_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(X2_GPIO_PORT, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin =  X3_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(X3_GPIO_PORT, &GPIO_InitStructure);
	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Pin = X4_GPIO_PIN ;    
   GPIO_Init(X4_GPIO_PORT, &GPIO_InitStructure);
   
/**************************************4列输入*************************************/
   GPIO_InitStructure.GPIO_Pin =  Y1_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(Y1_GPIO_PORT, &GPIO_InitStructure);	
   
   GPIO_InitStructure.GPIO_Pin =  Y2_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(Y2_GPIO_PORT, &GPIO_InitStructure);	
   
   GPIO_InitStructure.GPIO_Pin =  Y3_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(Y3_GPIO_PORT, &GPIO_InitStructure);	
	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Pin = Y4_GPIO_PIN;      
   GPIO_Init(Y4_GPIO_PORT, &GPIO_InitStructure);	
}

int Key_Scan(void)
{
   uchar KeyVal;
   GPIO_SetBits(X1_GPIO_PORT,X1_GPIO_PIN);  //先让X1输出高
   GPIO_SetBits(X2_GPIO_PORT,X2_GPIO_PIN);  //先让X2输出高
   GPIO_SetBits(X3_GPIO_PORT,X3_GPIO_PIN);  //先让X3输出高
   GPIO_SetBits(X4_GPIO_PORT,X4_GPIO_PIN);  //先让X4输出高


	if((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN)|GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN)|GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN)|GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))==0x0000)  
        return -1; //如果X1到X4全为零则没有按键按下  
	 else
	 {	
	    delay_ms(5);    //延时5ms去抖动
         if((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN)|GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN)|GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN)|GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))==0x0000)
	    return -1;
	 }
	 
     GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_SetBits(X4_GPIO_PORT,X4_GPIO_PIN); 
     
    Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
    Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=12;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=13;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=14;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=15;
    
     while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
    //等待按键释放
     GPIO_SetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);
   
    Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
    Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=0;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=1;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=2;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=3;
       
      while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
		

     GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_SetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);
        
     Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
     Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=4;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=5;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=6;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=7;
    
      while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
		
     GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_SetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);   

     Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
     Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=8;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=9;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=10;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=11;

       while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
	  
		return KeyVal;
}

/************************************
        按键表盘为：		
							1  2  3  A 
							4  5  6  B
							7  8  9  C
							*  0  #  D 
************************************/
/*

void Key_Test(void) 
{
    int num;
	  num = Key_Scan();
	  switch(num)
	  { 
        case 0: printf("0\n"); break;					  				      
				case 1: printf("1\n"); break;					  				       
				case 2: printf("2\n"); break;					  				     
				case 3: printf("3\n"); break;					  				     
				case 4: printf("4\n"); break;				 	       
				case 5: printf("5\n"); break;					  				      
				case 6: printf("6\n"); break;					  				      
				case 7: printf("7\n"); break;					 			       
				case 8: printf("8\n"); break;								 		       
				case 9: printf("9\n"); break;							 				     	
        case 'A': printf("A\n"); break;						 				      		
				case 'B': printf("B\n"); break;					 				      
				case 'C': printf("C\n"); break;							 				      	
        case 'D': printf("D\n"); break;							 				       	
				case '#': printf("#\n"); break;					 				      
				case '*': printf("*\n"); break;					 			      
      }
}


*/
