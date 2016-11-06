#include "HeroDisplayLayer.h"
#include "cocostudio/CocoStudio.h"
#include "BlockLayer.h"
#include "AudioManager.h"
#include "ListItem.h"
#include "GameData.h"
#include "Tools.h"
#include "HeroCard.h"

USING_NS_CC;
using namespace ui;
using namespace std;


HeroDisplayLayer::HeroDisplayLayer()
{
}

HeroDisplayLayer::~HeroDisplayLayer()
{
}

bool HeroDisplayLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//�����������β�
	auto blockLayer = BlockLayer::create();
	blockLayer->setName(blockName);
	addChild(blockLayer);

	loadUI();
	
	//����item
	auto heroCardMap = GameData::getInstance()->getHeroCardMap();
	loadItem(heroCardMap->size());

	return true;
}

void HeroDisplayLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	//���ҿؼ�
	_listView = node->getChildByName<ListView*>(listViewName);
	_btnClose = node->getChildByName<Button*>(btnCloseName);


	//���¼��ص�
	_btnClose->addTouchEventListener(CC_CALLBACK_2(HeroDisplayLayer::btnCloseCallBack, this));

}

void HeroDisplayLayer::loadItem(int n)
{
	auto heroCardMap = GameData::getInstance()->getHeroCardMap();

	//��ʼ���ص�����
	int startIndex = _itemVector.size();
	//������������ʵ�ʼ��ص�endIndex - 1
	int endIndex = startIndex + n;
	//��ǰ������
	int index = 0;

	for (auto iter = heroCardMap->begin(); iter != heroCardMap->end(); ++iter)
	{
		if (Tools::betweenAnd(index, startIndex, endIndex - 1))
		{
			auto item = ListItem::create();

			//����item��ʾ������
			auto property = iter->second->getProperty();
			setItemAttribute(property, item);
			item->setBtnTexture(btnDetails1, btnDetails2);
			item->setBtnTag(index);
			item->setBtnCallBack([&](Ref* pSender, Widget::TouchEventType type) {
				if (type == Widget::TouchEventType::ENDED)
				{
					int tag = dynamic_cast<Button*>(pSender)->getTag();

					log("----%d", tag);
				}
			});


			//��ӵ�listView��itemVector
			_listView->pushBackCustomItem(item);
			_itemVector.pushBack(item);
		}
		else if (static_cast<unsigned>(startIndex) >= heroCardMap->size() || index >= endIndex)
		{
			//�����ǰ�������Ѿ�������Ҫ���ص�����������������е�item�Ѿ�ȫ�����������ѭ��
			break;
		}

		++index;
	}
}

void HeroDisplayLayer::setItemAttribute(const HeroCardProperty * property, ListItem * item)
{
	//�����ı���ǩ
	item->setLabelText(LEVEL, StringUtils::format("Lv:%d", property->level));
	item->setLabelText(NAME, *(property->name));
	item->setStarNum(property->star);
	item->setLabelText(TEXT1, StringUtils::format("%d", property->hp));
	item->setLabelText(TEXT2, StringUtils::format("%d", property->ap));

	//����ͼ��
	item->setIco(StringUtils::format("head%d.png", property->type), hpIco, apIco);
	

	setItemColor(item, property->star);
}

void HeroDisplayLayer::updateItemAttribute(const int heroId, const int itenId)
{
	auto hero = GameData::getInstance()->getHeroCardById(heroId);

	//���µ���item������
	setItemAttribute(hero->getProperty(), _itemVector.at(itenId));
}

void HeroDisplayLayer::setItemColor(ListItem * item, int star)
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

void HeroDisplayLayer::btnCloseCallBack(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		//�����Ч
		auto audio = AudioManager::getInstance();
		audio->playEffect(audio->clickEffect);

		endAnimation();
	}
}

void HeroDisplayLayer::onEnterTransitionDidFinish()
{
	startAnimation();
}

void HeroDisplayLayer::startAnimation()
{
	//��ʼΪ0
	this->setScale(0.0f);

	auto ani = Sequence::createWithTwoActions(Spawn::createWithTwoActions(ScaleTo::create(0.5f, 1.0f), RotateTo::create(0.5f, 720)), CallFunc::create([&]() {
		//��ʾ����������
		this->getChildByName(blockName)->setOpacity(150);
	}));

	this->runAction(ani);
}

void HeroDisplayLayer::endAnimation()
{
	//���ش������β�
	this->getChildByName(blockName)->setOpacity(0.0f);

	auto ani = Sequence::createWithTwoActions(Spawn::createWithTwoActions(ScaleTo::create(0.5f, 0.0f), RotateTo::create(0.5f, 720)), CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}
