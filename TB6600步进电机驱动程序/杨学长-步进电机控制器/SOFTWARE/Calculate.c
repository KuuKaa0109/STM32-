#include "Calculate.h"

int Get_Speed(int Speed)              //�õ��ٶȶ�Ӧ������Ƶ��
{
	float  Speed_Num;                   //����Ƶ��
	Speed_Num=(Speed*6)/Angle_Bu;
	return (int)(Speed_Num) ;
}

int Get_Angle(int Angle)              //�õ��Ƕȶ�Ӧ��������
{
	float  Angle_Num;                   //������
	Angle_Num=Angle/Angle_Bu;
	return (int)(Angle_Num);
}
