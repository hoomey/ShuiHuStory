/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	DetailsLayer.cpp
// Author:		 Metoor
// Version: 	1.0
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "DetailsLayer.h"
#include "cocostudio/CocoStudio.h"
#include "BlockLayer.h"
#include "GameData.h"
#include "AudioManager.h"
#include "Equipment.h"
#include "HeroCard.h"
#include "I18N.h"
#include "Tools.h"
#include "McLog.h"
#include "AudioManager.h"
#include "DialogManager.h"

USING_NS_CC;
using namespace ui;
using namespace std;

DetailsLayer::DetailsLayer()
	:_objectId(0),
	_intensifyFun(nullptr),
	_levelupFunc(nullptr)
{
	//��ȡ��������
	_data = GameData::getInstance();
	_i18n = I18N::getInstance();
}

DetailsLayer::~DetailsLayer()
{
}

bool DetailsLayer::init()
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

	return true;
}

void DetailsLayer::initUiWithId(int id, DisplayType type)
{
	_objectId = id;
	_type = type;

	updateAttribute();
}

void DetailsLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	//���ҿؼ�
	_nameLabel = node->getChildByName<Text*>(nameLabelName);
	_ico = node->getChildByName<ImageView*>(icoName);
	_attributeLabel = node->getChildByName<Text*>(attributeLabelName);
	_btnIntensify = node->getChildByName<Button*>(btnIntensifyName);
	_btnLevelup = node->getChildByName<Button*>(btnLevelupName);
	_btnClose = node->getChildByName<Button*>(btnCloseName);
	_btnSell = node->getChildByName<Button*>(btnSellName);
	_btnAbandon = node->getChildByName<Button*>(btnAbandonName);

	//�رհ�ť�ص�
	_btnClose->addTouchEventListener(CC_CALLBACK_2(DetailsLayer::btnCloseCallBack, this));
	
	//ǿ����ť�ص�
	_btnIntensify->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			//�����Ч
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			dynamic_cast<Button*>(pSender)->setUserData((void*)BT_INTENSIFY);

			intensify();
		}
	});

	//������ť�ص�
	_btnLevelup->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			//�����Ч
			AudioManager::getInstance()->playClickEffect();
		}
		
		if (type == Widget::TouchEventType::ENDED)
		{
			dynamic_cast<Button*>(pSender)->setUserData((void*)BT_LEVEL_UP);

			levelup();
		}
	});

	//������Ʒ
	_btnSell->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			//�����Ч
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			sell();
		}
	});

	//������Ʒ
	_btnAbandon->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			//�����Ч
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			abandon();
		}
	});
}

int DetailsLayer::calculateCost(BtnType type)
{
	if (BT_LEVEL_UP == type)
	{
		return calculateGold();
	}
	else
	{
		return calculateDiamond();
	}
}

int DetailsLayer::calculateGold()
{
	int cost = 0;

	switch (_type)
	{
	case DT_EQUIPMENT:
	{
		//����������Ҫ���Ľ��
		auto property = _data->getEquipmentById(_objectId)->getProperty();
		cost = property->level * levelup_base_gold * (1 + property->star * 0.1f);
		break;
	}
	case DT_HERO:
	{
		//����������Ҫ���Ľ��
		auto property = _data->getHeroCardById(_objectId)->getProperty();
		cost = property->level * levelup_base_gold * (1 + property->star * 0.1f);
		break;
	}
	default:
		break;
	}
	return cost;
}

int DetailsLayer::calculateDiamond()
{
	int cost = 0;

	switch (_type)
	{
	case DT_EQUIPMENT:
	{
		//����ǿ������Ҫ����ʯ
		auto property = _data->getEquipmentById(_objectId)->getProperty();
		cost = property->exLevel * intensify_base_diamond * (1 + property->star *0.1f);
		break;
	}
	case DT_HERO:
	{
		//����ǿ������Ҫ����ʯ
		auto property = _data->getHeroCardById(_objectId)->getProperty();
		cost = property->exLevel * intensify_base_diamond * (1 + property->star *0.1f);
		break;
	}
	default:
		break;
	}
	return cost;
}

