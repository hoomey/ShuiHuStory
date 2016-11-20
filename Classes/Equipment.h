/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	Equipment.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include "TypeStruct.h"

class Equipment
{
public:
	Equipment();

	~Equipment();
	
	void setUserId(int id);

	//����config�е�EquipmentVector����������װ��
	void init(const int index);

	//����ģ�������µ�װ��������Ϊ��ʼװ����ģ��
	void init(const EquipmentType* equipmentType);

	//�������е�װ��ģ������װ��������Ϊ�����װ������
	void init(const SaveEquipmentData* saveEquipmentData);

	//���װ����Ҫ���������
	const SaveEquipmentData getSaveData();

	//���װ������
	const EquipmentProperty* getProperty();

	//������ǿ��װ��
	void levelup();
	void intensify();

	//����װ�����мӳ�֮������ԣ�����Ϊ��ʼװ����ģ��
	void calculatePropery(const EquipmentType* equipmentType);

private:
	//װ��������������Ϣ
	EquipmentProperty* _property;
};

#endif // EQUIPMENT_H_
