/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	TypeStruct.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __TYPESTRUCT_H__
#define __TYPESTRUCT_H__

#include "string"
#include "ConstantDefine.h"

using std::string;


//��������װ����Ϣ���ļ��Ľṹ��Ϊ�˷��㱣�棬���и����Ͷ���ת��Ϊ���ͱ���
struct SaveEquipmentData
{
	int id;				//Ψһ��ʶ��
	int type;			//��ʼ����ģ����
	int level;			//�ȼ�
	int exLevel;		//ǿ���ȼ�
	int user;			//ʹ����
	int rate;			//�����ģ������Ա��ʣ����磺1.2��ʾ��������Ϊģ�����Ե�1.2��
	int star;			//�Ǽ�
};

//װ�������Խṹ
struct EquipmentProperty
{
	int id;				//Ψһ��ʶ��
	int type;			//��ʼ����ģ����
	int level;			//�ȼ�
	int exLevel;		//ǿ���ȼ�
	int user;			//ʹ����
	float rate;			//�����ģ������Ա��ʣ����磺1.2��ʾ��������Ϊģ�����Ե�1.2��
	int star;			//�Ǽ�

	int defend;		//����
	int magicDefend;	//ħ������
	int ap;				//������
	int mp;				//ħ������
	int hp;				//����ֵ
	int speed;			//����ʱ�����ȼ���ֵԽ�����ȼ�Խ��
	float critRate;		//����
	float blockRate;		//��
	float critDamage;	//�����˺��ӳ�
	
	int buyMoney;		//����Ľ��
	int sellMoney;		//�����Ľ��

	const string * name;		//����
	const string * textureName;	//��������
	const string * des;			//����

};

//װ��ģ�����Խṹ
struct EquipmentType
{
	string name;		//����
	int type;			//��ʼ����ģ����
	int defend;		//����
	int magicDefend;	//ħ������
	int ap;				//������
	int mp;				//ħ������
	int hp;				//����ֵ
	int speed;			//����ʱ�����ȼ���ֵԽ�����ȼ�Խ��
	int star;			//�Ǽ�
	int critRate;		//����
	int blockRate;		//��
	int buyMoney;		//����Ľ��
	int sellMoney;		//�����Ľ��
	int critDamage;		//�����˺��ӳ�
	string textureName;	//��������
	string des;			//����
};

struct HeroCardType
{
	int type;				//����
	int star;				//Ʒ��
	int hp;					//���Ƶ�Ѫ
	int ap;					//����������
	int mp;					//����ħ������
	int defend;				//���Ƶ��������
	int magicDefend;		//���Ƶ�ħ������
	int attackId;			//��ͨ������ʽ
	int skillId;			//���ܹ�����ʽ
	int speed;				//�ٶ�
	int critRate;			//����
	int blockRate;			//��
	int critDamage;			//�����˺��ӳ�
	int buyMoney;			//����Ľ��
	int sellMoney;			//�����Ľ��
	bool isMagic;			//�Ƿ�ħ������

	string textureName;		//����
	string name;			//����
	string exName;			//����
	string starName;		//�Ǿ�����
	string skillName;		//��������
	string des;
};

//��������Ӣ����Ϣ���ļ��Ľṹ��Ϊ�˷��㱣�棬���и����Ͷ���ת��Ϊ���ͱ��档����1.2->120
struct SaveHeroCardData
{
	int id;				//Ψһ��ʶ��
	int type;			//��ʼ����ģ����
	int level;			//�ȼ�
	int exLevel;		//ǿ���ȼ�
	int rate;			//�����ģ������Ա��ʣ����磺120��ʾ��������Ϊģ�����Ե�1.2��
	int star;			//�Ǽ�
	
	//װ�����
	int equipmentId[max_equipment_num];	//-1��ʾû����������͵�װ��������1000��ʾװ��Id
};

struct HeroCardProperty
{
	int id;				//Ψһ��ʶ��
	int type;			//��ʼ����ģ����
	int level;			//�ȼ�
	int exLevel;		//ǿ���ȼ�
	float rate;			//�����ģ������Ա��ʣ����磺1.2��ʾ��������Ϊģ�����Ե�1.2��
	int star;			//Ʒ��/�Ǽ�

	const string* textureName;		//����
	const string* name;				//����
	const string* exName;			//����
	const string* starName;			//�Ǿ�����
	const string* skillName;		//��������
	const string* des;				//����

	int hp;					//���Ƶ�Ѫ
	int ap;					//����������
	int mp;					//����������
	int defend;				//���Ƶ��������
	int magicDefend;		//���Ƶ�ħ������
	int attackId;			//��ͨ������ʽ
	int skillId;			//���ܹ�����ʽ
	int speed;				//�ٶ�
	float critRate;			//����
	float blockRate;			//��
	float critDamage;		//�����˺��ӳ�
	int buyMoney;		//����Ľ��
	int sellMoney;		//�����Ľ��
	bool isMagic;			//�Ƿ�ħ������
	

	int equipmentId[max_equipment_num];	//-1��ʾû����������͵�װ��������1000��ʾװ��Id

};

struct EnemyType {
	int type;
	string textureName;
	string name;
	string exname;
	string starname;
	string skillsname;
	int hp;
	int ap;
	int attackId;
	int skillId;
	int level;
	int magic;
	string des;
	int defend;
	int magicDefend;
};


struct MapData
{
	int startData[6];
	string name;
	int coin;
	int exp;
	int type;
	int chalevel;
	int card;
	int sword;

	string cardName;
	string cardTexture;
	string equipmentName;
	string equipmentTexture;
};

#endif // TYPESTRUCT_H_
