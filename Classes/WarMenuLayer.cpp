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
	Director::getInstance()->getTextureCache()->addImageAsync("backgrounds/worldbg.png", CC_CALLBACK_1(WarMenuLayer::loadTexture, this));

	//�첽������Ϸui
	Director::getInstance()->getTextureCache()->addImageAsync("ui/ui_2.png", CC_CALLBACK_1(WarMenuLayer::loadTexture, this));
}

WarMenuLayer::~WarMenuLayer()
{
	auto textureCache = Director::getInstance()->getTextureCache();
	
	//�Ƴ����������ص�Texture
	for (int index= 0; index < _textureList.size(); ++index)
	{
		textureCache->removeTexture(_textureList.at(index));
		_textureList.popBack();
	}
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

void WarMenuLayer::loadTexture(cocos2d::Texture2D * texture)
{
	//������غ��texture
	_textureList.pushBack(texture);
}