int DetailsLayer::findSameTypeObject()
{
	int result = none;

	switch (_type)
	{
	case DT_EQUIPMENT:
	{
		auto equimpentMap = _data->getEquipmentMap();
		auto curProperty = _data->getEquipmentById(_objectId)->getProperty();

		for (auto iter = equimpentMap->begin(); iter != equimpentMap->end(); ++iter)
		{
			auto property = iter->second->getProperty();

			if (property->type == curProperty->type && iter->first != _objectId && property->user == none)
			{
				//�ж����ͬ����װ��������û��װ����Ӣ�����ϣ�����ҳɹ�
				result = iter->first;
				break;
			}
		}
		break;
	}
	case DT_HERO:
	{
		auto heroMap = _data->getHeroCardMap();
		auto curProperty = _data->getHeroCardById(_objectId)->getProperty();

		for (auto iter = heroMap->begin(); iter != heroMap->end(); ++iter)
		{
			auto property = iter->second->getProperty();

			if (property->type == curProperty->type && iter->first != _objectId && _objectId)
			{
				//��������Ӣ���Ѿ���ս������Ը�Ӣ��
				if (!_data->isBattleHero(iter->first))
				{
					result = iter->first;
				}
			}
		}
		break;
	}
	default:
		break;
	}

	return result;
}

void DetailsLayer::levelupEquiupment()
{
	auto dm = DialogManager::getInstance();
	auto property = _data->getEquipmentById(_objectId)->getProperty();

	
	int cost = calculateCost(BT_LEVEL_UP);

	dm->showDialog(_i18n->getStringByKey(levelupTitle), StringUtils::format(_i18n->getStringByKey(levelTips).c_str(), cost,
		property->name->c_str()),
		[&, cost](Ref* pSender) {

		auto equipment = _data->getEquipmentById(_objectId);

		//�ж��Ƿ����㹻�Ľ�ң� ��Ϊ��Ҫ���Ľ�������Ǹ���
		if (_data->setGold(-cost))
		{
			//�������������㣬�����ɹ�
			equipment->levelup();
			//��������
			updateAttribute();
			dm->showTips(StringUtils::format(I18N::getInstance()->getStringByKey(succed).c_str(), equipment->getProperty()->name->c_str()), Color4B::GREEN);
		}
		else
		{
			//��Ҳ���
			dm->showTips(I18N::getInstance()->getStringByKey(notEnoughGold));
		}
	});
}

void DetailsLayer::levelupHero()
{
	auto dm = DialogManager::getInstance();
	auto property = _data->getHeroCardById(_objectId)->getProperty();

	int cost = calculateCost(BT_LEVEL_UP);

	dm->showDialog(_i18n->getStringByKey(levelupTitle), StringUtils::format(_i18n->getStringByKey(levelTips).c_str(), cost,
		property->name->c_str()),
		[&, cost](Ref* pSender) {

		auto hero = _data->getHeroCardById(_objectId);

		//�ж��Ƿ����㹻�Ľ�ң� ��Ϊ��Ҫ���Ľ�������Ǹ���
		if (_data->setGold(-cost))
		{
			//�������������㣬�����ɹ�
			hero->levelup();
			//���������������
			updateAttribute();
			dm->showTips(StringUtils::format(I18N::getInstance()->getStringByKey(succed).c_str(), hero->getProperty()->name->c_str()), Color4B::GREEN);
		}
		else
		{
			//��Ҳ���
			dm->showTips(I18N::getInstance()->getStringByKey(notEnoughGold));
		}
	});
}

void DetailsLayer::intensifyEquipment()
{
	auto dm = DialogManager::getInstance();
	auto property = _data->getEquipmentById(_objectId)->getProperty();

	int cost = calculateCost(BT_INTENSIFY);

	dm->showDialog(_i18n->getStringByKey(intensifyTitle), StringUtils::format(_i18n->getStringByKey(intensifyTips).c_str(), cost,
		property->name->c_str(), property->name->c_str()),
		[&, cost](Ref* pSender) {

		auto equipment = _data->getEquipmentById(_objectId);

		//�ж��Ƿ����㹻����ʯ�� ��Ϊ��Ҫ������ʯ�����Ǹ���
		if (_data->setDiamond(-cost))
		{
			//�Ƿ�����ͬ��װ��
			int id = findSameTypeObject();

			if (id != none)
			{
				//ɾ����Ϊǿ�����ϵ�װ��
				_data->deleteEquipmentById(id);
				//ǿ���ɹ�
				equipment->intensify();
				//����ǿ���������
				updateAttribute();
				dm->showTips(StringUtils::format(I18N::getInstance()->getStringByKey(succed).c_str(), equipment->getProperty()->name->c_str()), Color4B::GREEN);
			}
			else
			{
				//û����ͬ�Ĳ���
				dm->showTips(StringUtils::format(I18N::getInstance()->getStringByKey(notEnougMaterial).c_str(), equipment->getProperty()->name->c_str()));
			}
		}
		else
		{
			//û�н��
			dm->showTips(I18N::getInstance()->getStringByKey(notEnoughGold).c_str());
		}
	});
}

