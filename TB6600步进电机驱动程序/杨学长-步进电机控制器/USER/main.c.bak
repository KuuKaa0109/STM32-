#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "OLED.h"
#include "8266.h"
#include "driver.h"
#include "Calculate.h"
#include "math.h"


int key;                                                   //保存键值
int i=0,j=0,x=0;
int Data=0;
int Speed_Num=0;                                            //速度所对应的频率
int Angle_Num=0;                                            //角度所对应的脉冲数
int Speed=0;
int Angle=0;
int len;
//int Show_Speed;
//int SHow_Angle;
//网络串口助手发送数据提示信息
unsigned char SENDDATE[17]="AT+CIPSEND=0,46\r\n";
unsigned char SEND1[17]="请发送控制参数:\r\n";
unsigned char SEND2[29]="S+TargetSpeed\rA+TargetAngle\r\n";

int main(void)
{
	int flag=0;                                      //标志位
	delay_init(168);
	uart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置系统中断优先级分组2
	TIM8_OPM_RCR_Init(999,168-1);                    //1MHz计数频率  单脉冲+重复计数模式
	Driver_Init();
	OLED_Init();
  OLED_Clear();
	KEY_Init();
	OLED_Display_On(); 
	wifi_init();
	Locate_Rle(1600,500,CW);
//	while(1){
//		
//		OLED_Refresh_Gram();
//	OLED_ShowString(00,00,"Speed:",12);           //显示转速
//	
//	};
		
		
		
		
  while(1)
	{
    key=KEY_Scan(0);		                          //得到键值
		if(key==WKUP_PRES)                            //按下K_UP键发送提示信息并更新标志位
		{
			flag=1;
			for(i=0;i<17;i++)
			{
				USART_SendData(USART1, SENDDATE[i]);
		    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	    }
	    delay_ms(500);
		  for(i=0;i<17;i++)
			{
				USART_SendData(USART1, SEND1[i]);
		    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	    }
			for(i=0;i<29;i++)
			{
				USART_SendData(USART1, SEND2[i]);
		    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	    }
		}
		if(key==KEY0_PRES)                           //记录不同按键的状态
			flag=2;
		if(key==KEY1_PRES)
			flag=3;

		
		if(flag==1)                                  //按下K_UP键执行远程控制函数
		{
			if(USART_RX_STA&0x8000)
		 {					   
			len=USART_RX_STA&0x3fff;                  //得到此次接收到的数据长度
      for(i=0;i<15;i++)                          //去除受到的信息前面的前缀
	  	{
		     if(USART_RX_BUF[i]==':')
		     j=i+1;
	    }
		  for(i=len-1;i>j;j--)                       //提取数字
		  {
		     Data+=USART_RX_BUF[i]*pow(10,x);
		     x++;
		  }
			x=0;
			USART_RX_STA=0;
			
		  if(USART_RX_BUF[j]=='S')                  //改变目标速度值
			{
		    Speed = Data;
				Speed_Num=Get_Speed(Speed);
			}
		  if(USART_RX_BUF[j]=='A')                  //改变目标角度值
			{
		    Angle = Data;
        Angle_Num=Get_Angle(Angle);
			}
		}			
			Data=0;
			OLED_Refresh_Gram();
		  OLED_ShowString(00,00,"Speed:",12);           //显示转速
		  OLED_ShowNum(36,00,Speed,8,12);
		  OLED_ShowString(96,00,"r/min",12);
	  	OLED_ShowString(00,12,"Angle:",12);           //显示角度
		  OLED_ShowNum(36,12,Angle,8,12);
			
			if(Angle_Num!=0&&Speed_Num==0)
      {
			  Locate_Rle(Angle_Num,500,CW);            //步进电机以500HZ频率正转Angle_Num个脉冲
				delay_ms(500);
			}		
      if(Speed_Num!=0&&Angle_Num==0) 
			{
			  Locate_Rle(100000,Speed_Num,CW);          //步进电机以Speed_NUm的频率正转
			  delay_ms(500);
			}	
      if(Angle_Num!=0&&Speed_Num!=0)
      {
			  Locate_Rle(Angle_Num,Speed_Num,CW);     //步进电机以Speed_NUm的频率正转Angle_Num个脉冲
				delay_ms(500);
			}		
			
		}		
		
			
		if(flag==2)                                     //按下K0键执行速度递增、递减函数函数
		{
			for(i=0;i<100;i++)                            //递增
			{
				Speed=i;
			  Speed_Num=Get_Speed (Speed);
			  OLED_Refresh_Gram();
		    OLED_ShowString(00,00,"Speed:",12);           //显示转速
		    OLED_ShowNum(36,00,Speed,8,12);
		    OLED_ShowString(96,00,"r/min",12);
			  Locate_Rle(1000000,Speed_Num,CW);
			  delay_ms(1000);
			}
			if(i>=100)
			{
				for(;i>0;i--)                              //递减
				{
					Speed=i;
			    Speed_Num=Get_Speed (Speed);             //得到速度对应的频率
			    OLED_Refresh_Gram();
		      OLED_ShowString(00,00,"Speed:",12);           //显示转速
		      OLED_ShowNum(36,00,Speed,8,12);
		      OLED_ShowString(96,00,"r/min",12);
		    	Locate_Rle(1000000,Speed_Num,CW);        //调整步进电机转速
		    	delay_ms(1000);
				}	
		  }
		}
				
		if(flag==3)                                     //按下K1键执行负重运行函数
		{
			if(USART_RX_STA&0x8000)		
      {
				
			   len=USART_RX_STA&0x3fff;                  //得到此次接收到的数据长度
			}
      for(i=0;i<15;i++)                            //去除受到的信息前面的后缀
	  	{
		     if(USART_RX_BUF[i]==':')
		     j=i+1;
	    }
		  for(i=len-1;i>j;j--)                         //提取数字
		  {
		     Data+=USART_RX_BUF[i]*pow(10,x);
		     x++;
		  }
			x=0;
			USART_RX_STA=0;
			if(USART_RX_BUF[j]=='A')                    //改变目标角度值
			{
		    Angle = Data;
        Angle_Num=Get_Angle(Angle);
			}				
			Data=0;
			OLED_Refresh_Gram();
	  	OLED_ShowString(00,12,"Angle:",12);           //显示角度
		  OLED_ShowNum(36,12,Angle,8,12);
			Locate_Rle(Angle_Num,500,CW);                 //步进电机以500HZ的频率正转目标角度			
		}
  }
}


