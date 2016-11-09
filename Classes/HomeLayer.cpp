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
#include "ConstantDefine.h"
#include "DetialsLayer.h"

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

	return true;
}

void HomeLayer::loadUI()
{
	//���ر༭�õ���ҳ�����ļ�
	auto homeLayer = CSLoader::createNode(csbName);
	addChild(homeLayer);

	//�󶨲˵��Ļص�����
	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		auto menu = homeLayer->getChildByTag<Button*>(index);
		menu->addTouchEventListener(CC_CALLBACK_2(HomeLayer::menuCallBack, this));
	}
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
			detailsLayer->setBtnIntensifyCallBack([](Ref* pSender, Widget::TouchEventType type) {
				log("intensify clicked...");
			});

			detailsLayer->setBtnLevelupCallBack([](Ref* pSender, Widget::TouchEventType type) {
				log("levelup clicked...");
			});
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
			detailsLayer->setBtnIntensifyCallBack([](Ref* pSender, Widget::TouchEventType type) {
				log("intensify clicked...");
			});
			detailsLayer->setBtnLevelupCallBack([](Ref* pSender, Widget::TouchEventType type) {
				log("levelup clicked...");
			});
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
