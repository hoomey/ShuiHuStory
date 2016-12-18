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
#include "AudioManager.h"
#include "ConstantDefine.h"
#include "I18N.h"
#include "Config.h"
#include "HomeLayer.h"
#include "TeamLayer.h"
#include "HeroLayer.h"
#include "PictureLayer.h"
#include "StoreLayer.h"
#include "WarMenuLayer.h"
#include "DialogManager.h"

USING_NS_CC;
using namespace ui;
using namespace std;


GameScene::GameScene()
	:_preMenu(nullptr),
	_preLayer(nullptr),
	_currentLayer(nullptr)
{
	//��ʼ����Ϸ���ݹ�����
	if (GameData::isNullptr())
	{
		Config::getInstance();
		GameData::getInstance()->readData();
		I18N::getInstance()->loadData();
		AudioManager::getInstance()->preLoadGlobalAudio();
	}

	//�첽������Ϸui
	Director::getInstance()->getTextureCache()->addImageAsync("ui/ui_1", [&](Texture2D* texture) {
		log("ui_1.png load finsh..");
	});
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("head.plist", "head.pvr.ccz");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("equipment.plist", "equipment.pvr.ccz");
}

GameScene::~GameScene()
{
	//�ͷ���Ϸ����
	I18N::getInstance()->loadStringFile("string.plist");
	GameData::getInstance()->destoryInstance();
	Config::getInstance()->destoryInstance();
	AudioManager::getInstance()->destoryInstance();
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

	//�����ֻ����ؼ��ĵ���¼�
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//����������Ч
	auto paricle = ParticleLayer::create();
	addChild(paricle, particle_z_order);

	//����Ĭ��ת��Home����
	_preLayer = HomeLayer::create();
	addChild(_preLayer);
	_preMenu->setEnabled(false);

	//��Ϸ��������
	AudioManager::getInstance()->playGamingSceneBgMusic();

	return true;
}

cocos2d::Layer * GameScene::createLayer(GameMenuType type)
{
	Layer* layer = nullptr;

	switch (type)
	{
	case GMT_HOME:
		layer = HomeLayer::create();
		break;
	case GMT_TEAM:
		layer = TeamLayer::create();
		break;
	case GMT_HERO:
		layer = HeroLayer::create();
		break;
	case GMT_WAR:
		layer = WarMenuLayer::create();
		break;
	case GMT_PHOTO:
		layer = PictureLayer::create();
		break;
	case GMT_STORE:
		layer = StoreLayer::create();
		break;
	default:
		break;
	}

	return layer;
}

//�ֻ����ؼ�����ص�
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		//�����˳���Ϸ����
		auto i18n = I18N::getInstance();
		DialogManager::getInstance()->showDialog(i18n->getStringByKey(qtitle), i18n->getStringByKey(quit), [](Ref* psender) {
			Director::getInstance()->end();
		});
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
			//�ͷ���һ�˵���
			_preLayer->removeFromParentAndCleanup(true);

			//������ǰ����˵���Ӧ�ĳ���
			_currentLayer = createLayer(static_cast<GameMenuType>(currentTag));
			addChild(_currentLayer);
		}

		//�������������ͬ�Ĳ˵������õ�ǰ�Ĳ˵��������һ�εĲ˵�
		_preMenu->setEnabled(true);
		currentMenu->setEnabled(false);

		//������ε���Ĳ˵��ͳ���ָ������
		_preMenu = currentMenu;
		_preLayer = _currentLayer;

		//����ǰ����ָ���ÿ�
		_currentLayer = nullptr;

	}
}
