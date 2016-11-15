/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	AboutLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/14
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "AboutLayer.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "BlockLayer.h"
#include "ConstantDefine.h"

USING_NS_CC;
using namespace ui;

AboutLayer::AboutLayer()
{
}

AboutLayer::~AboutLayer()
{
}

bool AboutLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//����������
	auto blockLayer = BlockLayer::create();
	blockLayer->setName(blockTagName);
	addChild(blockLayer);

	loadUI();

	return true;
}

void AboutLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_btnClose = node->getChildByName<Button*>(btnCloseName);

	_btnClose->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::BEGAN == type)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (Widget::TouchEventType::ENDED == type)
		{
			endAnimation();
		}
	});
}

void AboutLayer::startAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//����λ������Ļ����
	this->setPosition(-visibleSize.width, 0);

	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(0, 0)), 0.2f);

	//���ƶ���ɺ���ʾ����������
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		//��ʾ����������
		dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(160.0f);
	}));

	this->runAction(ani);
}

void AboutLayer::endAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�����ش�������
	dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(0.0f);

	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(-visibleSize.width, 0)), 0.2f);

	//������ƶ����ͷ���Դ
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}

void AboutLayer::onEnterTransitionDidFinish()
{
	startAnimation();
}
