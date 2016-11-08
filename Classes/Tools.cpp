/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	Tools.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "Tools.h"


int Tools::getRandomInt(int min, int max)
{
	/************************************************************************/
	/*  ��Ϊ���ڵ��Ե�����������ǿ����ѭ������������ȡʱ��ʱ�����ȡ����ͬ��ʱ�䡣��Ϊ��  */
	/*	�������ӣ�ʱ�䣩��ͬ����ô�����������Ҳ����ͬ��Ϊ�˱�����ѭ�����ȡʱ�����Ϊ��	*/
	/*	�ϻ�ȡ���ܴ����������ȿɱ��������ͬ��ʱ�����ӡ�	*/
	/************************************************************************/
	static unsigned randomCount = 0;

	time_t currentTimer = getCurrentTimeSecond();

	//��Ϊ���ϻ�ȡ�Ĵ��������������ͬ��ʱ��
	currentTimer += randomCount;
	++randomCount;

	std::default_random_engine e(currentTimer);

	std::uniform_int_distribution<unsigned> u(min, max);

	return u(e);
}

tm Tools::getCurrentTimeTm()
{
	time_t timer = getCurrentTimeSecond();
	tm *tmTemp = localtime(&timer);

	return *tmTemp;
}

float Tools::intToPercent(int x)
{
	return x / 100.0f;
}

int Tools::percentToInt(float x)
{
	return static_cast<int>(x * 100);
}

bool Tools::intToBool(int i)
{
	return (i != 0);
}

float Tools::keepTwoEffectNum(float f)
{
	int temp = static_cast<int>(f * 1000);
	int last = temp % 10;
	
	if(last >4)
	{
		f = (temp + 10 - last) / 1000.0f;
	}
	else
	{
		f = (temp - last) / 1000.0f;
	}
	return f;
}

bool Tools::betweenAnd(int p, int min, int max)
{
	bool result = true;

	if (p < min || p > max)
	{
		result = false;
	}

	return result;
}

void Tools::arrayAssignment(int length, int des[], int src[])
{
	for (int index = 0; index < length; ++index)
	{
		des[index] = src[index];
	}
}

int Tools::randomBetweenOneAndFive(int starNum, int onePercent, int twoPercent, int threePercent, int fourPercent, int fivePercent)
{
	int result = 0;

	starNum = maxInt(minInt(starNum, 5), 1);

	if (onePercent + twoPercent + threePercent + fourPercent + fivePercent == 100)
	{
		int rd = getRandomInt(1, 100);

		if (rd < onePercent)
		{
			result = starNum;
		}
		else if (rd < twoPercent + onePercent)
		{
			result = starNum + 1;
		}
		else if (rd < threePercent + twoPercent + onePercent)
		{
			result = starNum + 2;
		}
		else if (rd < fourPercent + threePercent + twoPercent + onePercent)
		{
			result = starNum + 3;
		}
		else
		{
			result = starNum + 4;
		}
	}

	return result;
}

time_t Tools::getCurrentTimeSecond()
{
	return (time_t)time(NULL);
}

int Tools::maxInt(int a, int b)
{
	return (a > b ? a : b);
}

int Tools::minInt(int a, int b)
{
	return (a > b ? b : a);
}
