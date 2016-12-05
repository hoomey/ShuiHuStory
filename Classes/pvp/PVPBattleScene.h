/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	PVPBattleScene.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/12/04
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef PVPBATTLESCENE_H_  
#define PVPBATTLESCENE_H_  
  
#include "cocos2d.h"
#include "ConstantDefine.h"
#include "PVPRole.h"
#include <vector>

struct PVPData;
class PVPRole;

struct BattleProgress
{
	int player;
	int attackHeroPos;
	int dmg[max_battle_hero_num];
	int skillId;
};

class PVPBattleScene : public cocos2d::Layer
{
public:
	PVPBattleScene();
	~PVPBattleScene();
	virtual bool init() override;
	CREATE_FUNC(PVPBattleScene);

	static cocos2d::Scene* createScene(PVPData * pvpData);

private:
	//���ַ�����������ԭ��ս������
	void getBattleProgressFromeString(const std::string & battle);

	void getEnemyData(const std::string& data);

	//�����ҷ�Ӣ�ۺ͵ط���ɫ
	void createRole();

	//���ҷ���ɫ�͵з���ɫ��ʾ�ĳ�����
	void displayRole();

	//ս������
	void battle(float dt);

	void createBgAndMusic();

	void loadAnimation();
	void unLoadAnimation();

	void onEnter() override;
	void onExit() override;
	void onEnterTransitionDidFinish() override;

private:
	const cocos2d::Point HeroPosition[max_battle_hero_num] = { cocos2d::Point(120, 350), cocos2d::Point(320, 350), cocos2d::Point(520, 350),
		cocos2d::Point(120, 120), cocos2d::Point(320, 120), cocos2d::Point(520, 120) };

	const cocos2d::Point EnemyPosition[max_battle_hero_num] = { cocos2d::Point(120, 610), cocos2d::Point(320, 610), cocos2d::Point(520, 610),
		cocos2d::Point(120, 840), cocos2d::Point(320, 840), cocos2d::Point(520, 840) };

	//ÿ��Ӣ�۹���ս����ʱ��
	const float frequent = 1.3f;

private:
	int _playerId;
	
	//��Ϸ�Ƿ����
	bool _isGameOver;
	
	//�Ƿ�ʤ��
	bool _isWin;

	//������Ϸ���ĵĽ��
	int _gold;

	//��ǰ����������
	unsigned int _currentIndex;

	PVPRole _enemyArray[max_battle_hero_num];
	PVPRole _heroArray[max_battle_hero_num];

	std::vector<BattleProgress*> _battleVector;
	std::vector<PVPEnemy*> _enemyData;
};
  
#endif // PVPBATTLESCENE_H_ 
