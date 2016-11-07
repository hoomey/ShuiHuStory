/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	DialogManager.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "DialogManager.h"
#include "McLog.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "BlockLayer.h"
#include "TypeStruct.h"

DialogManager* DialogManager::_instance = nullptr;

USING_NS_CC;


DialogManager::DialogManager()
{
}

cocos2d::Node * DialogManager::createTip(const std::string* text, cocos2d::Color4B color, int size)
{
	//��ȡcocos stuido�༭�õ�ui�ļ�
	auto tipLayer = (CSLoader::createNode(csbName_TipLayer));

	//��ȡ��ʾ�ı����ݵ�Text�ؼ�
	auto label = tipLayer->getChildByName<ui::Text*>("text");

	Size visibleSize = Director::getInstance()->getVisibleSize();

	label->setString(*text);
	label->setTextColor(color);
	label->setFontSize(size);
	tipLayer->setAnchorPoint(Point::ANCHOR_MIDDLE);
	tipLayer->setPosition(visibleSize.width / 2, visibleSize.height / 1.2f);
	
	return tipLayer;
}

DialogManager::~DialogManager()
{
}

DialogManager * DialogManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new (std::nothrow)DialogManager();

		if (!_instance)
		{
			//������־��¼
			McLog mLog;
			mLog.addError("_instance create failed...", __FILE__, __LINE__);
		}
	}

	return _instance;
}

void DialogManager::showTip(const std::string* text, float second, cocos2d::Color4B color, int size)
{
	auto currentScene = Director::getInstance()->getRunningScene();
	
	//�����ǰ�������Ѿ������һ����ʾ�������ظ�����
	if (!currentScene->getChildByName("tip"))
	{
		auto tip = createTip(text, color, size);
		tip->setName("tip");
		tip->setOpacity(0);
		currentScene->addChild(tip, tip_z_order);

		auto animate = Sequence::create(FadeIn::create(1.0f), DelayTime::create(3.5f), FadeOut::create(1.0f), CallFunc::create([]() {
			auto tip = Director::getInstance()->getRunningScene()->getChildByName("tip");
			
			//�ӵ�ǰ�����Ƴ���ʾ�򣬲�������Դ
			tip->removeFromParentAndCleanup(true);
		}), NULL);

		tip->runAction(animate);
	}
	
}

void DialogManager::destoryInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}