void DetailsLayer::intensifyHero()
{
	auto dm = DialogManager::getInstance();
	auto property = _data->getHeroCardById(_objectId)->getProperty();

	int cost = calculateCost(BT_INTENSIFY);

	dm->showDialog(_i18n->getStringByKey(intensifyTitle), StringUtils::format(_i18n->getStringByKey(intensifyTips).c_str(), cost,
		property->name->c_str(), property->name->c_str()),
		[&, cost](Ref* pSender) {

		auto hero = _data->getHeroCardById(_objectId);

		//�ж��Ƿ����㹻����ʯ�� ��Ϊ��Ҫ������ʯ�����Ǹ���
		if (_data->setDiamond(-cost))
		{
			//�Ƿ�����ͬ�Ŀ���
			int id = findSameTypeObject();

			if (id != none)
			{
				//ɾ����Ϊǿ�����ϵĿ���
				_data->deleteHeroCardById(id);
				//ǿ���ɹ�
				hero->intensify();
				//����ǿ���������
				updateAttribute();
				dm->showTips(StringUtils::format(I18N::getInstance()->getStringByKey(succed).c_str(), hero->getProperty()->name->c_str()), Color4B::GREEN);
			}
			else
			{
				//û����ͬ�Ĳ���
				dm->showTips(StringUtils::format(I18N::getInstance()->getStringByKey(notEnougMaterial).c_str(), hero->getProperty()->name->c_str()));
			}
		}
		else
		{
			//û�н��
			dm->showTips(I18N::getInstance()->getStringByKey(notEnoughGold).c_str());
		}
	});
}

string DetailsLayer::propertyToString(const EquipmentProperty * property)
{
	string res = StringUtils::format(_i18n->getStringByKey(level_d).c_str(), property->level);
	res += "\t";
	res += StringUtils::format(_i18n->getStringByKey(intensify_d).c_str(), "+", property->exLevel);
	res += "\n";

	//���װ��������
	int type = property->type / 100;

	switch (type)
	{
	case 1:
	case 2:
	{
		//�·�
		res += StringUtils::format(_i18n->getStringByKey(define_d).c_str(), "+", property->defend);
		res += "\n";
		res += StringUtils::format(_i18n->getStringByKey(mDefine_d).c_str(), "+", property->magicDefend);
		break;
	}
	case 3:
	{
		//����
		res += StringUtils::format(_i18n->getStringByKey(ap_d).c_str(), "+", property->ap);
		res += "\n";
		res += StringUtils::format(_i18n->getStringByKey(mp_d).c_str(), "+", property->mp);
		res += "\n";
		res += StringUtils::format(_i18n->getStringByKey(crit_d).c_str(), "+", property->critRate);
		break;
	}
	case 4:
	{
		//���
		res += StringUtils::format(_i18n->getStringByKey(hp_d).c_str(), "+", property->hp);
		res += "\n";
		res += StringUtils::format(_i18n->getStringByKey(critDmg_d).c_str(), "+", Tools::percentToInt(property->critDamage));
		break;
	}
	case 5:
	{
		//Ь��
		res += StringUtils::format(_i18n->getStringByKey(speed_d).c_str(), "+", property->speed);
		res += "\n";
		res += StringUtils::format(_i18n->getStringByKey(block_d).c_str(), "+", property->blockRate);
		break;
	}
	case 6:
	{
		//����
		res += StringUtils::format(_i18n->getStringByKey(speed_d).c_str(), "+", property->speed);
		res += "\n";
		res += StringUtils::format(_i18n->getStringByKey(hp_d).c_str(), "+", property->hp);
		res += "\n";
		res += StringUtils::format(_i18n->getStringByKey(define_d).c_str(), "+", property->defend);
		res += "\n";
		res += StringUtils::format(_i18n->getStringByKey(mDefine_d).c_str(), "+", property->magicDefend);
		break;
	}
	default:
		break;
	}

	return res;
}

