#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include "TypeStruct.h"

class Equipment
{
public:
	Equipment();

	~Equipment();
	
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

	//����װ�����мӳ�֮������ԣ�����Ϊ��ʼװ����ģ��
	void calculatePropery(const EquipmentType* equipmentType);

private:
	//װ��������������Ϣ
	EquipmentProperty* _property;
};

#endif // EQUIPMENT_H_
