/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	EquipmentDisplayLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "EquipmentDisplayLayer.h"
#include "cocostudio/CocoStudio.h"
#include "GameData.h"
#include "BlockLayer.h"
#include "Tools.h"
#include "Equipment.h"
#include "AudioManager.h"
#include "ListItem.h"

USING_NS_CC;
using namespace ui;
using namespace std;

EquipmentDisplayLayer::EquipmentDisplayLayer()
	:_preClicked(none)
{
}

EquipmentDisplayLayer::~EquipmentDisplayLayer()
{
}

bool EquipmentDisplayLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//�������Σ���ֹ��͸�������һ��
	auto blockLayer = BlockLayer::create();
	blockLayer->setName(blockName);
	addChild(blockLayer);

	loadUI();

	//��ʼ��Item
	auto equipment = GameData::getInstance()->getEquipmentMap();
	loadItem(equipment->size());

	return true;
}

void EquipmentDisplayLayer::onEnterTransitionDidFinish()
{
	startAnimation();
}

void EquipmentDisplayLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	//���ҿؼ�
	_listView = node->getChildByName<ListView*>(listViewName);
	_btnClose = node->getChildByName<Button*>(btnCloseName);
	_tipLabel = node->getChildByName<Text*>(tipLabelName);

	//���¼��ص�
	_btnClose->addTouchEventListener(CC_CALLBACK_2(EquipmentDisplayLayer::btnCloseCallBack, this));
}

void EquipmentDisplayLayer::setTipLabel()
{
	_tipLabel->setString(StringUtils::format("%d/%d", _itemVector.size(), equipment_map_max_size));
}

void EquipmentDisplayLayer::setItemAttribute(const EquipmentProperty * property, ListItem* item)
{
	//�����ı���ǩ
	item->setLabelText(LEVEL, StringUtils::format("Lv:%d", property->level));
	item->setLabelText(NAME, *(property->name));
	item->setStarNum(property->star);

	//������ɫ
	setItemColor(item, property->star);

	int type = property->type;

	if (Tools::betweenAnd(type, 100, 108))
	{
		//ñ��
		item->setIco(*(property->textureName), defineIco, mDefineIco);

		item->setLabelText(TEXT1, StringUtils::format("%d", property->defend));
		item->setLabelText(TEXT2, StringUtils::format("%d", property->magicDefend));
	}
	else if (Tools::betweenAnd(type, 200, 207))
	{
		//�·�
		item->setIco(*(property->textureName), defineIco, mDefineIco);

		item->setLabelText(TEXT1, StringUtils::format("%d", property->defend));
		item->setLabelText(TEXT2, StringUtils::format("%d", property->magicDefend));
	}
	else if (Tools::betweenAnd(type, 300, 324))
	{
		//����
		item->setIco(*(property->textureName), apIco, mpIco);

		item->setLabelText(TEXT1, StringUtils::format("%d", property->ap));
		item->setLabelText(TEXT2, StringUtils::format("%d", property->mp));
	}
	else if (Tools::betweenAnd(type, 400, 405))
	{
		//���
		item->setIco(*(property->textureName), hpIco, critIco);

		item->setLabelText(TEXT1, StringUtils::format("%d", property->hp));
		item->setLabelText(TEXT2, StringUtils::format("%d%%", Tools::percentToInt(property->critDamage)));
	}
	else if (Tools::betweenAnd(type, 500, 504))
	{
		//Ь��
		item->setIco(*(property->textureName), speedIco, blockIco);

		item->setLabelText(TEXT1, StringUtils::format("%d", property->speed));
		item->setLabelText(TEXT2, StringUtils::format("%d%%", Tools::percentToInt(property->blockRate)));
	}
	else if (Tools::betweenAnd(type, 600, 604))
	{
		//����
		item->setIco(*(property->textureName), hpIco, speedIco);

		item->setLabelText(TEXT1, StringUtils::format("%d", property->hp));
		item->setLabelText(TEXT2, StringUtils::format("%d", property->speed));
	}
}

void EquipmentDisplayLayer::updateItemAttribute(const int equipmentId, const int itenId)
{
	auto equipment = GameData::getInstance()->getEquipmentById(equipmentId);
	
	//���µ���item������
	setItemAttribute(equipment->getProperty(), _itemVector.at(itenId));
}

void EquipmentDisplayLayer::loadItem(int n)
{
	auto equipmentMap = GameData::getInstance()->getEquipmentMap();

	//��ʼ���ص�����
	int startIndex = _itemVector.size();
	//������������ʵ�ʼ��ص�endIndex - 1
	int endIndex = startIndex + n;
	//��ǰ������
	int index = 0;

	for (auto iter = equipmentMap->begin(); iter != equipmentMap->end(); ++iter)
	{
		if (Tools::betweenAnd(index, startIndex, endIndex - 1) && static_cast<unsigned>(startIndex) < equipmentMap->size())
		{
			auto item = ListItem::create();
			
			//����item��ʾ������
			auto property = (iter->second)->getProperty();
			setItemAttribute(property, item);
			item->setBtnTexture(btnDetails1, btnDetails2);
			item->setBtnTag(index);
			item->setBtnCallBack([&](Ref* pSender, Widget::TouchEventType type) { 
				if(type == Widget::TouchEventType::ENDED)
				{
					int tag = dynamic_cast<Button*>(pSender)->getTag();

					log("----%d", tag);
				}
			});
			
			//��ӵ�listView��itemVector
			_listView->pushBackCustomItem(item);
			_itemVector.pushBack(item);

		}
		else if (static_cast<unsigned>(startIndex) >= equipmentMap->size() || index >= endIndex)
		{
			//�����ǰ�������Ѿ�������Ҫ���ص�����������������е�item�Ѿ�ȫ�����������ѭ��
			break;
		}

		++index;
	}

	//�����б��ϱ�����ʹ����Ϣ
	setTipLabel();
}

void EquipmentDisplayLayer::setItemColor(ListItem * item, int star)
{
	Color4B color;

	//������ɫ
	switch (star)
	{
	case 1:
		color = Color4B::WHITE;
		break;
	case 2:
		color = Color4B::BLUE;
		break;
	case 3:
		color = Color4B::GREEN;
		break;
	case 4:
		color = Color4B(255, 0, 255, 255);
		break;
	case 5:
		color = Color4B(255, 102, 0, 255);
		break;
	default:
		break;
	}

	for (int i = 0; i < 4; ++i)
	{
		item->setLabelColor(static_cast<ItemLabelType>(i), color);
	}
}

void EquipmentDisplayLayer::btnCloseCallBack(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		//�����Ч
		AudioManager::getInstance()->playClickEffect();

		endAnimation();
	}
}

void EquipmentDisplayLayer::startAnimation()
{
	//��ʼΪ0
	this->setScale(0.0f);

	auto ani = Sequence::createWithTwoActions(Spawn::createWithTwoActions(ScaleTo::create(0.5f, 1.0f), RotateTo::create(0.5f, 720)), CallFunc::create([&]() {
		//��ʾ����������
		this->getChildByName(blockName)->setOpacity(150);
	}));

	this->runAction(ani);
}

void EquipmentDisplayLayer::endAnimation()
{
	//���ش������β�
	this->getChildByName(blockName)->setOpacity(0.0f);

	auto ani = Sequence::createWithTwoActions(Spawn::createWithTwoActions(ScaleTo::create(0.5f, 0.0f), RotateTo::create(0.5f, 720)), CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}
