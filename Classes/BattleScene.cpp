/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	BattleScene.cpp
// Author:		 Metoor
// Version: 	1.0
// Date: 		2016/12/01
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "BattleScene.h"
#include "Role.h"
#include "GameData.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"
#include "json/document.h"
#include "TypeStruct.h"
#include "HeroCard.h"
#include "Tools.h"
#include "AudioManager.h"
#include "GameOverLayer.h"
#include "DialogManager.h"
#include "AboutLayer.h"
#include "I18N.h"

USING_NS_CC;
using namespace std;

BattleScene::BattleScene()
	:_mapData(nullptr),
	_currentAttackIndex(0)
{
	AudioManager::getInstance()->preLoadBattleSceneAudio();
	loadAnimation();
	_mapData = new MapData();
	readEnemyMould();
}

BattleScene::~BattleScene()
{
	AudioManager::getInstance()->unLoadBattleSceneAudio();
	unLoadAnimation();

	CC_SAFE_DELETE(_mapData);

	//�ͷ�ģ��ռ�õ���Դ
	for (int index = _enemyMouldVector.size() - 1; index >= 0; --index)
	{
		CC_SAFE_DELETE(_enemyMouldVector.at(index));
		_enemyMouldVector.pop_back();
	}
}

bool BattleScene::init()
{
	if (!Layer::init())
	{
		return false;;
	}

	//����ֻ������¼�����
	addPhoneEventListener();

	createBgAndMusic();

	return true;
}

cocos2d::Scene * BattleScene::createScene(MapData* mapData)
{
	auto layer = BattleScene::create();
	layer->setMapData(mapData);

	auto scene = Scene::create();
	scene->addChild(layer);

	return scene;
}

void BattleScene::setMapData(MapData * mapData)
{
	_mapData->card = mapData->card;
	_mapData->chalevel = mapData->chalevel;
	_mapData->exp = mapData->exp;
	_mapData->gold = mapData->gold;
	_mapData->sword = mapData->sword;

	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		int type = mapData->startData[pos];

		if (type > 0)
		{
			_mapData->startData[pos] = type;
		}
		else
		{
			_mapData->startData[pos] = none;
		}
	}

	//������ս�ȼ�����ʵ�ʵĹ�������
	calEnemyRealProperty();
}

void BattleScene::battle(float dt)
{
	if (_currentAttackIndex >= _roleList.size())
	{
		//��Ϊɾ���˽�ɫ��������˽�ɫ����ǰ�ƶ���
		_currentAttackIndex = _roleList.size() - 1;
	}

	auto role = _roleList.at(_currentAttackIndex);
	if (role->getIsAlive())
	{
		//Ӣ�ۻ�����
		auto enemyList = getEnemyList(role);
		role->attack(enemyList);

		//����ѭ��
		_currentAttackIndex = (++_currentAttackIndex) % _roleList.size();
	}

}

int BattleScene::getRowRole(int * list, int row)
{
	CCAssert(row < 2, "col must be less than 2");

	int result = none;

	//�������ң����ص�һ�����ŵĽ�ɫ��������������Ѿ��������򷵻�none
	for (int pos = 0 + row * 3; pos < 3 + 3 * row; ++pos)
	{
		int index = list[pos];
		if (index != none)
		{
			result = index;
			break;
		}
	}

	return result;
}

int BattleScene::getColRole(int * list, int col)
{
	CCAssert(col < 3, "col must be less than 3");

	int result = none;

	int row1 = list[col];
	int row2 = list[col + 3];

	//��col�ĵ�һ�ŵ��ڶ��ţ����ص�һ�����ŵĽ�ɫ��������������Ѿ������򷵻�none
	if (row1 != none)
	{
		result = row1;
	}
	else if (row2 != none)
	{
		result = row2;
	}

	return result;
}

void BattleScene::createBgAndMusic()
{

	//��������
	int randomIndex = Tools::getRandomInt(0, 2);
	Sprite * bg = Sprite::create(StringUtils::format("warbg%d.png", randomIndex));
	bg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	bg->setPosition(Point::ZERO);
	addChild(bg);

	//���ű�������
	AudioManager::getInstance()->playBattleSceneBgMusic();
}

void BattleScene::initRoleIndex()
{
	//��ʼ���б�Ϊnone
	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		_enemyIndex[pos] = none;
		_heroIndex[pos] = none;
	}

	for (int index = 0; index < _roleList.size(); ++index)
	{
		auto role = _roleList.at(index);

		if (role->getRoleType() == RT_HERO)
		{
			//��ɫ����ΪHero
			_heroIndex[role->getPos()] = index;
		}
		else
		{
			//��ɫ����Ϊ����
			_enemyIndex[role->getPos()] = index;
		}
	}
}