string DetailsLayer::propertyToString(const HeroCardProperty* property)
{
	//�����Ը�ʽ����Ҫ��ʾ�������ַ�����ȥ
	string res = StringUtils::format(_i18n->getStringByKey(level_d).c_str(), property->level);
	res += "\t";
	res += StringUtils::format(_i18n->getStringByKey(intensify_d).c_str(), "", property->exLevel);
	res += "\n";
	res += StringUtils::format(_i18n->getStringByKey(star_d).c_str(), property->star);
	res += "\t";
	res += StringUtils::format(_i18n->getStringByKey(crit_d).c_str(), "", property->critRate);
	res += "\n";
	res += StringUtils::format(_i18n->getStringByKey(ap_d).c_str(), "", property->ap);
	res += "\t";
	res += StringUtils::format(_i18n->getStringByKey(mp_d).c_str(), "", property->mp);
	res += "\n";
	res += StringUtils::format(_i18n->getStringByKey(define_d).c_str(), "", property->defend);
	res += "\t";
	res += StringUtils::format(_i18n->getStringByKey(mDefine_d).c_str(), "", property->magicDefend);
	res += "\n";
	res += StringUtils::format(_i18n->getStringByKey(speed_d).c_str(), "", property->speed);
	res += "\t";
	res += StringUtils::format(_i18n->getStringByKey(block_d).c_str(), "", property->blockRate);
	res += "\n";
	res += StringUtils::format(_i18n->getStringByKey(hp_d).c_str(), "", property->hp);
	res += "\n";
	res += StringUtils::format(_i18n->getStringByKey(critDmg_d).c_str(), "", Tools::percentToInt(property->critDamage));

	return res;
}

void DetailsLayer::updateAttribute()
{
	switch (_type)
	{
	case DT_EQUIPMENT:
	{
		auto property = _data->getEquipmentById(_objectId)->getProperty();
		setName(*(property->name));
		setNameColor(property->star);
		setIco(*(property->textureName));
		setAttributeString(propertyToString(property));
		break;
	}
	case DT_HERO:
	{
		auto property = _data->getHeroCardById(_objectId)->getProperty();
		setName(*(property->name));
		setNameColor(property->star);
		setIco(StringUtils::format("head%d.png", property->type));
		setAttributeString(propertyToString(property));
		break;
	}
	default:
		break;
	}
}

void DetailsLayer::setName(const std::string name)
{
	_nameLabel->setString(name);
}

void DetailsLayer::setNameColor(int star)
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
		color = Color4B::YELLOW;
		break;
	default:
		break;
	}

	_nameLabel->setTextColor(color);
}

void DetailsLayer::setAttributeString(const std::string& content)
{
	_attributeLabel->setString(content);
}

void DetailsLayer::setIco(const std::string& icoName)
{
	_ico->loadTexture(icoName, TextureResType::PLIST);
}

void DetailsLayer::intensify()
{
	switch (_type)
	{
	case DT_EQUIPMENT:
		intensifyEquipment();
		break;
	case DT_HERO:
		intensifyHero();
		break;
	default:
		break;
	}
}

void DetailsLayer::levelup()
{
	switch (_type)
	{
	case DT_EQUIPMENT:
		levelupEquiupment();
		break;
	case DT_HERO:
		levelupHero();
		break;
	default:
		break;
	}
}

void DetailsLayer::startAnimation()
{
	this->setScale(0.0f);

	auto ani = Spawn::createWithTwoActions(ScaleTo::create(0.5f, 1.0f), RotateTo::create(0.5f, 720));
	this->runAction(ani);
}

