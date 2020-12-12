#include "8266.h"
#include "delay.h"
#include "usart.h"

/******** ATָ�� *********************/
unsigned char RST[8]="AT+RST\r\n";                                         //����
unsigned char CWMODE[13]="AT+CWMODE=2\r\n";                                //1-Stationģʽ�� 2-APģʽ�� 3-AP��Stationģʽ
unsigned char AP[36]="AT+CWSAP=\"TEST\",\"123456123456\",1,3\r\n";         //����AP������WiFi�ȵ����ƺ����룩****���ú�����������ģ�飡����

/*********Server �����շ�************/
unsigned char CONNECT[13]="AT+CIPMUX=1\r\n";                               //0-��·����ģʽ�� 1-��·����ģʽ
unsigned char FWQ[21]="AT+CIPSERVER=1,8080\r\n" ;                          //AT+CIPSERVER=1,8080 ����TCP����˿�***����������
unsigned char TIME[16]="AT+CIPSTO=2880\r\n";                               //���÷�������ʱʱ��
//unsigned char SENDDATE[16]="AT+CIPSEND=1,6\r\n";
/*
ָ� 1)��·����ʱ(+CIPMUX=0)��ָ��Ϊ�� AT+CIPSEND=<length>
2)��·����ʱ(+CIPMUX=1) ��ָ��Ϊ�� AT+CIPSEND= <id>,<length>
��Ӧ�� �յ���������Ȼ��з��ء�>����Ȼ��ʼ���մ�������
�����ݳ����� length ʱ�������ݡ�
���δ�������ӻ����ӱ��Ͽ������� ERROR
������ݷ��ͳɹ������� SEND OK
˵���� <id>:��Ҫ���ڴ������ӵ� id ��
<length>:���ֲ����������������ݵĳ��ȣ���󳤶�Ϊ 2048
*/
//unsigned char D[14]="AT+CIPMODE=1\r\n";          //͸��ģʽ
//unsigned char E[12]="AT+CIPSEND\r\n";

void wifi_init()
{
	u8 i=0;
	delay_ms(1000);
//	for(i=0;i<8;i++)
//	{
//		USART_SendData(USART1, RST[i]);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
//	}	
//	delay_ms(500);
	
//	for(i=0;i<13;i++)
//	{
//		USART_SendData(USART1, CWMODE[i]);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
//	}
//	delay_ms(500); 
	
//	for(i=0;i<36;i++)
//	{
//		USART_SendData(USART1, AP[i]);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
//	}
//	delay_ms(500);

	for(i=0;i<13;i++)
	{
		USART_SendData(USART1, CONNECT[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}
	delay_ms(500);
	
	for(i=0;i<21;i++)
	{
		USART_SendData(USART1, FWQ[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}
	delay_ms(500);	
	
	for(i=0;i<16;i++)
	{
		USART_SendData(USART1, TIME[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}
	delay_ms(500);
	
//	for(i=0;i<17;i++)
//	{
//		USART_SendData(USART1, SENDDATE[i]);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
//	}
//	delay_ms(500);
	
}

