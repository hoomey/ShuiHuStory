/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	StoreLayer.cpp
// Author:		 Metoor
// Version: 	1.0
// Date: 		2016/11/24
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "StoreLayer.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "DialogManager.h"
#include "GameData.h"
#include "I18N.h"
#include "HeroCard.h"
#include "Equipment.h"
#include "Tools.h"
#include "HeroInfoLayer.h"
#include "DisplayListItem.h"
#include "McLog.h"

USING_NS_CC;
using namespace ui;
using namespace std;

StoreLayer::StoreLayer()
{
	//��ȡ�Ƿ����
	_isBuyEquipment = UserDefault::getInstance()->getBoolForKey(isBuyEquipment.c_str(), false);
	_isBuyHero = UserDefault::getInstance()->getBoolForKey(isBuyHero.c_str(), false);
}

StoreLayer::~StoreLayer()
{
}

bool StoreLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	loadUI();

	//������̬item
	unsigned int preTime = UserDefault::getInstance()->getIntegerForKey(preTimeKey.c_str(), 0);
	unsigned int currentTime = Tools::getCurrentTimeSecond();
	
	auto i18n = I18N::getInstance();
	auto dialog = DialogManager::getInstance();

	//���׼��
	if (preTime != 0 && currentTime < preTime)
	{
		dialog->showIllegalDialog(i18n->getStringByKey(error), i18n->getStringByKey(illegal));
	}
	else
	{
		if (currentTime - preTime >= intervalTime)
		{
			//�����ϴθ��³���6Сʱ�����Ը���
			//���ù���Ȩ��
			_isBuyHero = false;
			_isBuyEquipment = false;

			createRandomItem(getRandomHeroType(), getRandomEquipment());

			//���汾�θ��µ�ʱ��
			UserDefault::getInstance()->setIntegerForKey(preTimeKey.c_str(), currentTime);
		}
		else
		{
			//�����ϴθ���û�г���6Сʱ�����ܸ���
			createRandomItem();
		}
	}

	//���������ʯ�ͽ��
	updateDiamond();
	updateGold();

	return true;
}

void StoreLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_listView = node->getChildByName<ListView*>(listViewName);
	_goldLabel = node->getChildByName<Text*>(goldLabelName);
	_diamondLabel = node->getChildByName<Text*>(diamondLabelName);

	//���ҳ�ʼĬ�ϵ�������ťָ��
	for (int index = 0; index < 4; ++index)
	{
		auto item = _listView->getChildByName(StringUtils::format(itemName.c_str(), index));
		auto btn = item->getChildByName<Button*>(btnOkName);

		btn->addTouchEventListener(CC_CALLBACK_2(StoreLayer::btnOkCallBack, this));
	}
}

int StoreLayer::getRandomHeroType()
{
	int type = Tools::getRandomInt(0, 108);

	return type;
}

int StoreLayer::getRandomEquipment()
{
	int first = Tools::getRandomInt(1, 6);
	int type = none;
	int second = none;

	switch (first)
	{
	case 1:
		second = Tools::getRandomInt(0, 8);
		type = first * 100 + second;
		break;
	case 2:
		second = Tools::getRandomInt(0, 7);
		type = first * 100 + second;
		break;
	case 3:
		second = Tools::getRandomInt(0, 24);
		type = first * 100 + second;
		break;
	case 4:
		second = Tools::getRandomInt(0, 5);
		type = first * 100 + second;
		break;
	case 5:
		second = Tools::getRandomInt(0, 4);
		type = first * 100 + second;
		break;
	case 6:
		second = Tools::getRandomInt(0, 7);
		type = first * 100 + second;
		break;
	default:
		break;
	}

	return type;
}

void StoreLayer::saveEquipment()
{
	auto file = UserDefault::getInstance();
	auto sd = _equipment->getSaveData();

	file->setIntegerForKey(eId.c_str(), sd.id);
	file->setIntegerForKey(eType.c_str(), sd.type);
	file->setIntegerForKey(eRate.c_str(), sd.rate);
	file->setIntegerForKey(eStar.c_str(), sd.star);
}

void StoreLayer::saveHeroCard()
{
	auto file = UserDefault::getInstance();
	auto sd = _hero->getSaveData();

	file->setIntegerForKey(hId.c_str(), sd.id);
	file->setIntegerForKey(hType.c_str(), sd.type);
	file->setIntegerForKey(hRate.c_str(), sd.rate);
	file->setIntegerForKey(hStar.c_str(), sd.star);
}

void StoreLayer::getSaveEquipment(SaveEquipmentData & sd)
{
	auto file = UserDefault::getInstance();

	sd.id = file->getIntegerForKey(eId.c_str(), none);
	sd.type = file->getIntegerForKey(eType.c_str(), none);
	sd.rate = file->getIntegerForKey(eRate.c_str(), none);
	sd.star = file->getIntegerForKey(eStar.c_str(), none);
	sd.level = 1;
	sd.exLevel = 0;
	sd.user = none;
}

