/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	Tools.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <random>
#include <ctime>

class Tools
{
public:
	//��÷�Χ[min, max]�ڵ���������� --ע�⣺�ú�����ѭ��������ò��ܳ���10��
	static int getRandomInt(int min, int max);

	//��ȡ��ǰϵͳʱ��-�뼶��
	static time_t getCurrentTimeSecond();

	//��ȡ��ǰϵͳʱ��-�����յ�---ע�⣺�꣨tm_year = ��ǰ��� - 1900�����£�tm_mon[0~11]��
	static tm getCurrentTimeTm();

	//����һ���������Χ[1~5]���и������ĸ���Ϊ��,����0���ʾ�����ĸ��ʳ���(��Ӳ�����100)���磺��2(����[2~5]), 10��1�ĸ���10%���� 20�� 30�� 30�� 10����
	static int randomBetweenOneAndFive(int starNum, int onePercent, int twoPercent, int threePercent = 0, int fourPercent = 0, int fivePercent = 0);

	//������ת���ɰٷֱ�
	static float intToPercent(int x);

	//�Ѱٷֱ�ת��������
	static int percentToInt(float x);

	//bool����ת����int
	static bool intToBool(int i);

	//int����ת����bool
	//static int boolToInt(bool b);

	//����С�������λ(��������)
	static float keepTwoEffectNum(float f);

	//betweenAnd��1�� 2�� 3������1�Ƿ��ڷ�Χ��2�� 3��
	static bool betweenAnd(int p, int min, int max);

	//���鸳ֵ��length���鳤��,��src���桾0-length����ֵ��ֵ��des����)--ע��Խ������
	static void arrayAssignment(int length, int des[], int src[]);

	//�Ƚϴ�С
	static int maxInt(int a, int b);
	static int minInt(int a, int b);

private:
	Tools();

};

#endif // TOOLS_H_
