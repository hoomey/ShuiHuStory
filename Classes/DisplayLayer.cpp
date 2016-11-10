/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	DisplayLayer.cpp
// Author:		 Metoor
// Version: 	1.0
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "DisplayLayer.h"
#include "cocostudio/CocoStudio.h"
#include "GameData.h"
#include "BlockLayer.h"
#include "Tools.h"
#include "Equipment.h"
#include "HeroCard.h"
#include "AudioManager.h"
#include "DisplayListItem.h"

USING_NS_CC;
using namespace ui;
using namespace std;

DisplayLayer::DisplayLayer()
	:_clickedIndex(none),
	_func(nullptr),
	_type(OT_NONE),
	_isNeedUpadateUserData(false)
{
}

DisplayLayer::~DisplayLayer()
{
}

bool DisplayLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//�������Σ���ֹ��͸�������һ��
	auto blockLayer = BlockLayer::create();
	blockLayer->setName(blockTagName);
	addChild(blockLayer);

	loadUI();

	addUpdateDisplayItemEventListener();

	return true;
}

void DisplayLayer::addUpdateDisplayItemEventListener()
{
	//ע����������¼�
	auto listen = EventListenerCustom::create(msg_update_display_item, [&](EventCustom* event) {
		_isNeedUpadateUserData = true;
		updateItemAttribute();
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
}

void DisplayLayer::onEnterTransitionDidFinish()
{
	//��ʼ���б�
	load();

	startAnimation();
}

void DisplayLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	//���ҿؼ�
	_listView = node->getChildByName<ListView*>(listViewName);
	_btnClose = node->getChildByName<Button*>(btnCloseName);
	_tipLabel = node->getChildByName<Text*>(tipLabelName);

	//���¼��ص�
	_btnClose->addTouchEventListener(CC_CALLBACK_2(DisplayLayer::btnCloseCallBack, this));
}

void DisplayLayer::load()
{
	CCAssert(_type != OT_NONE, "please call setDisplayType(),before call this...");

	auto data = GameData::getInstance();

	switch (_type)
	{
	case OT_EQUIPMENT:
		loadItem(data->getEquipmentMap());
		break;
	case OT_HERO:
		loadItem(data->getHeroCardMap());
		break;
	default:
		break;
	}
}

void DisplayLayer::setTipLabel()
{
	switch (_type)
	{
	case OT_EQUIPMENT:
		_tipLabel->setString(StringUtils::format("%d/%d", _objectIdVector.size(), equipment_map_max_size));
		break;
	case OT_HERO:
		_tipLabel->setString(StringUtils::format("%d/%d", _objectIdVector.size(), hero_card_map_max_size));
		break;
	default:
		break;
	}

}

void DisplayLayer::setItemAttribute(const HeroCardProperty * property, DisplayListItem * item)
{
	//�����ı���ǩ
	item->setLabelText(ILT_LEVEL, StringUtils::format("Lv:%d", property->level));
	item->setLabelText(ILT_NAME, *(property->name));
	item->setStarNum(property->star);
	item->setLabelText(ILT_ATTRIBUTE1, StringUtils::format("%d", property->hp));

	//Ӣ����ħ�������͵�����ʾħ��������������ʾ������
	if (property->isMagic)
	{
		item->setLabelText(ILT_ATTRIBUTE2, StringUtils::format("%d", property->mp));
		item->setIco(StringUtils::format("head%d.png", property->type), hpIco, mpIco);
	}
	else
	{
		item->setLabelText(ILT_ATTRIBUTE2, StringUtils::format("%d", property->ap));
		item->setIco(StringUtils::format("head%d.png", property->type), hpIco, apIco);
	}

	setItemColor(item, property->star);
}

void DisplayLayer::setItemAttribute(const EquipmentProperty * property, DisplayListItem* item)
{
	//�����ı���ǩ
	item->setLabelText(ILT_LEVEL, StringUtils::format("Lv:%d", property->level));
	item->setLabelText(ILT_NAME, *(property->name));
	item->setStarNum(property->star);

	//������ɫ
	setItemColor(item, property->star);

	int type = property->type;

	if (Tools::betweenAnd(type, 100, 108))
	{
		//ñ��
		item->setIco(*(property->textureName), defineIco, mDefineIco);
		item->setLabelText(ILT_ATTRIBUTE1, StringUtils::format("%d", property->defend));
		item->setLabelText(ILT_ATTRIBUTE2, StringUtils::format("%d", property->magicDefend));
	}
	else if (Tools::betweenAnd(type, 200, 207))
	{
		//�·�
		item->setIco(*(property->textureName), defineIco, mDefineIco);
		item->setLabelText(ILT_ATTRIBUTE1, StringUtils::format("%d", property->defend));
		item->setLabelText(ILT_ATTRIBUTE2, StringUtils::format("%d", property->magicDefend));
	}
	else if (Tools::betweenAnd(type, 300, 324))
	{
		//����
		item->setIco(*(property->textureName), apIco, mpIco);
		item->setLabelText(ILT_ATTRIBUTE1, StringUtils::format("%d", property->ap));
		item->setLabelText(ILT_ATTRIBUTE2, StringUtils::format("%d", property->mp));
	}
	else if (Tools::betweenAnd(type, 400, 405))
	{
		//���
		item->setIco(*(property->textureName), hpIco, critIco);
		item->setLabelText(ILT_ATTRIBUTE1, StringUtils::format("%d", property->hp));
		item->setLabelText(ILT_ATTRIBUTE2, StringUtils::format("%d%%", Tools::percentToInt(property->critDamage)));
	}
	else if (Tools::betweenAnd(type, 500, 504))
	{
		//Ь��
		item->setIco(*(property->textureName), speedIco, blockIco);
		item->setLabelText(ILT_ATTRIBUTE1, StringUtils::format("%d", property->speed));
		item->setLabelText(ILT_ATTRIBUTE2, StringUtils::format("%d%%", Tools::percentToInt(property->blockRate)));
	}
	else if (Tools::betweenAnd(type, 600, 604))
	{
		//����
		item->setIco(*(property->textureName), hpIco, speedIco);
		item->setLabelText(ILT_ATTRIBUTE1, StringUtils::format("%d", property->hp));
		item->setLabelText(ILT_ATTRIBUTE2, StringUtils::format("%d", property->speed));
	}
}

void DisplayLayer::updateItemAttribute()
{
	//ͨ���������listview�ж�Ӧ��item
	auto item = dynamic_cast<DisplayListItem*>(_listView->getItem(_clickedIndex));

	switch (_type)
	{
	case OT_EQUIPMENT:
	{
		auto equipment = GameData::getInstance()->getEquipmentById(_objectIdVector.at(_clickedIndex));

		//���µ���item������
		setItemAttribute(equipment->getProperty(), item);

		break;
	}
	case OT_HERO:
	{
		auto hero = GameData::getInstance()->getHeroCardById(_objectIdVector.at(_clickedIndex));

		//���µ���item������
		setItemAttribute(hero->getProperty(), item);
		break;
	}
	default:
		break;
	}

}

void DisplayLayer::loadItem(const unordered_map<int, Equipment*>* equipmentMap)
{
	//��ʼ���ص�����
	int startIndex = _objectIdVector.size();
	//������������ʵ�ʼ��ص�endIndex - 1
	int endIndex = startIndex + equipmentMap->size();
	//��ǰ������
	int index = 0;

	for (auto iter = equipmentMap->begin(); iter != equipmentMap->end(); ++iter)
	{
		if (Tools::betweenAnd(index, startIndex, endIndex - 1) && static_cast<unsigned>(startIndex) < equipmentMap->size())
		{
			auto item = DisplayListItem::create();

			//����item��ʾ������
			auto property = (iter->second)->getProperty();
			setItemAttribute(property, item);
			item->setBtnTexture(_normalTexture, _pressedTexture);
			item->setBtnTag(index);
			item->setBtnCallBack([&](Ref* pSender) {
				auto btn = dynamic_cast<Button*>(pSender);
				_clickedIndex = btn->getTag();

				//�����û����õĻص�
				if (_func)
				{
					//����ѡ�е���Ʒid
					btn->setUserData((void*)_objectIdVector.at(_clickedIndex));
					_func(pSender);
				}
			});

			//��item��ӵ�listView��������itemװ����Ӧ��Id
			_listView->pushBackCustomItem(item);
			_objectIdVector.push_back(iter->first);

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

void DisplayLayer::loadItem(const unordered_map<int, HeroCard*>* heroMap)
{
	//��ʼ���ص�����
	int startIndex = _objectIdVector.size();
	//������������ʵ�ʼ��ص�endIndex - 1
	int endIndex = startIndex + heroMap->size();
	//��ǰ������
	int index = 0;

	for (auto iter = heroMap->begin(); iter != heroMap->end(); ++iter)
	{
		if (Tools::betweenAnd(index, startIndex, endIndex - 1) && static_cast<unsigned>(startIndex) < heroMap->size())
		{
			auto item = DisplayListItem::create();

			//����item��ʾ������
			auto property = (iter->second)->getProperty();
			setItemAttribute(property, item);
			item->setBtnTexture(_normalTexture, _pressedTexture);
			item->setBtnTag(index);
			item->setBtnCallBack([&](Ref* pSender) {

				auto btn = dynamic_cast<Button*>(pSender);
				_clickedIndex = btn->getTag();

				//�����û����õĻص�
				if (_func)
				{
					//����ѡ�е���Ʒid
					btn->setUserData((void*)_objectIdVector.at(_clickedIndex));
					_func(pSender);
				}
			});

			//��item��ӵ�listView��������itemװ����Ӧ��Id
			_listView->pushBackCustomItem(item);
			_objectIdVector.push_back(iter->first);

		}
		else if (static_cast<unsigned>(startIndex) >= heroMap->size() || index >= endIndex)
		{
			//�����ǰ�������Ѿ�������Ҫ���ص�����������������е�item�Ѿ�ȫ�����������ѭ��
			break;
		}

		++index;
	}

	//�����б��ϱ�����ʹ����Ϣ
	setTipLabel();
}

void DisplayLayer::setDisplayType(ObjectType type)
{
	_type = type;
}

void DisplayLayer::setBtnCallBack(std::function<void(cocos2d::Ref*pSender)> func)
{
	_func = func;
}

void DisplayLayer::setBtnTxture(const std::string& normal, const std::string& pressed)
{
	_normalTexture = normal;
	_pressedTexture = pressed;
}

void DisplayLayer::setItemColor(DisplayListItem * item, int star)
{
	Color4B color;

	//��ö�Ӧ�Ǽ�����ɫֵ
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
		color = Color4B::MAGENTA;
		break;
	case 5:
		color = Color4B::ORANGE;
		break;
	default:
		break;
	}

	for (int i = 0; i < 4; ++i)
	{
		item->setLabelColor(static_cast<ItemLabelType>(i), color);
	}
}

void DisplayLayer::btnCloseCallBack(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		//�����Ч
		AudioManager::getInstance()->playClickEffect();

		if (_isNeedUpadateUserData)
		{
			//���͸����û����ݵ���Ϣ
			_eventDispatcher->dispatchCustomEvent(msg_update_user_data);
		}
		
		endAnimation();
	}
}

void DisplayLayer::startAnimation()
{
	//��ʼΪ0
	this->setScale(0.0f);

	auto ani = Sequence::createWithTwoActions(Spawn::createWithTwoActions(ScaleTo::create(0.5f, 1.0f), RotateTo::create(0.5f, 720)), CallFunc::create([&]() {
		//��ʾ����������
		this->getChildByName(blockTagName)->setOpacity(150);
	}));

	this->runAction(ani);
}

void DisplayLayer::endAnimation()
{
	//���ش������β�
	this->getChildByName(blockTagName)->setOpacity(0.0f);

	auto ani = Sequence::createWithTwoActions(Spawn::createWithTwoActions(ScaleTo::create(0.5f, 0.0f), RotateTo::create(0.5f, 720)), CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}
