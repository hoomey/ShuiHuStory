/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	BattleScene.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/12/01
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef BATTLESCENE_H_  
#define BATTLESCENE_H_  
  
#include "cocos2d.h"
#include "vector"
#include "ConstantDefine.h"

//ǰ������
struct MapData;
struct EnemyProperty;
class Role;

class BattleScene : public cocos2d::Layer
{
public:
	BattleScene();
	~BattleScene();
	virtual bool init() override;
	CREATE_FUNC(BattleScene);

	static cocos2d::Scene* createScene(MapData* mapData);

	//���ùؿ���ص����ݣ��磺��ս�ȼ�����ʤ������
	void setMapData(MapData* mapData);

private:
	//ս������
	void battle(float dt);

	//��ó�սλ��һ���е�һ����Ϊ�յĽ�ɫ�������������none���ʾ��Ϊ�� row��0�� 1��
	int getRowRole(int* list, int row);

	//��ó�սλ�ã�ĳһ�в�Ϊ�յĽ�ɫ�������Ϊ���򷵻�none�� col��0�� 2��
	int getColRole(int* list, int col);

	//���role�Ĺ�������
	cocos2d::Vector<Role*>* getEnemyList(Role* role);

	void createBgAndMusic();

	//����_enemyIndex��_heroIndex��_roleList��ӳ�䡣
	void initRoleIndex();

	//�����ҷ�Ӣ�ۺ͵ط���ɫ
	void createRole();

	//���ҷ���ɫ�͵з���ɫ��ʾ�ĳ�����
	void displayRole();

	//��ȡ�з���Ӣ�۵�����ģ��
	void readEnemyMould();

	//����ģ���������˵�ʵ������
	void calEnemyRealProperty();

	//��roleList���Ԫ������role->speed�Ӵ�С����
	void sortBySpeed();
	
	//ͨ�Ķ�Ӧ���͵ĵ�������
	EnemyProperty* getEnemyProperty(int type);

	//�Ƴ�roleList�������Ľ�ɫ
	void removeDeadRoleFormRoleList();

	//��Ϸû�н�������none�� ��Ϸ��������һ�ʤ����0�����Ի�ʤ����1
	int isGameOver();

	//�ж�list���Ƿ��л��ŵĽ�ɫ
	bool isAlive(int * list);

	void loadAnimation();
	void unLoadAnimation();


	void onEnter() override;
	void onExit() override;
	void onEnterTransitionDidFinish() override;

	void update(float dt);

private:
	const cocos2d::Point HeroPosition[max_battle_hero_num] = { cocos2d::Point(120, 350), cocos2d::Point(320, 350), cocos2d::Point(520, 350),
		cocos2d::Point(120, 120), cocos2d::Point(320, 120), cocos2d::Point(520, 120) };

	const cocos2d::Point EnemyPosition[max_battle_hero_num] = { cocos2d::Point(120, 610), cocos2d::Point(320, 610), cocos2d::Point(520, 610),
		cocos2d::Point(120, 840), cocos2d::Point(320, 840), cocos2d::Point(520, 840) };

	//��ǰ���ڽ��й�����Ϊ�Ľ�ɫ����
	const float frequent = 1.5f;

private:
	//��ǰ���ڽ��й�����Ϊ�Ľ�ɫ����
	int _currentAttackIndex;

	//�����ݴ湥�����󣬱���ÿ�ζ��ȴ�������
	cocos2d::Vector<Role*> _attackList;

	MapData* _mapData;
	cocos2d::Vector<Role*> _roleList;

	//��¼��ɫ��_roleList�е�������none��ʾ������
	int _enemyIndex[max_battle_hero_num];
	int _heroIndex[max_battle_hero_num];

	std::vector<EnemyProperty*> _enemyMouldVector;
};
  
#endif // BATTLESCENE_H_ 
