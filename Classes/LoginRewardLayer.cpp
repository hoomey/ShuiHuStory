/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	LoginRewardLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/11
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "LoginRewardLayer.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "BlockLayer.h"
#include "GameData.h"
#include "DialogManager.h"
#include "I18N.h"
#include "Tools.h"

USING_NS_CC;
using namespace ui;
using namespace std;

LoginRewardLayer::LoginRewardLayer()
{
}

LoginRewardLayer::~LoginRewardLayer()
{
}

bool LoginRewardLayer::init()
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

	initData();

	return true;
}

void LoginRewardLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_timeTips = node->getChildByName<Text*>(timeLabelName);
	_contentLabel = node->getChildByName<Text*>(contentLabelName);
	_btnOk = node->getChildByName<Button*>(btnOkName);
	_btnClose = node->getChildByName<Button*>(btnCloseName);

	//����
	_btnClose->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			endAnimation();
		}
	});

	_btnOk->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			//���Ż�ý����Ч
			AudioManager::getInstance()->playEffect(rewardGoldEffectName);
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			//���ð�ť
			_btnOk->setEnabled(false);
			//���汾����ȡ��ʱ��
			UserDefault::getInstance()->setIntegerForKey(preGetTime.c_str(), Tools::getCurrentTimeSecond());

			//��ý���
			auto data = GameData::getInstance();
			auto i18n = I18N::getInstance();

			int gold = login_gold_base * data->getLevel();
			int diamond = login_diamond_base * data->getLevel();
			data->setGold(gold);
			data->setDiamond(diamond);

			DialogManager::getInstance()->showTips(StringUtils::format(i18n->getStringByKey(loginRewardTips).c_str(), gold, diamond), Color4B::GREEN);
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(msg_update_user_data);
			endAnimation();
		}
	});
}

void LoginRewardLayer::initData()
{
	auto i18n = I18N::getInstance();
	auto data = GameData::getInstance();

	unsigned int currentTime = Tools::getCurrentTimeSecond();
	unsigned int preTime = UserDefault::getInstance()->getIntegerForKey(preGetTime.c_str(), 0);

	unsigned diffTime = Tools::maxInt(0, currentTime - preTime);

	//���Ҫ��ʾ������
	string s = StringUtils::format(i18n->getStringByKey(rewardGold).c_str(), data->getLevel() * login_gold_base);
	s += "\n\n";
	s += StringUtils::format(i18n->getStringByKey(rewardDiamond).c_str(), data->getLevel() * login_diamond_base);

	//���ý�������
	_contentLabel->setString(s);

	if (diffTime >= intervalTime)
	{
		//������ȡʱ�䣬�����ϴ�12Сʱ����
		_btnOk->setEnabled(true);
		_timeTips->setString(StringUtils::format(i18n->getStringByKey(loginRewardTimeTips2).c_str()));
	}
	else
	{
		//������ʱ��
		_remainTime = Tools::maxInt(0, intervalTime - diffTime);

		schedule(schedule_selector(LoginRewardLayer::updateTime), 1.0f);
		_btnOk->setEnabled(false);

	}
}

void LoginRewardLayer::startAnimation()
{
	//y���0���ӵ�1
	setScaleY(0.0f);

	auto ani = Sequence::createWithTwoActions(ScaleTo::create(0.4f, 1.0f), CallFunc::create([&]() {
		//��ʾ����������
		dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(160.0f);
	}));

	this->runAction(ani);
}

void LoginRewardLayer::endAnimation()
{
	//�����ش�������
	dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(0.0f);

	//y���1��С��0
	auto ani = Sequence::createWithTwoActions(ScaleTo::create(0.4f, 1.0f, 0.0f), CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}

void LoginRewardLayer::onEnterTransitionDidFinish()
{
	startAnimation();
}

void LoginRewardLayer::updateTime(float dt)
{
	auto i18n = I18N::getInstance();

	if (_remainTime <= 0)
	{
		//ȡ����ʱ��
		unschedule(schedule_selector(LoginRewardLayer::updateTime));

		//������ȡʱ�䣬�����ϴ�12Сʱ����
		_btnOk->setEnabled(true);
		_timeTips->setString(StringUtils::format(i18n->getStringByKey(loginRewardTimeTips2).c_str()));
	}
	else
	{
		_remainTime -= dt;

		//���㵹��ʱ
		int hour = _remainTime / 3600;
		int min = (_remainTime - hour *3600) /60;
		int sec = _remainTime - (hour * 3600 + min * 60);

		_timeTips->setString(StringUtils::format(i18n->getStringByKey(loginRewardTimeTips1).c_str(), hour, min, sec));
	}
}
