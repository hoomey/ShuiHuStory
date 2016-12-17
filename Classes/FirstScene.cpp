/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	FirstScene.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "FirstScene.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "ParticleLayer.h"
#include "GameScene.h"
#include "DialogManager.h"
#include "I18N.h"
#include "AboutLayer.h"
#include "ConstantDefine.h"

USING_NS_CC;
using namespace ui;

FirstScene::FirstScene()
	:_currentIndex(0)
{
	AudioManager::getInstance()->preLoadGlobalAudio();

	readChatData();
}

FirstScene::~FirstScene()
{
	UserDefault::getInstance()->setBoolForKey("if", false);
}

bool FirstScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//����ֻ������¼�
	addPhoneEventListener();


	//��������
	AudioManager::getInstance()->playFirstSceneBgMusic();

	//ע�ᴥ���¼�
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = [](Touch* touch, Event* event) {

		return true;
	};

	listen->onTouchMoved = [](Touch* touch, Event* event) {

	};

	listen->onTouchEnded = [&](Touch* touch, Event* event) {
		//�����Ч
		AudioManager::getInstance()->playClickEffect();


		nextMsg();
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);

	loadUI();

	//����������Ч
	auto particle = ParticleLayer::create();
	addChild(particle, 9000);

	//��ʾ��ʼ�԰�
	nextMsg();

	return true;
}

cocos2d::Scene * FirstScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FirstScene::create();

	scene->addChild(layer);

	return scene;
}

void FirstScene::loadUI()
{
	//������
	auto root = CSLoader::createNode(csbName);
	addChild(root);

	_heroName = root->getChildByTag<Text*>(heroNameTextTag);
	_chatContent = root->getChildByTag<Text*>(chatContentTextTag);
	_heroImage = root->getChildByTag<ImageView*>(heroImageTag);
}

void FirstScene::setContent(std::string heroName, std::string chatContent, std::string heroImage)
{
	_heroName->setString(heroName);
	_chatContent->setString(chatContent);
	_heroImage->loadTexture(heroImage);
}

void FirstScene::readChatData()
{
	std::string jsonpath = FileUtils::getInstance()->fullPathForFilename(storyFileName);
	std::string contentStr = FileUtils::getInstance()->getStringFromFile(jsonpath);
	_doc.Parse<0>(contentStr.c_str());

	if (_doc.HasParseError()) {
		return;
	}
}

void FirstScene::nextMsg()
{
	if (_currentIndex < _doc["datas"].Size())
	{
		rapidjson::Value & json = _doc["datas"][_currentIndex];
		setContent(json["name"].GetString(), json["msg"].GetString(), json["picture"].GetString());
		++_currentIndex;
	}
	else
	{
		//�԰������ת����Ϸ��ҳ
		Director::getInstance()->replaceScene(TransitionShrinkGrow::create(1.0f, GameScene::createScene()));
	}
}

void FirstScene::addPhoneEventListener()
{
	//���ֻ����ؼ��ļ���
	auto listener = EventListenerKeyboard::create();

	//�ͻص�������
	listener->onKeyReleased = CC_CALLBACK_2(FirstScene::onKeyReleased, this);

	//��ӵ��¼��ַ�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void FirstScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * pEvent)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
	{
		//�����˳���Ϸ����
		auto i18n = I18N::getInstance();
		DialogManager::getInstance()->showDialog(i18n->getStringByKey(qtitle), i18n->getStringByKey(quit), [](Ref* psender) {
			Director::getInstance()->end();
		});
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_MENU:
	{
		auto aboutLayer = AboutLayer::create();
		addChild(aboutLayer);
		break;
	}
	default:
		break;
	}
}