void BattleScene::createRole()
{
	auto gameData = GameData::getInstance();

	//����Ӣ�۽�ɫ
	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		int heroId = gameData->getBattleHeroId(pos);

		if (heroId != none)
		{
			//��λ����Ӣ�ۣ�����Ӣ��
			auto property = gameData->getHeroCardById(heroId)->getProperty();
			auto heroRole = Role::create();
			heroRole->initRole(property, pos);

			_roleList.pushBack(heroRole);
		}
	}

	//�����з���ɫ
	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		int enemyType = _mapData->startData[pos];

		if (enemyType != none)
		{
			//��λ����Ӣ�ۣ�����Ӣ��
			auto property = getEnemyProperty(enemyType);
			auto enemyRole = Role::create();
			enemyRole->initRole(property, pos);

			_roleList.pushBack(enemyRole);
		}
	}

	//����speed����������Ϊ�����ٶȸߵ����ȹ���
	sortBySpeed();

	//���ݴ����õĽ�ɫ����������
	initRoleIndex();
}

void BattleScene::displayRole()
{
	//��ʾӢ��
	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		int index = _heroIndex[pos];

		if (index != none)
		{
			auto role = _roleList.at(index);
			role->setPosition(HeroPosition[pos]);
			addChild(role);
		}
	}

	//��ʾ����
	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		int index = _enemyIndex[pos];

		if (index != none)
		{
			auto role = _roleList.at(index);
			role->setPosition(EnemyPosition[pos]);
			addChild(role);
		}
	}
}

void BattleScene::readEnemyMould()
{
	string filepath = FileUtils::getInstance()->fullPathForFilename("datas/enemy.json");
	rapidjson::Document doc;

	string content = FileUtils::getInstance()->getStringFromFile(filepath);

	doc.Parse<0>(content.c_str());

	if (doc.HasParseError()) {
		CCAssert(false, "Json::cloth.json Reader Parse error!");
	}

	if (!doc["data"].IsNull() && doc["data"].IsArray())
	{

		for (unsigned int inex = 0; inex < doc["data"].Size(); ++inex)
		{
			rapidjson::Value & json = doc["data"][inex];

			auto enemy = new EnemyProperty();

			enemy->ap = json["ap"].GetInt();
			enemy->mp = json["mp"].GetInt();
			enemy->hp = json["hp"].GetInt();
			enemy->type = json["type"].GetInt();
			enemy->attackId = json["attackid"].GetInt();
			enemy->skillId = json["skillsid"].GetInt();
			enemy->defend = json["defend"].GetInt();
			enemy->mDefend = json["mDefine"].GetInt();
			enemy->block = json["block"].GetInt();
			enemy->crit = json["crit"].GetInt();
			enemy->critDmg = json["critDmg"].GetInt();
			enemy->speed = json["speed"].GetInt();
			enemy->isMagic = json["isMagic"].GetBool();

			_enemyMouldVector.push_back(enemy);
		}
	}
}

void BattleScene::calEnemyRealProperty()
{
	for (unsigned int index = 0; index < _enemyMouldVector.size(); ++index)
	{
		auto enemyProerty = _enemyMouldVector.at(index);

		//ÿ����һ���������ӵ�����
		int hp = 50;
		int ap = 20;
		int df = 10;
		int speed = 2;
		int critDmg = 1;
		float rate = 0.5;

		int chalevel = _mapData->chalevel;

		enemyProerty->ap += chalevel * ap;
		enemyProerty->mp += chalevel * ap;
		enemyProerty->hp += chalevel * hp;
		enemyProerty->defend += chalevel * df;
		enemyProerty->mDefend += chalevel * df;
		enemyProerty->block += (int)(chalevel * rate);
		enemyProerty->crit += (int)(chalevel * rate);
		enemyProerty->critDmg += chalevel * critDmg;
		enemyProerty->speed += chalevel * speed;
	}
}

void BattleScene::sortBySpeed()
{
	int length = _roleList.size();

	for (int i = 0; i < length - 1; ++i)
	{
		int swapIndex = none;
		int speed1 = _roleList.at(i)->getSpeed();

		for (int j = i + 1; j < length; ++j)
		{
			int speed2 = _roleList.at(j)->getSpeed();

			if (speed1 < speed2)
			{
				//���ָ����������¼�������������������Ա�����ɱ��β��Һ󽻻�λ��
				swapIndex = j;
				speed1 = speed2;
			}
		}

		if (swapIndex != none)
		{
			//�ͱ����ҵ�������������λ��
			_roleList.swap(i, swapIndex);
		}
	}
}

