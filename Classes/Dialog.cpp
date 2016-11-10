/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	Dialog.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/09
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "Dialog.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "BlockLayer.h"
#include "ConstantDefine.h"

USING_NS_CC;
using namespace std;
using namespace ui;

Dialog::Dialog()
{
}

Dialog::~Dialog()
{
}

bool Dialog::init()
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

void Dialog::startAnimation()
{
	//y���0���ӵ�1
	setScaleY(0.0f);

	auto ani = Sequence::createWithTwoActions(ScaleTo::create(0.4f, 1.0f), CallFunc::create([&]() {
		//��ʾ����������
		dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(160.0f);
	}));

	this->runAction(ani);
}

void Dialog::endAnimation()
{
	//�����ش�������
	dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(0.0f);
	
	//y���1��С��0
	auto ani = Sequence::createWithTwoActions(ScaleTo::create(0.4f, 1.0f, 0.0f), CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}

void Dialog::setContentColor(cocos2d::Color4B color)
{
	_content->setTextColor(color);
}

void Dialog::setCanceBtnlDisplay(bool isDisplay)
{
	_btnClose->setVisible(isDisplay);
}

void Dialog::setContent(const std::string & content)
{
	_content->setString(content);
}

void Dialog::setFontSize(int contentTextSize)
{
	_content->setFontSize(contentTextSize);
}

void Dialog::setTitle(const std::string & title)
{
	_title->setString(title);
}

void Dialog::setBtnOkCallBack(std::function<void(cocos2d::Ref*pSender)> func)
{
	_btnOk->addTouchEventListener([&, func](Ref*pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			//�����Ч
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			func(this);

			endAnimation();
		}
	});
}

void Dialog::initDialog(const std::string & title, const std::string & content, std::function<void(cocos2d::Ref*pSender)> func)
{
	setTitle(title);
	setContent(content);
	setBtnOkCallBack(func);
}

void Dialog::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//���öԻ����λ������Ļ����
	node->setAnchorPoint(Point::ANCHOR_MIDDLE);
	node->setPosition(visibleSize / 2);
	addChild(node);

	//Ѱ�ҿؼ�
	_btnOk = node->getChildByName<Button*>(btnOkName);
	_btnClose = node->getChildByName<Button*>(btnCloseName);
	_title = node->getChildByName<Text*>(titleName);
	_content = node->getChildByName<Text*>(contentName);

	//���¼�����
	_btnClose->addTouchEventListener([&](Ref* pSendsr, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			endAnimation();
		}

	});
}

void Dialog::onEnterTransitionDidFinish()
{
	startAnimation();
}
