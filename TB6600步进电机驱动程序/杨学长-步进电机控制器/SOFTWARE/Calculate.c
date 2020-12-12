#include "Calculate.h"

int Get_Speed(int Speed)              //得到速度对应的脉冲频率
{
	float  Speed_Num;                   //脉冲频率
	Speed_Num=(Speed*6)/Angle_Bu;
	return (int)(Speed_Num) ;
}

int Get_Angle(int Angle)              //得到角度对应的脉冲数
{
	float  Angle_Num;                   //脉冲数
	Angle_Num=Angle/Angle_Bu;
	return (int)(Angle_Num);
}
