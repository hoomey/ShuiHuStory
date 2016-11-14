/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	LevelupRewardLayer.cpp
// Author:		 Metoor
// Version: 	1.0
// Date: 		2016/11/11
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "LevelupRewardLayer.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "BlockLayer.h"
#include "GameData.h"
#include "LevelupRewardItem.h"
#include "DialogManager.h"
#include "I18N.h"

USING_NS_CC;
using namespace ui;
using namespace std;

LevelupRewardLayer::LevelupRewardLayer()
{
	readData();
}

LevelupRewardLayer::~LevelupRewardLayer()
{
	saveData();
}

bool LevelupRewardLayer::init()
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

void LevelupRewardLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_btnClose = node->getChildByName<Button*>(btnCloseName);
	_listView = node->getChildByName<ListView*>(listViewName);

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
}

void LevelupRewardLayer::loadItem()
{
	for (int pos = 0; pos < itemCount; ++pos)
	{

		if (_isGetGift[pos])
		{
			//����Ѿ���ȡ���ˣ����ٴ���
			continue;
		}

		auto item = LevelupRewardItem::create();

		//���㽱����Ϣ
		int index = pos + 1;
		int level = item_level_base + index * item_level_increaseNum;
		int gold = gift_base_diamond + index * item_gold_increaseNum;
		int diamond = gift_base_diamond + index * item_diamond_increaseNum;

		//�����ǰ�ȼ�С����ȡҪ���������ȡ��ť
		if (GameData::getInstance()->getLevel() < level)
		{
			item->setBtnEnable(false);
		}

		//����item��ʾ����
		item->setRewardString(level, diamond, gold);
		item->setBtnCallback([&, pos, level, gold, diamond](Ref* pSender) {
			int tag = dynamic_cast<Button*>(pSender)->getTag();

			//��¼�û���ȡ���
			_isGetGift[pos] = true;

			//��ý���
			auto data = GameData::getInstance();
			data->setGold(gold);
			data->setDiamond(diamond);
			dynamic_cast<LevelupRewardItem*>(_listView->getItem(pos))->setBtnEnable(false);
			
			//֪ͨ�����û�����
			_eventDispatcher->dispatchCustomEvent(msg_update_user_data);

			//��ʾ��ʾ
			DialogManager::getInstance()->showTips(StringUtils::format(I18N::getInstance()->getStringByKey(loginRewardTips).c_str(), gold, diamond), Color4B::GREEN);
		});


		_listView->pushBackCustomItem(item);
	}
}

void LevelupRewardLayer::readData()
{
	for (int pos = 0; pos < itemCount; ++pos)
	{
		_isGetGift[pos] = UserDefault::getInstance()->getBoolForKey(StringUtils::format(is_get_gift_key.c_str(), pos).c_str(), false);
	}
}

void LevelupRewardLayer::saveData()
{
	for (int pos = 0; pos < itemCount; ++pos)
	{
		UserDefault::getInstance()->setBoolForKey(StringUtils::format(is_get_gift_key.c_str(), pos).c_str(), _isGetGift[pos]);
	}
}

void LevelupRewardLayer::startAnimation()
{
	//y���0���ӵ�1
	setScaleY(0.0f);

	auto ani = Sequence::createWithTwoActions(ScaleTo::create(0.4f, 1.0f), CallFunc::create([&]() {
		//��ʾ����������
		dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(160.0f);
	}));

	this->runAction(ani);
}

void LevelupRewardLayer::endAnimation()
{
	//�����ش�������
	dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(0.0f);

	//y���1��С��0
	auto ani = Sequence::createWithTwoActions(ScaleTo::create(0.4f, 1.0f, 0.0f), CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}

void LevelupRewardLayer::onEnterTransitionDidFinish()
{
	loadItem();
	startAnimation();
}
