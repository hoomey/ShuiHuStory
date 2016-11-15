/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	TeamLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/14
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "TeamLayer.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "GameData.h"
#include "HeroCard.h"
#include "DisplayLayer.h"
#include "AudioManager.h"
#include "DisplayListItem.h"
#include "DialogManager.h"
#include "I18N.h"

USING_NS_CC;
using namespace ui;
using namespace std;

TeamLayer::TeamLayer()
	:_selectTag(none),
	_displayLayer(nullptr)
{
}

TeamLayer::~TeamLayer()
{
}

bool TeamLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	loadUI();

	addTouchEventListener();

	updateData();

	return true;
}

void TeamLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);
	
	for (int index = 0; index < max_battle_hero_num; ++index)
	{
		_nameLabel[index] = node->getChildByName<Text*>(StringUtils::format(nameLabel.c_str(), index));
		_heroIco[index] = node->getChildByName<Sprite*>(StringUtils::format(heroIcoSprite.c_str(), index));
	}
}

void TeamLayer::updateData()
{
	auto battleArray = GameData::getInstance()->getBattleHeroArray();

	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		int id = battleArray[pos];
		
		if (id < init_unique_num)
		{
			//���id == -1�� ��ʾ��λ��û��Ӣ��,��ʾĬ��ͼƬ
			if (id == -1)
			{
				_heroIco[pos]->setSpriteFrame(addIco);
				_nameLabel[pos]->setString("");
			}
		}
		else
		{
			//��ø�λ���ϵ�Ӣ����Ϣ
			auto property = GameData::getInstance()->getHeroCardById(id)->getProperty();

			string icoName = StringUtils::format(heroName.c_str(), property->type);
			
			//������ʾͷ��
			_heroIco[pos]->setSpriteFrame(icoName);
			//������ʾ������
			_nameLabel[pos]->setString(*(property->name));
		}
	}
}

void TeamLayer::setUnBattleBtn()
{
	auto objIdVector = _displayLayer->getObjectIdVector();

	for (unsigned int index = 0; index < objIdVector->size(); ++index)
	{
		int id = objIdVector->at(index);
		
		if (GameData::getInstance()->isBattleHero(id))
		{
			//���Ӣ���Ѿ������ˣ��򻻳�����ťͼƬ
			auto item = _displayLayer->getObjectItemByIndex(index);
			item->setBtnTexture(btnUnbattleHero1, btnUnbattleHero2);
		}
	}
}

int TeamLayer::getHeroIcoisContainPoint(cocos2d::Point & point)
{
	int result = none;

	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		auto sp = _heroIco[pos];

		//��������κ�һ��Ӣ��ͼ�����棬�򷵻����ڵı�ǩ
		if(sp->getBoundingBox().containsPoint(point))
		{
			int tag = sp->getTag();
			
			//�ж�ѡ�е��ǲ����Լ�
			if (tag != _selectTag)
			{
				result = tag;
				break;
			}
			else
			{
				//������Լ�������Լ������²���
				continue;
			}
		}
	}

	return result;
}

void TeamLayer::addTouchEventListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TeamLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TeamLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TeamLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool TeamLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	Point touchPos = touch->getLocation();

	_selectTag = getHeroIcoisContainPoint(touchPos);

	if (_selectTag < 0)
	{
		//���û��ѡ��Ӣ��ͼ�꣬����Ա��δ���������ִ�к�������
		return false;
	}

	//ѡ�к���С����
	_heroIco[_selectTag]->setScale(0.8f);
	_nameLabel[_selectTag]->setScale(0.8f);

	//����Ӣ��ͼ������ֵ�z˳�򣬷�ֹ���ڵ�
	_heroIco[_selectTag]->setLocalZOrder(select_z_order);
	_nameLabel[_selectTag]->setLocalZOrder(select_z_order);

	return true;
}

void TeamLayer::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	Point pos = touch->getLocation();

	//�ƶ�Ӣ��ͼ���Ӣ������
	_heroIco[_selectTag]->setPosition(pos);
	_nameLabel[_selectTag]->setPosition(pos - distanceNameToIco);
}

