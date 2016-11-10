/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	HomeLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "HomeLayer.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "DisplayLayer.h"
#include "DetialsLayer.h"
#include "GameData.h"

USING_NS_CC;
using namespace ui;
using namespace std;

HomeLayer::HomeLayer()
	:_preMenu(nullptr)
{
}

HomeLayer::~HomeLayer()
{
}

bool HomeLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	loadUI();

	//��ʼ������Ϊnullptr
	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		_layerPointer[index] = nullptr;
	}

	updateUserData();

	addUpdateUserDataEventListener();

	return true;
}

void HomeLayer::loadUI()
{
	//���ر༭�õ���ҳ�����ļ�
	auto homeLayer = CSLoader::createNode(csbName);
	addChild(homeLayer);

	_dianmodLabel = homeLayer->getChildByName<Text*>(diamodNumName);
	_goldLabel = homeLayer->getChildByName<Text*>(goldNumName);
	_levelLabel = homeLayer->getChildByName<Text*>(levelNumName);
	_expLabel = homeLayer->getChildByName<Text*>(expNumName);
	_expBar = homeLayer->getChildByName<LoadingBar*>(expBarName);

	//�󶨲˵��Ļص�����
	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		auto menu = homeLayer->getChildByTag<Button*>(index);
		menu->addTouchEventListener(CC_CALLBACK_2(HomeLayer::menuCallBack, this));
	}
}

void HomeLayer::addUpdateUserDataEventListener()
{
	//ע����������¼�
	auto listen = EventListenerCustom::create(msg_update_user_data, [&](EventCustom* event) {
		updateUserData();
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
}

void HomeLayer::updateUserData()
{
	auto data = GameData::getInstance();

	_levelLabel->setString(StringUtils::format("%d", data->getLevel()));
	_goldLabel->setString(StringUtils::format("%d", data->getGold()));
	_dianmodLabel->setString(StringUtils::format("%d", data->getDiamond()));
	
	//���þ������ĵ�ǰ������ܵþ���
	int maxExp = data->getExpLimit(start_exp_rate, data->getLevel());
	int currentExp = data->getExp();

	_expLabel->setString(StringUtils::format("%d/%d", currentExp, maxExp));
	_expBar->setPercent(currentExp * 1.0f / maxExp);
}

Layer* HomeLayer::createMenuLayer(HomeMenuType type)
{
	Layer* layer = nullptr;

	switch (type)
	{
	case HMT_EQUIPMENT:
	{
		auto displayLayer = DisplayLayer::create();
		displayLayer->setBtnTxture(btnDetails1, btnDetails2);
		displayLayer->setDisplayType(OT_EQUIPMENT);

		//�б���item��İ�ť�ص�
		displayLayer->setBtnCallBack([&](Ref* pSender) {
			auto btn = static_cast<Button*>(pSender);
			int id = (int)btn->getUserData();

			//����װ������㲢��ʾ
			auto detailsLayer = DetialsLayer::create();
			detailsLayer->initUiWithId(id, DT_EQUIPMENT);
			
			addChild(detailsLayer);
		});

		layer = displayLayer;
		break;
	}
	case HMT_HERO:
	{
		auto displayLayer = DisplayLayer::create();
		displayLayer->setBtnTxture(btnDetails1, btnDetails2);
		displayLayer->setDisplayType(OT_HERO);

		//�б���item��İ�ť�ص�
		displayLayer->setBtnCallBack([&](Ref* pSender) {
			auto btn = static_cast<Button*>(pSender);
			int id = (int)btn->getUserData();

			//����Ӣ�ۿ�������㲢��ʾ
			auto detailsLayer = DetialsLayer::create();
			detailsLayer->initUiWithId(id, DT_HERO);
			addChild(detailsLayer);
		});

		layer = displayLayer;
		break;
	}
	case HMT_LOGIN:
		break;
	case HMT_LEVEL_UP:
		break;
	case HMT_ABOUT:
		break;
	case HMT_AUDIO:
		break;
	default:
		break;
	}

	return layer;
}

void HomeLayer::menuCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		//���ŵ����Ч
		AudioManager::getInstance()->playClickEffect();
	}

	if (type == Widget::TouchEventType::ENDED)
	{
		int currentTag = dynamic_cast<Button*>(pSender)->getTag();
		auto layer = createMenuLayer(static_cast<HomeMenuType>(currentTag));
		addChild(layer);
	}
}
