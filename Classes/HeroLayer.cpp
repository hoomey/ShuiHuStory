/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	HeroLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/18
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "HeroLayer.h"
#include "cocostudio/CocoStudio.h"
#include "BlockLayer.h"
#include "GameData.h"
#include "AudioManager.h"
#include "PageViewItem.h"
#include "DisplayEquipmentByType.h"
#include "HeroCard.h"
#include "Equipment.h"
#include "DetailsLayer.h"
#include "McLog.h"
#include "DisplayLayer.h"
#include "DisplayListItem.h"
#include "DialogManager.h"
#include "I18N.h"

USING_NS_CC;
using namespace ui;
using namespace std;

HeroLayer::HeroLayer()
{
	//��ʼ������
	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		_itemId[pos] = none;
	}
}

HeroLayer::~HeroLayer()
{
}

bool HeroLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//���ɵ���¼�
	auto blockLayer = BlockLayer::create();
	blockLayer->setName(blockTagName);
	addChild(blockLayer);

	loadUI();

	addEquipmentUpateEventListener();
	addHeroUpateEventListener();

	return true;
}

void HeroLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_pageView = node->getChildByName<PageView*>(pageViewName);
	_btnChange = node->getChildByName<Button*>(btnChangeName);
	_btnDetails = node->getChildByName<Button*>(btnDetailsName);

	//�󶨵���ص�
	_btnChange->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			//��������ѡ���Ӣ���б�
			auto layer = DisplayLayer::create();
			layer->setTag(displayLayerTag);
			layer->setDisplayType(OT_HERO);
			layer->setBtnCallBack([&](Ref* pSender) {
				int pos = _pageView->getCurrentPageIndex();
				int currentId = _itemId[pos];

				auto btn = dynamic_cast<Button*>(pSender);
				int id = (int)btn->getUserData();
				auto data = GameData::getInstance();

				//���Ѿ������Ӣ��װ���������������Ӣ��
				auto currentHero = data->getHeroCardById(currentId);
				//���������Ӣ��
				auto hero = data->getHeroCardById(id);

				for (int pos = 0; pos < max_equipment_num; ++pos)
				{
					int currentEquipmentId = currentHero->getEquipmentByPos(pos);
					
					if (currentEquipmentId != none)
					{
						auto equipment = data->getEquipmentById(currentEquipmentId);

						//����ǰװ����ʹ��������Ϊ���������Ӣ��
						equipment->setUserId(id);
						hero->wearEquipment(pos, currentEquipmentId);
						currentHero->wearEquipment(pos, none);
					}
				}

				//���³�ս�б��Ӣ��Id
				int heroPos = data->getPosById(currentId);

				if (heroPos != none)
				{
					//����ǰλ�õ�Ӣ������
					data->setBattleHero(heroPos, id);
					
					//���±���pageview��item��id
					_itemId[heroPos] = id;
				}

				//�����ɹ���ʾ
				DialogManager::getInstance()->showTips(I18N::getInstance()->getStringByKey(unbattleSuc), Color4B::GREEN);
				
				//���͸������ݵ���Ϣ
				_eventDispatcher->dispatchCustomEvent(msg_update_hero_pageview_item, (void*)id);
				
				//ͨ��Tag��ȡ���б��ָ�룬Ȼ��ر��б�
				dynamic_cast<DisplayLayer*>(getChildByTag(displayLayerTag))->endAnimation();
			});
			addChild(layer);

			setEnableBtn(layer);
		}
	});

	_btnDetails->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			int pos = _pageView->getCurrentPageIndex();
			int id = _itemId[pos];

			if (id != none)
			{
				//id��Ч��������ϸ���Խ���
				auto layer = DetailsLayer::create();
				layer->initUiWithId(id, DT_HERO);
				addChild(layer);
			}
			else
			{
				McLog mc;
				mc.addWaring("'id' value is error...", __FILE__, __LINE__);
			}
			
		}
	});

}

void HeroLayer::loadItem()
{
	int itemIndex = 0;

	auto data = GameData::getInstance();

	auto battleHero = data->getBattleHeroArray();

	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		int id = battleHero[pos];
		
		if (id != none)
		{
			auto item = PageViewItem::create();
			item->initWithHeroId(id);

			//����pageview��װ��itemѡ�лص�
			item->setBtnCallBack([&, pos, battleHero](Ref* pSender) {
				int heroId = battleHero[pos];
				auto btn = dynamic_cast<Button*>(pSender);
				int tag = btn->getTag();

				auto layer = DisplayEquipmentByType::create();
				layer->setDisPlayEquipmentType(ET(tag), heroId);

				//����listview��item��ť����¼�
				layer->setBtnCallBack([&, heroId](Ref* pSender, int equipmentPos, int equipmentId, bool isAdd) {
					
					auto data = GameData::getInstance();
					auto hero = data->getHeroCardById(heroId);

					//�����λ���Ѿ���װ�����Ƚ�����װ���Ƴ�
					int preEquipmentId = hero->getEquipmentByPos(equipmentPos);
					
					if (preEquipmentId != none)
					{
						auto equipment = data->getEquipmentById(preEquipmentId);
						equipment->setUserId(none);
					}

					if (isAdd)
					{
						//ΪӢ�����װ��
						auto curEquipment = data->getEquipmentById(equipmentId);
						curEquipment->setUserId(heroId);
						hero->wearEquipment(equipmentPos, equipmentId);	
					}
					else
					{
						//ж��Ӣ�۵�װ��
						hero->wearEquipment(equipmentPos, none);
					}
					
					hero->updatetePropery();
				});

				addChild(layer);
			});

			_pageView->addPage(item);
			_itemId[itemIndex++] = id;
		}
	}

	//����Ĭ����ʾ��ҳ��
	_pageView->setCurrentPageIndex(0);
}

void HeroLayer::setEnableBtn(DisplayLayer* display)
{
	auto objectVector = display->getObjectIdVector();
	auto data = GameData::getInstance();

	for (unsigned int index = 0; index < objectVector->size(); ++index)
	{
		int id = objectVector->at(index);
		auto item = display->getObjectItemByIndex(index);

		//�ж��Ƿ��Ѿ�������
		if (data->isBattleHero(id))
		{
			//Ӣ���Ѿ����󣬲����ڱ�ѡ������
			item->setBtnTexture(btnUnbattleHero1, btnUnbattleHero2);
			item->setBtnEnable(false);
		}
		else
		{
			//Ӣ��û��������������
			item->setBtnTexture(btnBattleHero1, btnBattleHero2);
		}
	}
}

void HeroLayer::addEquipmentUpateEventListener()
{
	//ע����������¼�
	auto listen = EventListenerCustom::create(msg_update_hero_pageview_item, CC_CALLBACK_1(HeroLayer::updateEnentListern, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
}

void HeroLayer::addHeroUpateEventListener()
{
	//ע����������¼�
	auto listen = EventListenerCustom::create(msg_update_display_item, CC_CALLBACK_1(HeroLayer::updateEnentListern, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
}

void HeroLayer::onEnterTransitionDidFinish()
{
	loadItem();
}

void HeroLayer::updateEnentListern(cocos2d::EventCustom* event)
{
	int id = (int)event->getUserData();

	int index = _pageView->getCurrentPageIndex();
	auto item = dynamic_cast<PageViewItem*>(_pageView->getItem(index));
	item->updateData();

	//ֻ���ڸ���Ӣ�۵�ʱ��ᴫ���������Id
	if (id > init_unique_num)
	{
		item->updateData(id);
	}
	else
	{
		item->updateData();
	}
}
