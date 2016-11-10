/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	GameScene.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "GameScene.h"
#include "ParticleLayer.h"
#include "cocostudio/CocoStudio.h"
#include "GameData.h"
#include "HomeLayer.h"
#include "AudioManager.h"
#include "ConstantDefine.h"
#include "I18N.h"

USING_NS_CC;
using namespace ui;
using namespace std;


GameScene::GameScene()
	:_preMenu(nullptr)
{
	//��ʼ����Ϸ����
	GameData::getInstance();

	AudioManager::getInstance()->preLoadGlobalAudio();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("head.plist", "head.pvr.ccz");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("equipment.plist", "equipment.pvr.ccz");
	
	I18N::getInstance()->loadStringFile("string.plist");
}

GameScene::~GameScene()
{
	auto gameData = GameData::getInstance();
	gameData->saveUniqueIdentifierNumToFile();
	gameData->saveEquipment();
	gameData->saveHeroCard();
	gameData->saveBattleHero();

	auto audio = AudioManager::getInstance();
	audio->unLoadGlobalEffect();

	gameData->destoryInstance();
	audio->destoryInstance();

	//��ΪButton�����ü��������Խ�����ȫ���ÿ�
	initArrayToNullptr();
}

Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	loadUI();

	initArrayToNullptr();

	//�����ֻ����ؼ��ĵ���¼�
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//����������Ч
	auto paricle = ParticleLayer::create();
	addChild(paricle, particle_z_order);

	//����Ĭ��ת��Home����
	_layerPointer[0] = HomeLayer::create();
	addChild(_layerPointer[0]);
	_preMenu->setEnabled(false);

	return true;
}

//�ֻ����ؼ�����ص�
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::getInstance()->end();
	}
}

void GameScene::initArrayToNullptr()
{
	//��ʼ������Ϊnullptr
	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		_layerPointer[index] = nullptr;
	}
}

void GameScene::loadUI()
{
	//������Ϸ����
	auto bgLayer = CSLoader::createNode(csbName);
	addChild(bgLayer);

	//���ز˵���
	auto menuLayer = CSLoader::createNode(csbMenuName);
	addChild(menuLayer, menu_z_order);

	//Ϊ�˵��󶨻ص�����
	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		auto menu = menuLayer->getChildByTag<Button*>(index);
		menu->addTouchEventListener(CC_CALLBACK_2(GameScene::menuCallBack, this));

		//��Ϊ��ʼĬ��ѡ�е�һ����ť
		if (index == 0)
		{
			_preMenu = menu;
		}
	}
}

void GameScene::menuCallBack(Ref * pSender, Widget::TouchEventType type)
{

	if (type == Widget::TouchEventType::BEGAN)
	{
		//���ŵ����Ч
		AudioManager::getInstance()->playClickEffect();
	}

	if (type == Widget::TouchEventType::ENDED)
	{
		//��ȡ��ǰ�ĵ���˵���tag���ϴε����Tag
		auto currentMenu = dynamic_cast<Button*>(pSender);
		int currentTag = currentMenu->getTag();
		int preTag = _preMenu->getTag();

		if (preTag != currentTag && preTag != none)
		{
			//����ϴε���������εĲ�һ�����Ҳ�����none������Ҫ������ǰ�����㣬Ȼ���ͷ��ϴε�������
			log("--current:%d--pre:%d", currentTag, preTag);
		}

		//�������������ͬ�Ĳ˵������õ�ǰ�Ĳ˵��������һ�εĲ˵�
		_preMenu->setEnabled(true);
		currentMenu->setEnabled(false);

		//������ε���Ĳ˵�ָ������
		_preMenu = currentMenu;

	}
}
