/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	HeroInfoLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/22
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "HeroInfoLayer.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "Config.h"
#include "GameData.h"
#include "BlockLayer.h"
#include "Tools.h"
#include "HeroCard.h"

USING_NS_CC;
using namespace ui;
using namespace std;

HeroInfoLayer::HeroInfoLayer()
{
	initArrayToNulptr();
}

HeroInfoLayer::~HeroInfoLayer()
{
	//��ΪText�������ü����������ڲ���Ҫ��ʱ���ÿ�
	initArrayToNulptr();
}

bool HeroInfoLayer::init()
{
	if (!Layer::init())
	{
		return true;
	}

	//����������
	auto blockLayer = BlockLayer::create();
	blockLayer->setName(blockTagName);
	addChild(blockLayer);

	loadUI();

	return true;
}

void HeroInfoLayer::initWithHerotype(const int type, HeroType heroType)
{
	if (heroType == HT_GAMEDATA)
	{
		//��ʾConfig��ģ��Ӣ������
		auto hero = GameData::getInstance()->getHeroCardById(type)->getProperty();
		setAttribute(hero);
	}
	else
	{
		//��ʾGameData����һ�õ�Ӣ������
		auto hero = Config::getInstance()->getHeroCardByIndex(type);
		setAttribute(hero);
	}
}

void HeroInfoLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_scrollView = node->getChildByTag<ScrollView*>(scrollViewTag);
	_btnClose = node->getChildByTag<Button*>(btnCloseTag);
	_heroImg = dynamic_cast<ImageView*>(_scrollView->getChildByTag(heroImgTag));

	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		_textList[index] = dynamic_cast<Text*>(_scrollView->getChildByTag(index));
	}

	//�رհ�ť�ص�
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

void HeroInfoLayer::setAttribute(const HeroCardType * hero)
{
	//������ʾ������
	string name = StringUtils::format("%s|%s", hero->exName.c_str(), hero->name.c_str());
	_heroImg->loadTexture(hero->textureName);
	setString(TT_NAME, name);
	setString(TT_STARNAME, hero->starName);
	setString(TT_HP, hero->hp);
	setString(TT_AP, hero->ap);
	setString(TT_MP, hero->mp);
	setString(TT_CRIT, StringUtils::format("%d%%", hero->critRate));
	setString(TT_BLOCK, StringUtils::format("%d%%", hero->blockRate));
	setString(TT_SPEED, hero->speed);
	setString(TT_DEFIME, hero->defend);
	setString(TT_MDEFIME, hero->magicDefend);
	setString(TT_CRITDMG, StringUtils::format("%d%%", hero->critDamage));
	setString(TT_SKILL, hero->skillName);
	setString(TT_CONTENT, hero->des);
}

void HeroInfoLayer::setAttribute(const HeroCardProperty * hero)
{
	//������ʾ������
	string name = StringUtils::format("Lv%d %s+%d", hero->level, hero->name->c_str(), hero->exLevel);
	_heroImg->loadTexture(*(hero->textureName));
	setString(TT_NAME, name);
	setString(TT_STARNAME, *(hero->starName));
	setString(TT_HP, hero->hp);
	setString(TT_AP, hero->ap);
	setString(TT_MP, hero->mp);
	setString(TT_CRIT, StringUtils::format("%d%%", hero->critRate));
	setString(TT_BLOCK, StringUtils::format("%d%%", hero->blockRate));
	setString(TT_SPEED, hero->speed);
	setString(TT_DEFIME, hero->defend);
	setString(TT_MDEFIME, hero->magicDefend);
	setString(TT_CRITDMG, StringUtils::format("%d%%", hero->critDamage));
	setString(TT_SKILL, *(hero->skillName));
	setString(TT_CONTENT, *(hero->des));
}

void HeroInfoLayer::setString(TextType type, const string & str)
{
	_textList[(int)type]->setString(str);
}

void HeroInfoLayer::setString(TextType type, int num)
{
	_textList[(int)type]->setString(StringUtils::format("%d", num));
}

void HeroInfoLayer::initArrayToNulptr()
{
	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		_textList[index] = nullptr;
	}
}

void HeroInfoLayer::onEnter()
{
	Layer::onEnter();

	startAnimation();
}

void HeroInfoLayer::startAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//����λ������Ļ����
	this->setPosition(visibleSize.width, 0);

	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(0, 0)), 0.2f);

	//���ƶ���ɺ���ʾ����������
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		//��ʾ����������
		dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(160.0f);
	}));

	this->runAction(ani);
}

void HeroInfoLayer::endAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�����ش�������
	dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(0.0f);

	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(visibleSize.width, 0)), 0.2f);

	//������ƶ����ͷ���Դ
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}
