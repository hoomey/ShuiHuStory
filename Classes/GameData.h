/*
*�����࣬��Ҫ���������Ϸ��ص����ݣ����磬��ҡ�Ԫ���ȵ�
*/

#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include <unordered_map>

class Equipment;
class HeroCard;

class GameData{
public:
	~GameData();

	//���ʵ��
	static GameData* getInstance();
	
	//����ʵ��
	void destoryInstance();

	//��ȡΨһ�ı�ʶ��
	int getUniqueIdentifierNum();

	//���浱ǰ�Ѿ�ʹ�õ��ı�ʶ��
	void saveUniqueIdentifierNumToFile();

	//��ȡ�ļ��еı�ʶ��
	void readUniqueIdentifierNumFromFile();

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

	//ͨ��Id��ȡ�Ѿ���õ�װ��
	Equipment* getEquipmentById(int id);

	//ͨ��Id��ȡ�Ѿ���õ�Ӣ�ۿ���
	HeroCard* getHeroCardById(int id);

private:
	GameData();

	//����_equipmentMap�����Ԫ��
	void destoryEquipmentMapElement();
	
	//����_heroCardMap�����Ԫ��
	void destoryHeroMapElement();

private:
	int _money;
	int _gold;
	int _level;
	int _exp;

	//�����ѻ�õ�װ��
	std::unordered_map<int, Equipment*> _equipmentMap;

	//�����ѻ�õ�Ӣ�ۿ���
	std::unordered_map<int, HeroCard*> _heroCardMap;

	int _uniqueIdentifierNum;	//��¼��ƷΨһ�ı�ʶ��

	//����
	static GameData* _gameData;
};

#endif // GAMEDATA_H_
