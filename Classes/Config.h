/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	Config.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/10/20
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <vector>
#include "TypeStruct.h"

class Config{
public:
	~Config();

	static Config* getInstance();


	//ͨ��type��ȡHeroType
	const HeroCardType* getHeroCardByIndex(int type);

	//ͨ��type��ȡEquipmentType-����Ҫ����type<101>ת������Ӧ��������
	const EquipmentType* getEquipmentByIndex(int type);

private:
	Config();

	//����ģVector�����Ԫ��
	void destoryHeroVectorElement();
	void destoryEquipmentVectorElement();

	//��Json�ļ��ж�ȡӢ��ģ�������
	void readHeroJson(string fileName);

	//��Json�ļ��ж�ȡװ��ģ�������
	void readEquipmentJson(string fileName);

private:
	//����Ӣ��ģ��[0~108]
	std::vector<HeroCardType*> _heroCardVector;

	//����װ��ģ��
	std::vector<EquipmentType*> _equipmentVector;

	//����
	static Config* _config;
};

#endif // CONFIG_H_
