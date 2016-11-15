/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	GameData.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/10/20
// Contact: 	caiufen@qq.com
// Description:		create by vs2015pro
*************************************************/


#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include <unordered_map>
#include "ConstantDefine.h"

class Equipment;
class HeroCard;

class GameData{
public:
	~GameData();

	//���ʵ��
	static GameData* getInstance();
	
	static bool isNullptr();

	//��������
	void readData();

	//�ͷż��ص�����
	void saveData();

	//�����û����ݣ���ң���ʯ������ ,�ȼ���������óɹ�����true��ʧ���򷵻�false��
	bool setGold(const int gold);
	bool setDiamond(const int diamond);
	//�����ɫ�ﵽ���ȼ��򷵻�false
	bool setExp(const int exp);
	
	//����û����ݷ���
	int getGold();
	int getDiamond();
	int getExp();
	int getLevel();

	//��ü���level��������Ҫ�ľ���ֵ��X�Ǳ���ϵ��
	int getExpLimit(float x, int level);

	//�����û����� ��ң���ʯ������ ,�ȼ�
	void saveUserData();
	
	//��ȡ�û����� ��ң���ʯ������ ,�ȼ�
	void readUserData();
 
	//����ʵ��
	void destoryInstance();

	//��ȡΨһ�ı�ʶ��
	int getUniqueIdentifierNum();

	//���浱ǰ�Ѿ�ʹ�õ��ı�ʶ��
	void saveUniqueIdentifierNumToFile();

	//��ȡ�ļ��еı�ʶ��
	void readUniqueIdentifierNumFromFile();

	//��ȡ��սӢ��
	void readBattleHero();

	//�����սӢ��
	void saveBattleHero();

	//��ָ���ļ��л���ѻ�õ�װ������
	void readEquipmentFromJson(std::string fileName);

	//��ָ���ļ��л���ѻ�õ�Ӣ������
	void readHeroCardFromJson(std::string fileName);

	//���ѻ�õ�װ������дָ���ļ����ļ�
	void saveEquipmentToFile(std::string fileName);

	//���ѻ��Ӣ�ۿ�������д��ָ���ļ�
	void saveHeroCardToFile(std::string fileName);

	//�����ѻ��װ�����Ƕ�saveEquipmentToFile�Ľ�һ����װ
	void saveEquipment();

	//�����ѻ��װ�����Ƕ�saveHeroCardToFile�Ľ�һ����װ
	void saveHeroCard();
	
	//��ȡ�ѻ�õ�װ���� �Ƕ�readEquipmentFromJson�Ľ�һ����װ
	void readEquipment();

	//��ȡ�ѻ��Ӣ�ۿ��ƣ� �Ƕ�readHeroCardFromJson�Ľ�һ����װ
	void readHeroCard();

	//��ӵ�һ��Ԫ�ص�_quipmentMap
	void addEquipmentToMap(Equipment* equipment);
	
	//���һ��Ԫ����_heroCardMap
	void addHeroCardToMap(HeroCard* heroCard);

	//ͨ��idɾ����������б���Ӣ�ۿ���
	void deleteHeroCardById(int id);

	//ͨ��id��������б��е�ɾ��װ��
	void deleteEquipmentById(int id);

	//ͨ��Id��ȡ�Ѿ���õ�װ��
	Equipment* getEquipmentById(int id);

	//ͨ��Id��ȡ�Ѿ���õ�Ӣ�ۿ���
	HeroCard* getHeroCardById(int id);

	//��ȡ��Ӧλ�õĳ�սӢ��id
	int getBattleHeroId(int pos);

	//��ó�սӢ������
	int* getBattleHeroArray();

	//���Ӣ���Ѿ����������󣬷���true�����򷵻�false
	bool unbattleHero(int id);

	//�ж�id�Ƿ��ս
	bool isBattleHero(int id);

	//��������Ӣ�۵ĸ���
	int getBattleHeroNum();

	void setBattleHero(int pos, int id);

	//���װ������
	const std::unordered_map<int, Equipment*>* getEquipmentMap();

	//���Ӣ�ۿ�������
	const std::unordered_map<int, HeroCard*>* getHeroCardMap();

private:
	GameData();

	//����_equipmentMap�����Ԫ��
	void destoryEquipmentMapElement();
	
	//����_heroCardMap�����Ԫ��
	void destoryHeroMapElement();

private:
	//�û�����
	int _gold;
	int _diamond;
	int _level;
	int _exp;

	//�����սӢ��
	int _battleHero[max_battle_hero_num];

	//�����ѻ�õ�װ��
	std::unordered_map<int, Equipment*> _equipmentMap;

	//�����ѻ�õ�Ӣ�ۿ���
	std::unordered_map<int, HeroCard*> _heroCardMap;

	int _uniqueIdentifierNum;	//��¼��ƷΨһ�ı�ʶ��

	//����
	static GameData* _gameData;
};

#endif // GAMEDATA_H_