EnemyProperty * BattleScene::getEnemyProperty(int type)
{
	//type�Ǵ�201��ʼ��������Ҫ��ȥ200��ת��������������
	int index = type - 200;

	return _enemyMouldVector.at(index);
}

void BattleScene::removeDeadRoleFormRoleList()
{
	for (int index = 0; index < _roleList.size(); ++index)
	{
		auto role = _roleList.at(index);
		int pos = role->getPos();

		if (!role->getIsAlive())
		{
			//�Ƴ������Ľ�ɫ
			if (role->getRoleType() == RT_HERO)
			{
				//���������ҷ�Ӣ��
				_heroIndex[pos] = none;
			}
			else
			{
				//�������ǵз���Ӣ��
				_enemyIndex[pos] = none;
			}

			_roleList.erase(index);

			//��Ϊ�Ƴ��˽�ɫ������������Ҳ��Ҫ����
			initRoleIndex();
		}
	}
}


void BattleScene::onEnter()
{
	Layer::onEnter();

	//������ɫ
	createRole();

	//��ʾ��ɫ
	displayRole();
}

void BattleScene::onExit()
{
	Layer::onExit();

	//ȡ����ʱ��
	unschedule(schedule_selector(BattleScene::battle));
	this->unscheduleUpdate();

	//�رձ�������
	AudioManager::getInstance()->playGamingSceneBgMusic();
}

void BattleScene::onEnterTransitionDidFinish()
{
	//������ʱ��
	schedule(schedule_selector(BattleScene::battle), frequent);
	this->scheduleUpdate();
}

void BattleScene::update(float dt)
{
	int gameover = isGameOver();

	switch (gameover)
	{
	case 0:
	case 1:
	{
		//��ֹͣ��ʱ��
		unschedule(schedule_selector(BattleScene::battle));
		this->unscheduleUpdate();

		//������Ϸ���㳡��
		auto delay = DelayTime::create(1.2f);
		auto gameOverCallback = CallFunc::create([&, gameover]() {
			
			auto overLayer = GameOverLayer::create();
			bool isWin = gameover == 0;
			ExtraRewardType rewardType = ERT_NONE;
			int type = none;
			
			//��ȡ���⽱��������
			if (_mapData->card != none)
			{
				rewardType = ERT_CARD;
				type = _mapData->card;
			}
			else if (_mapData->sword != none)
			{
				rewardType = ERT_EQUIPMENT;
				type = _mapData->sword;
			}
			
			overLayer->initLayer(isWin, rewardType, type, _mapData->gold, _mapData->exp);
			addChild(overLayer);
		});

		runAction(Sequence::createWithTwoActions(delay, gameOverCallback));

		break;
	}
	case -1:
		//��Ϸ��û�н���
		removeDeadRoleFormRoleList();
		break;
	default:
		break;
	}
}