void TeamLayer::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	Point pos = touch->getLocation();
	float distance = pos.distance(touch->getStartLocation());

	//����ƶ��ľ���С��5.0f������ƶ�,��Ϊ�ǵ���¼�
	if (distance > 5.0f)
	{
		//����Ӣ��λ��
		int endTag = getHeroIcoisContainPoint(pos);

		if (endTag < 0)
		{
			//�ƶ���������ԭ��С
			_heroIco[_selectTag]->setScale(1.0f);
			_nameLabel[_selectTag]->setScale(1.0f);

			//��ק������λ�÷Ƿ����Ż�ԭ����λ��
			_heroIco[_selectTag]->setPosition(HeroIcoPos[_selectTag]);
			_nameLabel[_selectTag]->setPosition(HeroNamePos[_selectTag]);
		}
		else
		{
			//����λ�óɹ�,����ק��Ӣ��ͼ�����õ��µ�λ��
			_heroIco[_selectTag]->setPosition(HeroIcoPos[endTag]);
			_nameLabel[_selectTag]->setPosition(HeroNamePos[endTag]);

			//������λ�õ�Ӣ�۷ŵ���קӢ�۵�ԭʼλ��
			_heroIco[endTag]->setPosition(HeroIcoPos[_selectTag]);
			_nameLabel[endTag]->setPosition(HeroNamePos[_selectTag]);

			//�ƶ���������ԭ��С
			_heroIco[_selectTag]->setScale(1.0f);
			_nameLabel[_selectTag]->setScale(1.0f);
			
			//���������ָ������
			auto sp = _heroIco[_selectTag];
			_heroIco[_selectTag] = _heroIco[endTag];
			_heroIco[endTag] = sp;

			//�������ֵ�ָ������
			auto lb = _nameLabel[_selectTag];
			_nameLabel[_selectTag] = _nameLabel[endTag];
			_nameLabel[endTag] = lb;

			//����Ӣ�۵ı�ǩ
			_heroIco[_selectTag]->setTag(_selectTag);
			_heroIco[endTag]->setTag(endTag);

			//������ս���������λ��
			auto battleArray = GameData::getInstance()->getBattleHeroArray();
			int id = battleArray[_selectTag];
			battleArray[_selectTag] = battleArray[endTag];
			battleArray[endTag] = id;

		}

	}
	else
	{
		//���ŵ����Ч
		AudioManager::getInstance()->playClickEffect();

		//����Ӣ�ۣ���һ���ǽ��ƶ�����Ӣ�۸�λ
		_heroIco[_selectTag]->setPosition(HeroIcoPos[_selectTag]);
		_nameLabel[_selectTag]->setPosition(HeroNamePos[_selectTag]);

		//�ƶ���������ԭ��С
		_heroIco[_selectTag]->setScale(1.0f);
		_nameLabel[_selectTag]->setScale(1.0f);

		//����Ӣ����ʾ�б��
		_displayLayer = DisplayLayer::create();
		_displayLayer->setDisplayType(OT_HERO);

		_displayLayer->setBtnTexture(btnBattleHero1, btnBattlehero2);

		int selectTag = _selectTag;

		_displayLayer->setBtnCallBack([&, selectTag](Ref* pSender) {
			
			auto btn = dynamic_cast<Button*>(pSender);
			int tag = btn->getTag();
			auto data = GameData::getInstance();

			//ȡ��ѡ��Ӣ�۵�Id
			int id = _displayLayer->getObjectIdByIndex(tag);
			auto item = _displayLayer->getObjectItemByIndex(tag);

			if (data->isBattleHero(id))
			{
				//�����ǰֻ��һ��Ӣ�ۣ�����������(��Ҫ��֤������һ��Ӣ������)
				if (data->getBattleHeroNum() < 2)
				{
					//��ʾ����
					DialogManager::getInstance()->showTips(I18N::getInstance()->getStringByKey(atleastOneHero), Color4B::RED);
				}
				else
				{
					//Ӣ���Ѿ�������������������
					data->unbattleHero(id);

					//������İ�ť����������ť
					item->setBtnTexture(btnBattleHero1, btnBattlehero2);
					
					//��ʾ����
					DialogManager::getInstance()->showTips(I18N::getInstance()->getStringByKey(battleSuc), Color4B::GREEN);
					
					//��������
					updateData();

					//�ر��б��
					_displayLayer->endAnimation();
				}
			}
			else
			{
				//Ӣ��û��������������������
				data->setBattleHero(selectTag, id);

				//������İ�ť����������ť
				item->setBtnTexture(btnUnbattleHero1, btnUnbattleHero2);

				//��ʾ����
				DialogManager::getInstance()->showTips(I18N::getInstance()->getStringByKey(unbattleSuc), Color4B::GREEN);
				
				//��������
				updateData();

				//�ر��б��
				_displayLayer->endAnimation();
			}

		});

		addChild(_displayLayer);
		
		setUnBattleBtn();
	}

	//�ƶ���ϣ�����Ӣ��ͼ������ֵ�z˳��ΪĬ��ֵ
	_heroIco[_selectTag]->setLocalZOrder(default_z_order);
	_nameLabel[_selectTag]->setLocalZOrder(default_z_order);

	//ȡ��ѡ����
	_selectTag = none;
}