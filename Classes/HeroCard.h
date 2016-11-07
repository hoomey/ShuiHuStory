/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	HeroCard.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/
 
#ifndef __HEROCARD_H__
#define __HEROCARD_H__

#include "TypeStruct.h"

class HeroCard{
public:
	HeroCard();
	~HeroCard();

	//����config�е�HeroVector����������Ӣ�ۿ���
	void init(const int index);

	//����ģ�������µ�Ӣ�ۿ��ƣ�����Ϊ��ʼӢ�ۿ��Ƶ�ģ��
	void init(const HeroCardType* heroCardType);

	//����Ӣ�ۿ��ƣ�����Ϊ�����Ӣ�ۿ�������
	void init(const SaveHeroCardData* saveHeroCardData);

	//���Ӣ�ۿ�����Ҫ���������
	const SaveHeroCardData getSaveData();

	//���Ӣ�ۿ�������
	const HeroCardProperty* getProperty();

	//����װ��(int pos(������λ�á�0~5��), int equipmentId��Ҫ���ϵ�װ��Id��);
	//0�������1��ñ�ӣ�2��Ь�ӣ�3���·���4�����5������
	void wearEquipment(int pos, int equipmentId);

	//ͨ��λ����š�0~5����ø�λ��װ����װ����Id
	int getEquipmentByPos(int pos);

	//���¿��Ƶ����ԣ�������������/ǿ�������ƻ�װ��ʱ����
	void updatetePropery();

private:
	//���㿨��Ӣ��ǿ���������ļӳ����Բ���������
	void calculateHeroCardPropery(const HeroCardType * heroCardType);

	//����Ӣ�ۿ��������װ���ӳ����Բ�����Ӣ�ۿ�������
	void calculateEquipmentPropery();

private:
	//Ӣ�ۿ��Ƶ�����������Ϣ
	HeroCardProperty* _property;
};

#endif // HEROCARD_H_