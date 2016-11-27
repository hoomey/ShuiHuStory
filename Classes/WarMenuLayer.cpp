/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	WarMenuLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/26
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "WarMenuLayer.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "WorldMapLayer.h"

USING_NS_CC;
using namespace ui;
using namespace std;

WarMenuLayer::WarMenuLayer()
{
	//�첽���������ͼ����ͼƬ
	Director::getInstance()->getTextureCache()->addImageAsync("backgrounds/worldbg.png", [&](Texture2D* texture) {
		log("worldbg.png load finsh..");
		_texture = texture;
	});
}

WarMenuLayer::~WarMenuLayer()
{
	Director::getInstance()->getTextureCache()->removeTexture(_texture);
	log("worldbg.png removed...");
}

bool WarMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}


	loadUI();

	return true;
}

void WarMenuLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_btnLocal = node->getChildByName<Button*>(btnLocalName);
	_btnPvp = node->getChildByName<Button*>(btnPvpName);

	//�����ť�ص�
	_btnLocal->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::BEGAN == type)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (Widget::TouchEventType::ENDED == type)
		{
			auto layer = WorldMapLayer::create();
			addChild(layer);
		}
	});

	_btnPvp->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::BEGAN == type)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (Widget::TouchEventType::ENDED == type)
		{
			log("btn pvp...");
		}
	});
}