cocos2d::Vector<Role*>* BattleScene::getEnemyList(Role * role)
{
	//����ϴε�����
	_attackList.clear();

	int * indexList = nullptr;
	int attackId = role->getAttackId();

	if (role->getRoleType() == RT_HERO)
	{
		//������Ŀ���ǹ���
		indexList = _enemyIndex;
	}
	else
	{
		//������Ŀ����Ӣ��
		indexList = _heroIndex;
	}

	if (attackId >= 0 && attackId <= 100)	//��������Ŀ��
	{
		int currentPos = role->getPos();

		//���ȹ���ǰ��
		if (currentPos > 2)
		{
			currentPos -= 3;
		}

		int attackIndex = getColRole(indexList, currentPos);
		if (attackIndex != none)
		{
			//���Լ�ͬһ���н�ɫ�����ȹ�����һ�ţ������һ��û��ɫ���򹥻��ڶ���
			_attackList.pushBack(_roleList.at(attackIndex));
		}
		else if ((attackIndex = getRowRole(indexList, 0)) != none)
		{
			//�͹���Ӣ����ͬ��һ��û�н�ɫ����һ������λ���н�ɫ�����ȹ�����һ�ţ�
			_attackList.pushBack(_roleList.at(attackIndex));
		}
		else if ((attackIndex = getRowRole(indexList, 1)) != none)
		{
			//�͹���Ӣ����ͬ��һ��û�н�ɫ����һ��Ҳû�н�ɫ�������ڶ��Ž�ɫ��
			_attackList.pushBack(_roleList.at(attackIndex));
		}
	}
	else if (100 < attackId && attackId <= 200)	//����ȫ��Ŀ��
	{
		for (int pos = 0; pos < max_battle_hero_num; ++pos)
		{
			int attackIndex = indexList[pos];
			if (attackIndex != none)
			{
				//ֻҪ��Ӣ�۾���ӵ������б�
				_attackList.pushBack(_roleList.at(attackIndex));
			}
		}
	}
	else if (200 < attackId && attackId <= 300)	//����ǰ��Ŀ��
	{
		if (getRowRole(indexList, 0) != none)
		{
			//��һ����Ӣ�ۣ����ȹ�����һ��
			for (int pos = 0; pos < 3; ++pos)
			{
				int attackIndex = indexList[pos];
				if (attackIndex != none)
				{
					_attackList.pushBack(_roleList.at(attackIndex));
				}
			}
		}
		else if (getRowRole(indexList, 1) != none)
		{
			//��һ��û��Ӣ�ۣ����ǵڶ�����Ӣ��
			for (int pos = 3; pos < max_battle_hero_num; ++pos)
			{
				int attackIndex = indexList[pos];
				if (attackIndex != none)
				{
					_attackList.pushBack(_roleList.at(attackIndex));
				}
			}
		}
	}
	else if (300 < attackId && attackId <= 400)	//��������Ŀ��
	{
		if (getRowRole(indexList, 1) != none)
		{
			//�ڶ��Ŵ���Ӣ�ۣ����ȹ����ڶ���
			for (int pos = 3; pos < max_battle_hero_num; ++pos)
			{
				int attackIndex = indexList[pos];
				if (attackIndex != none)
				{
					_attackList.pushBack(_roleList.at(attackIndex));
				}
			}
		}
		else if (getRowRole(indexList, 0) != none)
		{
			//�ڶ���û��Ӣ�ۣ����ǵ�һ����Ӣ�ۣ�������һ��
			for (int pos = 0; pos < 3; ++pos)
			{
				int attackIndex = indexList[pos];
				if (attackIndex != none)
				{
					_attackList.pushBack(_roleList.at(attackIndex));
				}
			}
		}
	}
	else if (400 < attackId && attackId <= 500)	//��������Ŀ��
	{
		//���ȹ������Լ�ͬһ�е�Ӣ��
		int col = role->getPos();

		if (col > 2)
		{
			//Ӣ�۵�λ���ڵڶ��У��������Ӧ����
			col -= 3;
		}

		if (getColRole(indexList, col) != none)
		{
			//���Լ�ͬһ�еĵз���Ӣ��
			for (int pos = col; pos < max_battle_hero_num; pos += 3)
			{
				int attackIndex = indexList[pos];
				if (attackIndex != none)
				{
					_attackList.pushBack(_roleList.at(attackIndex));
				}
			}
		}
		else
		{
			//���Լ�ͬһ�еĵз�û��Ӣ�ۣ������ȹ�����һ��
			int nextCol = (col + 1) % 3;
			while (nextCol != col)
			{
				if (getColRole(indexList, nextCol) != none)
				{
					for (int pos = nextCol; pos < max_battle_hero_num; pos += 3)
					{
						int attackIndex = indexList[pos];
						if (attackIndex != none)
						{
							_attackList.pushBack(_roleList.at(attackIndex));
						}
					}
					
					//�Ѿ���ȡ��������������ѭ��
					break;
				}
				nextCol = (++nextCol) % 3;
			}
		}
	}

	return &_attackList;
}

int BattleScene::isGameOver()
{
	int result = none;

	int heroIsAlive = isAlive(_heroIndex);
	int enemyIsAlive = isAlive(_enemyIndex);

	if (heroIsAlive && enemyIsAlive)
	{
		result = none;
	}
	else if (heroIsAlive)
	{
		result = 0;
	}
	else
	{
		result = 1;
	}

	return result;
}

bool BattleScene::isAlive(int * list)
{
	bool isAlive = false;

	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		int index = list[pos];
		if (index != none)
		{
			isAlive = true;
			break;
		}
	}

	return isAlive;
}

void BattleScene::loadAnimation()
{
	//���ض�������
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect11.plist", "effect11.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect14.plist", "effect14.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect15.plist", "effect15.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect16.plist", "effect16.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect17.plist", "effect17.png");
}

void BattleScene::unLoadAnimation()
{
	//�ͷŶ�������
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("effect11.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("effect14.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("effect15.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("effect16.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("effect17.plist");
}

void BattleScene::addPhoneEventListener()
{
	//���ֻ����ؼ��ļ���
	auto listener = EventListenerKeyboard::create();

	//�ͻص�������
	listener->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);

	//��ӵ��¼��ַ�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void BattleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		//�����˳���Ϸ����
		auto i18n = I18N::getInstance();
		DialogManager::getInstance()->showDialog(i18n->getStringByKey(qtitle), i18n->getStringByKey(back), [](Ref* psender) {
			Director::getInstance()->popScene();
		});
	}
}