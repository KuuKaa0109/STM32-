#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
/*===========================================================
ʹ��ע�⣺
1.OLED_InitҪ����ʱ��ʼ��֮���ڵ��ã�����
2.Ϊ�˷�ֹ�����ܷɣ�OLED_Clear()��OLED_Display_On()��������Ҫ���ã���ѭ���⣩��OLED_Refresh_Gram()��ѭ�����棡������
===========================================================*/	  
extern u8 OLED_GRAM[128][8];	//OLED����  

#define macOLED_GPIO_PORT    	      GPIOE			              /* GPIO�˿� */
#define macOLED_GPIO_CLK 	          RCC_AHB1Periph_GPIOE		/* GPIO�˿�ʱ�� */
#define macOLED_GPIO_PIN		        GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9			        
 						  
//-----------------OLED�˿ڶ���----------------  					   
#define OLED_CS 	PEout(9)   //CS  Ƭѡ
#define OLED_RST  PEout(7)	//RES    �͵�ƽ��λ
#define OLED_RS 	PEout(8)   //DC  ����(1)������(0)���ƹܽ� 
//#define OLED_WR 	PGout(4)		//  
//#define OLED_RD 	PGout(7)	  //
 
//ʹ��4�ߴ��нӿ�ʱʹ�� 
#define OLED_SCLK 	PEout(5)  //D0
#define OLED_SDIN 	PEout(6)   //D1
		     
#define OLED_CMD  	0		//д����
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
#define OLED_DATA 	1		//д����
//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);                    //��ʾ�����ַ�
void OLED_ShowNum(u8 x,u8 y,int32_t num,u8 len,u8 size);                   //��ʾ����
void OLED_ShowNum_Left(u8 x,u8 y,int32_t num,u8 len,u8 size);
void OLED_ShowFloat(u8 x,u8 y,float num,u8 int_len,u8 dec_len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);	                      //��ʾ�ַ�����Ҫ��˫����
/*******************�Զ��庯��*****************************/


#endif  
	 