void DetailsLayer::endAnimation()
{
	auto ani = Sequence::createWithTwoActions(Spawn::createWithTwoActions(ScaleTo::create(0.5f, 0.0f), RotateTo::create(0.5f, 720)), CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}

void DetailsLayer::onEnter()
{
	Layer::onEnter();
	startAnimation();
}

void DetailsLayer::sell()
{
	switch (_type)
	{
	case DT_EQUIPMENT:
		sellOEquipment();
		break;
	case DT_HERO:
		sellOHero();
		break;
	default:
		break;
	}
}

void DetailsLayer::sellOEquipment()
{
	auto dm = DialogManager::getInstance();
	auto property = _data->getEquipmentById(_objectId)->getProperty();

	dm->showDialog(_i18n->getStringByKey(sellTitle), StringUtils::format(_i18n->getStringByKey(sellTips).c_str(), property->sellMoney, property->name->c_str()), [&](Ref* pSender) {
		
		auto property = _data->getEquipmentById(_objectId)->getProperty();
		_data->deleteEquipmentById(_objectId);
		_data->setGold(property->sellMoney);
		
		//���Ż�ý����Ч
		AudioManager::getInstance()->playEffect(rewardGoldEffectName);

		DialogManager::getInstance()->showTips(StringUtils::format(_i18n->getStringByKey(sellSucced).c_str(), property->sellMoney), Color4B::GREEN);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(msg_update_display_item, (void*)msg_update_display_item_parameter_sell);

		//��Ϊ��Ҫ����رղ�ִ����Ч�����Ѳ��ܵ���endAnimantion()
		this->removeFromParentAndCleanup(true);
	});
}

void DetailsLayer::sellOHero()
{
	auto dm = DialogManager::getInstance();
	auto property = _data->getHeroCardById(_objectId)->getProperty();

	dm->showDialog(_i18n->getStringByKey(sellTitle), StringUtils::format(_i18n->getStringByKey(sellTips).c_str(), property->sellMoney, property->name->c_str()), [&](Ref* pSender) {
		
		auto property = _data->getHeroCardById(_objectId)->getProperty();
		_data->deleteHeroCardById(_objectId);
		_data->setGold(property->sellMoney);

		DialogManager::getInstance()->showTips(StringUtils::format(_i18n->getStringByKey(sellSucced).c_str(), property->sellMoney), Color4B::GREEN);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(msg_update_display_item, (void*)msg_update_display_item_parameter_sell);

		//��Ϊ��Ҫ����رղ�ִ����Ч�����Ѳ��ܵ���endAnimantion()
		this->removeFromParentAndCleanup(true);
	});
}

void DetailsLayer::abandon()
{
	switch (_type)
	{
	case DT_EQUIPMENT:
		abandonEquipment();
		break;
	case DT_HERO:
		abandonHero();
		break;
	default:
		break;
	}
}

void DetailsLayer::abandonEquipment()
{
	auto dm = DialogManager::getInstance();
	auto property = _data->getEquipmentById(_objectId)->getProperty();

	dm->showDialog(_i18n->getStringByKey(abandonTitle), StringUtils::format(_i18n->getStringByKey(abandonTips).c_str(), property->name->c_str()), [&](Ref* pSender) {
		//������ѻ��װ���б�ɾ��
		_data->deleteEquipmentById(_objectId);

		DialogManager::getInstance()->showTips(_i18n->getStringByKey(abandonSucced), Color4B::GREEN);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(msg_update_display_item, (void*)msg_update_display_item_parameter_abandon);

		//��Ϊ��Ҫ����رղ�ִ����Ч�����Ѳ��ܵ���endAnimantion()
		this->removeFromParentAndCleanup(true);
	});
}

void DetailsLayer::abandonHero()
{
	auto dm = DialogManager::getInstance();
	auto property = _data->getHeroCardById(_objectId)->getProperty();

	dm->showDialog(_i18n->getStringByKey(abandonTitle), StringUtils::format(_i18n->getStringByKey(abandonTips).c_str(), property->name->c_str()), [&](Ref* pSender) {
		//������ѻ�ÿ���ɾ��
		_data->deleteHeroCardById(_objectId);

		DialogManager::getInstance()->showTips(_i18n->getStringByKey(abandonSucced), Color4B::GREEN);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(msg_update_display_item, (void*)msg_update_display_item_parameter_abandon);

		//��Ϊ��Ҫ����رղ�ִ����Ч�����Ѳ��ܵ���endAnimantion()
		this->removeFromParentAndCleanup(true);
	});
}

void DetailsLayer::btnCloseCallBack(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		//�����Ч
		AudioManager::getInstance()->playClickEffect();

		//���͸���DisplayLayer  item����Ϣ
		_eventDispatcher->dispatchCustomEvent(msg_update_display_item);
		
		endAnimation();
	}
}
