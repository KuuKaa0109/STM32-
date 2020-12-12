#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
/*===========================================================
使用注意：
1.OLED_Init要在延时初始化之后在调用！！！
2.为了防止程序跑飞，OLED_Clear()和OLED_Display_On()两个函数要调用（放循环外），OLED_Refresh_Gram()放循环里面！！！！
===========================================================*/	  
extern u8 OLED_GRAM[128][8];	//OLED缓存  

#define macOLED_GPIO_PORT    	      GPIOE			              /* GPIO端口 */
#define macOLED_GPIO_CLK 	          RCC_AHB1Periph_GPIOE		/* GPIO端口时钟 */
#define macOLED_GPIO_PIN		        GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9			        
 						  
//-----------------OLED端口定义----------------  					   
#define OLED_CS 	PEout(9)   //CS  片选
#define OLED_RST  PEout(7)	//RES    低电平复位
#define OLED_RS 	PEout(8)   //DC  数据(1)和命令(0)控制管脚 
//#define OLED_WR 	PGout(4)		//  
//#define OLED_RD 	PGout(7)	  //
 
//使用4线串行接口时使用 
#define OLED_SCLK 	PEout(5)  //D0
#define OLED_SDIN 	PEout(6)   //D1
		     
#define OLED_CMD  	0		//写命令
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
#define OLED_DATA 	1		//写数据
//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);                    //显示单个字符
void OLED_ShowNum(u8 x,u8 y,int32_t num,u8 len,u8 size);                   //显示数字
void OLED_ShowNum_Left(u8 x,u8 y,int32_t num,u8 len,u8 size);
void OLED_ShowFloat(u8 x,u8 y,float num,u8 int_len,u8 dec_len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);	                      //显示字符串，要用双引号
/*******************自定义函数*****************************/


#endif  
	 