void StoreLayer::getSaveHeroCard(SaveHeroCardData & sd)
{
	auto file = UserDefault::getInstance();

	sd.id = file->getIntegerForKey(hId.c_str(), none);
	sd.type = file->getIntegerForKey(hType.c_str(), none);
	sd.rate = file->getIntegerForKey(hRate.c_str(), none);
	sd.star = file->getIntegerForKey(hStar.c_str(), none);
	sd.level = 1;
	sd.exLevel = 0;

	for (int pos = 0; pos < max_equipment_num; ++pos)
	{
		sd.equipmentId[pos] = none;
	}
}

void StoreLayer::createRandomItem(int heroType, int equipmentType)
{
	//�Ƿ��Ǵ��ļ���ȡ���ݳ�ʼ��
	if (heroType == none || equipmentType == none)
	{
		//����Ӣ��
		SaveHeroCardData shd;
		getSaveHeroCard(shd);
		_hero = new (std::nothrow)HeroCard();
		_hero->init(&shd);

		//����װ��
		SaveEquipmentData sed;
		getSaveEquipment(sed);
		_equipment = new (std::nothrow)Equipment();
		_equipment->init(&sed);
	}
	else
	{
		//����Ӣ��
		_hero = new (std::nothrow)HeroCard();
		_hero->init(heroType);

		//����װ��
		_equipment = new (std::nothrow)Equipment();
		_equipment->init(equipmentType);

		//�����´�����Ӣ��װ����Ϣ���Ա����´λָ�
		saveEquipment();
		saveHeroCard();
	}

	auto data = GameData::getInstance();
	auto dialog = DialogManager::getInstance();
	auto i18n = I18N::getInstance();

	//��ʼ��Ӣ��item
	auto item1 = DisplayListItem::create();
	setItemAttribute(_hero->getProperty(), item1);
	
	if (_isBuyHero)
	{
		//�Ѿ�������������ڹ�����
		item1->setBtnTexture(btnBuyed1, btnBuyed2);
		item1->setBtnEnable(false);
	}
	else
	{
		item1->setBtnTexture(btnBuy1, btnBuy2);
	}
	
	item1->setBtnCallBack([&, data, dialog, i18n](Ref* pSender) {
		auto property = _hero->getProperty();
		auto btn = dynamic_cast<Button*>(pSender);

		dialog->showDialog(i18n->getStringByKey(buyTitle), StringUtils::format(i18n->getStringByKey(buy).c_str(), property->sellMoney, property->name), [&, data, dialog, i18n, property, btn](Ref* pSender) {
			if (data->setDiamond(-property->sellMoney))
			{
				//����ɹ�
				//���ð�ť�������������ѹ���
				btn->setEnabled(false);
				btn->loadTextureDisabled(btnBuyed2, Widget::TextureResType::PLIST);
				
				//��Ӣ�ۼ������Ӣ���б�
				data->addHeroCardToMap(_hero);

				//�����ѹ�����
				_isBuyHero = true;
				
				//���湺���¼
				UserDefault::getInstance()->setBoolForKey(isBuyHero.c_str(), _isBuyHero);
				
				//��ʾ��Ϣ
				dialog->showTips(i18n->getStringByKey(buySuc), Color4B::GREEN);
			}
			else
			{
				//����ʧ����ʾ��Ϣ
				dialog->showTips(i18n->getStringByKey(buyError));
			}
		});
	});


	_listView->pushBackCustomItem(item1);

	//��ʼ��װ��Item
	auto item2 = DisplayListItem::create();
	setItemAttribute(_equipment->getProperty(), item2);
	if (_isBuyEquipment)
	{
		//�Ѿ�������������ڹ�����
		item2->setBtnTexture(btnBuyed1, btnBuyed2);
		item2->setBtnEnable(false);
	}
	else
	{
		item2->setBtnTexture(btnBuy1, btnBuy2);
	}

	item2->setBtnCallBack([&, data, dialog, i18n](Ref* pSender) {
		auto property = _equipment->getProperty();
		auto btn = dynamic_cast<Button*>(pSender);

		dialog->showDialog(i18n->getStringByKey(buyTitle), StringUtils::format(i18n->getStringByKey(buy).c_str(), property->sellMoney, property->name), [&, data, dialog, i18n, property, btn](Ref* pSender) {
			if (data->setDiamond(-property->sellMoney))
			{
				//����ɹ�
				//���ð�ť�������������ѹ���
				btn->setEnabled(false);
				btn->loadTextureDisabled(btnBuyed2, Widget::TextureResType::PLIST);

				//��װ����ӵ����װ���б�
				data->addEquipmentToMap(_equipment);

				//�����ѹ�����
				_isBuyEquipment = true;

				UserDefault::getInstance()->setBoolForKey(isBuyEquipment.c_str(), _isBuyEquipment);

				//��ʾ��Ϣ
				dialog->showTips(i18n->getStringByKey(buySuc), Color4B::GREEN);
			}
			else
			{
				//����ʧ��,��ʾ��Ϣ
				dialog->showTips(i18n->getStringByKey(buyError));
			}
		});
	});

	_listView->pushBackCustomItem(item2);
}

