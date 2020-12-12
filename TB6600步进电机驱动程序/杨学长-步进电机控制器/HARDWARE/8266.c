#include "8266.h"
#include "delay.h"
#include "usart.h"

/******** AT指令 *********************/
unsigned char RST[8]="AT+RST\r\n";                                         //重启
unsigned char CWMODE[13]="AT+CWMODE=2\r\n";                                //1-Station模式， 2-AP模式， 3-AP兼Station模式
unsigned char AP[36]="AT+CWSAP=\"TEST\",\"123456123456\",1,3\r\n";         //配置AP参数（WiFi热点名称和密码）****设置后需重新启动模块！！！

/*********Server 方法收发************/
unsigned char CONNECT[13]="AT+CIPMUX=1\r\n";                               //0-单路连接模式， 1-多路连接模式
unsigned char FWQ[21]="AT+CIPSERVER=1,8080\r\n" ;                          //AT+CIPSERVER=1,8080 开启TCP服务端口***创建服务器
unsigned char TIME[16]="AT+CIPSTO=2880\r\n";                               //设置服务器超时时间
//unsigned char SENDDATE[16]="AT+CIPSEND=1,6\r\n";
/*
指令： 1)单路连接时(+CIPMUX=0)，指令为： AT+CIPSEND=<length>
2)多路连接时(+CIPMUX=1) ，指令为： AT+CIPSEND= <id>,<length>
响应： 收到此命令后先换行返回”>”，然后开始接收串口数据
当数据长度满 length 时发送数据。
如果未建立连接或连接被断开，返回 ERROR
如果数据发送成功，返回 SEND OK
说明： <id>:需要用于传输连接的 id 号
<length>:数字参数，表明发送数据的长度，最大长度为 2048
*/
//unsigned char D[14]="AT+CIPMODE=1\r\n";          //透传模式
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

