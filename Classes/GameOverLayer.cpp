/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	GameOverLayer.cpp
// Author:		 Metoor
// Version: 	1.0
// Date: 		2016/12/02
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "GameOverLayer.h"
#include "cocostudio/CocoStudio.h"
#include "BlockLayer.h"
#include "GameData.h"
#include "I18N.h"
#include "AudioManager.h"
#include "Equipment.h"
#include "HeroCard.h"
#include "Tools.h"

USING_NS_CC;
using namespace ui;
using namespace std;

GameOverLayer::GameOverLayer()
{
}

GameOverLayer::~GameOverLayer()
{
}

bool GameOverLayer::init()
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

void GameOverLayer::initLayer(bool isWin, ExtraRewardType rewardType, int type, int gold, int exp)
{
	_rewardType = rewardType;
	_type = type;
	_gold = gold;
	_exp = exp;
	_isWin = isWin;
	
	if (isWin)
	{
		win();
	}
	else
	{
		failed();
	}
}

void GameOverLayer::failed()
{
	_goldLabel->setString("");
	_expLabel->setString("");

	//��ʾ��սʧ��ͼƬ
	_ico->loadTexture(fail_tt, Widget::TextureResType::PLIST);
	_ico->setContentSize(Size(310, 80));
	_icoBg->setVisible(false);

	//��˸��Ч
	auto blink = Blink::create(65535.0f, 65535);
	_ico->runAction(blink);
}

void GameOverLayer::win()
{
	auto i18n = I18N::getInstance();

	//��ʾ��þ���ͽ��
	_goldLabel->setString(StringUtils::format(i18n->getStringByKey(rewardGold).c_str(), _gold));
	_expLabel->setString(StringUtils::format(i18n->getStringByKey(rewardExp).c_str(), _exp));

	string texture = createExtraReward();

	if (!texture.empty())
	{
		//��ʾ���⽱��ͼ��
		_ico->loadTexture(texture, Widget::TextureResType::PLIST);
		_ico->setContentSize(Size(135, 135));
		_icoBg->setVisible(true);
	}
	else
	{
		//��ʾս����ʤ��ͼƬ
		_ico->loadTexture(win_tt, Widget::TextureResType::PLIST);
		_ico->setContentSize(Size(310, 80));
		_icoBg->setVisible(false);
	}

	//��˸��Ч
	auto blink = Blink::create(65535.0f, 65535);
	_ico->runAction(blink);
}

void GameOverLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_ico = node->getChildByName<ImageView*>(icoName);
	_icoBg = node->getChildByName<ImageView*>(icoBgName);
	_expLabel = node->getChildByName<Text*>(expName);
	_goldLabel = node->getChildByName<Text*>(goldName);
	_btnOk = node->getChildByName<Button*>(btnOkName);

	_btnOk->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::BEGAN == type)
		{
			if (_isWin)
			{
				//ʤ����ť�����Ч
				AudioManager::getInstance()->playGetGoldEffect();
			}
			else
			{
				//ʧ�ܰ�ť�����Ч
				AudioManager::getInstance()->playClickEffect();
			}
			
		}

		if (Widget::TouchEventType::ENDED == type)
		{
			endAnimation();
		}
	});
}

string GameOverLayer::createExtraReward()
{
	string texture = "";
	auto data = GameData::getInstance();

	int randomNum = Tools::getRandomInt(1, 100);

	//��һ���ĸ��ʻ�����������
	if (randomNum < extraRewardProbability)
	{
		if (_rewardType == ERT_CARD)
		{
			auto hero = new HeroCard();
			hero->init(_type);
			data->addHeroCardToMap(hero);
			texture = StringUtils::format("head%d.png", _type);
		}
		else if (_rewardType == ERT_EQUIPMENT)
		{
			auto equipment = new Equipment();
			equipment->init(_type);
			data->addEquipmentToMap(equipment);
			texture = *(equipment->getProperty()->textureName);
		}
	}

	data->setGold(_gold);
	data->setExp(_exp);

	return texture;
}

void GameOverLayer::onEnter()
{
	Layer::onEnter();

	//ֹͣս������
	AudioManager::getInstance()->stopBackgroundMusic();
	
	//��Ϸ������Ч
	AudioManager::getInstance()->playGameOverEffect(_isWin);
	
	startAnimation();
}

void GameOverLayer::startAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//����λ������Ļ����
	this->setPosition(-visibleSize.width, 0);

	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(0, 0)), 0.2f);

	//���ƶ���ɺ���ʾ����������
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		//��ʾ����������
		dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(bl_opacity_on);
	}));

	this->runAction(ani);
}

void GameOverLayer::endAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�����ش�������
	dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(bl_opacity_off);

	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(visibleSize.width, 0)), 0.2f);

	//������ƶ����ͷ���Դ
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->popScene();
	}));

	this->runAction(ani);
}
