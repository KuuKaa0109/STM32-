#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "OLED.h"
#include "8266.h"
#include "driver.h"
#include "Calculate.h"
#include "math.h"


int key;                                                   //�����ֵ
int i=0,j=0,x=0;
int Data=0;
int Speed_Num=0;                                            //�ٶ�����Ӧ��Ƶ��
int Angle_Num=0;                                            //�Ƕ�����Ӧ��������
int Speed=0;
int Angle=0;
int len;
//int Show_Speed;
//int SHow_Angle;
//���紮�����ַ���������ʾ��Ϣ
unsigned char SENDDATE[17]="AT+CIPSEND=0,46\r\n";
unsigned char SEND1[17]="�뷢�Ϳ��Ʋ���:\r\n";
unsigned char SEND2[29]="S+TargetSpeed\rA+TargetAngle\r\n";

int main(void)
{
	int flag=0;                                      //��־λ
	delay_init(168);
	uart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //����ϵͳ�ж����ȼ�����2
	TIM8_OPM_RCR_Init(999,168-1);                    //1MHz����Ƶ��  ������+�ظ�����ģʽ
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
//	OLED_ShowString(00,00,"Speed:",12);           //��ʾת��
//	
//	};
		
		
		
		
  while(1)
	{
    key=KEY_Scan(0);		                          //�õ���ֵ
		if(key==WKUP_PRES)                            //����K_UP��������ʾ��Ϣ�����±�־λ
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
		if(key==KEY0_PRES)                           //��¼��ͬ������״̬
			flag=2;
		if(key==KEY1_PRES)
			flag=3;

		
		if(flag==1)                                  //����K_UP��ִ��Զ�̿��ƺ���
		{
			if(USART_RX_STA&0x8000)
		 {					   
			len=USART_RX_STA&0x3fff;                  //�õ��˴ν��յ������ݳ���
      for(i=0;i<15;i++)                          //ȥ���ܵ�����Ϣǰ���ǰ׺
	  	{
		     if(USART_RX_BUF[i]==':')
		     j=i+1;
	    }
		  for(i=len-1;i>j;j--)                       //��ȡ����
		  {
		     Data+=USART_RX_BUF[i]*pow(10,x);
		     x++;
		  }
			x=0;
			USART_RX_STA=0;
			
		  if(USART_RX_BUF[j]=='S')                  //�ı�Ŀ���ٶ�ֵ
			{
		    Speed = Data;
				Speed_Num=Get_Speed(Speed);
			}
		  if(USART_RX_BUF[j]=='A')                  //�ı�Ŀ��Ƕ�ֵ
			{
		    Angle = Data;
        Angle_Num=Get_Angle(Angle);
			}
		}			
			Data=0;
			OLED_Refresh_Gram();
		  OLED_ShowString(00,00,"Speed:",12);           //��ʾת��
		  OLED_ShowNum(36,00,Speed,8,12);
		  OLED_ShowString(96,00,"r/min",12);
	  	OLED_ShowString(00,12,"Angle:",12);           //��ʾ�Ƕ�
		  OLED_ShowNum(36,12,Angle,8,12);
			
			if(Angle_Num!=0&&Speed_Num==0)
      {
			  Locate_Rle(Angle_Num,500,CW);            //���������500HZƵ����תAngle_Num������
				delay_ms(500);
			}		
      if(Speed_Num!=0&&Angle_Num==0) 
			{
			  Locate_Rle(100000,Speed_Num,CW);          //���������Speed_NUm��Ƶ����ת
			  delay_ms(500);
			}	
      if(Angle_Num!=0&&Speed_Num!=0)
      {
			  Locate_Rle(Angle_Num,Speed_Num,CW);     //���������Speed_NUm��Ƶ����תAngle_Num������
				delay_ms(500);
			}		
			
		}		
		
			
		if(flag==2)                                     //����K0��ִ���ٶȵ������ݼ���������
		{
			for(i=0;i<100;i++)                            //����
			{
				Speed=i;
			  Speed_Num=Get_Speed (Speed);
			  OLED_Refresh_Gram();
		    OLED_ShowString(00,00,"Speed:",12);           //��ʾת��
		    OLED_ShowNum(36,00,Speed,8,12);
		    OLED_ShowString(96,00,"r/min",12);
			  Locate_Rle(1000000,Speed_Num,CW);
			  delay_ms(1000);
			}
			if(i>=100)
			{
				for(;i>0;i--)                              //�ݼ�
				{
					Speed=i;
			    Speed_Num=Get_Speed (Speed);             //�õ��ٶȶ�Ӧ��Ƶ��
			    OLED_Refresh_Gram();
		      OLED_ShowString(00,00,"Speed:",12);           //��ʾת��
		      OLED_ShowNum(36,00,Speed,8,12);
		      OLED_ShowString(96,00,"r/min",12);
		    	Locate_Rle(1000000,Speed_Num,CW);        //�����������ת��
		    	delay_ms(1000);
				}	
		  }
		}
				
		if(flag==3)                                     //����K1��ִ�и������к���
		{
			if(USART_RX_STA&0x8000)		
      {
				
			   len=USART_RX_STA&0x3fff;                  //�õ��˴ν��յ������ݳ���
			}
      for(i=0;i<15;i++)                            //ȥ���ܵ�����Ϣǰ��ĺ�׺
	  	{
		     if(USART_RX_BUF[i]==':')
		     j=i+1;
	    }
		  for(i=len-1;i>j;j--)                         //��ȡ����
		  {
		     Data+=USART_RX_BUF[i]*pow(10,x);
		     x++;
		  }
			x=0;
			USART_RX_STA=0;
			if(USART_RX_BUF[j]=='A')                    //�ı�Ŀ��Ƕ�ֵ
			{
		    Angle = Data;
        Angle_Num=Get_Angle(Angle);
			}				
			Data=0;
			OLED_Refresh_Gram();
	  	OLED_ShowString(00,12,"Angle:",12);           //��ʾ�Ƕ�
		  OLED_ShowNum(36,12,Angle,8,12);
			Locate_Rle(Angle_Num,500,CW);                 //���������500HZ��Ƶ����תĿ��Ƕ�			
		}
  }
}