void StoreLayer::setItemAttribute(const HeroCardProperty * property, DisplayListItem * item)
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

void StoreLayer::setItemAttribute(const EquipmentProperty * property, DisplayListItem * item)
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
		item->setLabelText(ILT_ATTRIBUTE2, StringUtils::format("%d%%", property->blockRate));
	}
	else if (Tools::betweenAnd(type, 600, 607))
	{
		//����
		item->setIco(*(property->textureName), hpIco, speedIco);
		item->setLabelText(ILT_ATTRIBUTE1, StringUtils::format("%d", property->hp));
		item->setLabelText(ILT_ATTRIBUTE2, StringUtils::format("%d", property->speed));
	}
}

void StoreLayer::setItemColor(DisplayListItem * item, int star)
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

void StoreLayer::updateDiamond()
{
	auto data = GameData::getInstance();
	_diamondLabel->setString(StringUtils::format("%d", data->getDiamond()));
}

void StoreLayer::updateGold()
{
	auto data = GameData::getInstance();
	_goldLabel->setString(StringUtils::format("%d", data->getGold()));
}

void StoreLayer::btnOkCallBack(Ref * pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		AudioManager::getInstance()->playClickEffect();
	}

	if (type == Widget::TouchEventType::ENDED)
	{
		int tag = dynamic_cast<Button*>(pSender)->getTag();

		auto dialog = DialogManager::getInstance();
		auto i18n = I18N::getInstance();
		auto data = GameData::getInstance();

		switch (tag)
		{
		case 0:
			dialog->showDialog(i18n->getStringByKey(buyTitle), StringUtils::format(i18n->getStringByKey(buyHero).c_str(), tian_d), [&, dialog, i18n, data](Ref* pSender) {
				if (data->setDiamond(-tian_d))
				{
					//����һ���µ����Ӣ��
					auto hero = new (std::nothrow)HeroCard();
					int type = Tools::getRandomInt(0, 35);
					hero->init(type);
					data->addHeroCardToMap(hero);

					//��ʾ�ɹ���ʾ��
					dialog->showTips(i18n->getStringByKey(buySuc), Color4B::GREEN);

					//��ʾ�����ɹ���Ӣ������
					auto info = HeroInfoLayer::create();
					info->initWithHerotype(hero->getProperty()->id, HT_GAMEDATA);
					addChild(info);

					//������ʯ
					updateDiamond();
				}
				else
				{
					//��ʯ����
					dialog->showTips(i18n->getStringByKey(buyError));
				}
			});
			break;
		case 1:
			dialog->showDialog(i18n->getStringByKey(buyTitle), StringUtils::format(i18n->getStringByKey(buyHero).c_str(), di_d), [&, dialog, i18n, data](Ref* pSender) {
				if (data->setDiamond(-tian_d))
				{
					//����һ���µ����Ӣ��
					auto hero = new (std::nothrow)HeroCard();
					int type = Tools::getRandomInt(36, 108);
					hero->init(type);
					data->addHeroCardToMap(hero);

					//��ʾ�ɹ���ʾ��
					dialog->showTips(i18n->getStringByKey(buySuc), Color4B::GREEN);

					//��ʾ�����ɹ���Ӣ������
					auto info = HeroInfoLayer::create();
					info->initWithHerotype(hero->getProperty()->id, HT_GAMEDATA);
					addChild(info);

					//������ʯ
					updateDiamond();
				}
				else
				{
					//��ʯ����
					dialog->showTips(i18n->getStringByKey(buyError));
				}
			});
			break;
		case 2:
			dialog->showDialog(i18n->getStringByKey(buyTitle), StringUtils::format(i18n->getStringByKey(buyGold).c_str(), gold_d, gold), [&, dialog, i18n, data](Ref* pSender) {
				if (data->setDiamond(-gold_d))
				{
					data->setGold(gold);

					updateGold();
					updateDiamond();

					//��ʾ�ɹ���ʾ��
					dialog->showTips(i18n->getStringByKey(buySuc), Color4B::GREEN);
				}
				else
				{
					//��ʯ����
					dialog->showTips(i18n->getStringByKey(buyError));
				}
			});
			break;
		case 3:
			dialog->showDialog(i18n->getStringByKey(buyTitle), StringUtils::format(i18n->getStringByKey(buyDiamond).c_str(), diamond_g, diamond), [&, dialog, i18n, data](Ref* pSender) {
				if (data->setGold(-diamond_g))
				{
					data->setDiamond(diamond);

					updateGold();
					updateDiamond();

					//��ʾ�ɹ���ʾ��
					dialog->showTips(i18n->getStringByKey(buySuc), Color4B::GREEN);
				}
				else
				{
					//��ʯ����
					dialog->showTips(i18n->getStringByKey(buyError));
				}
			});
			break;
		default:
			break;
		}
	}
}

void StoreLayer::onEnter()
{
	Layer::onEnter();

	DialogManager::getInstance()->showTips(I18N::getInstance()->getStringByKey(storeTips), Color4B::GREEN);
}
