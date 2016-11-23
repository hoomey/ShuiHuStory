/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	PictureLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/20
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "PictureLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Tools.h"
#include "Config.h"
#include "AudioManager.h"
#include "McLog.h"
#include "HeroInfoLayer.h"

USING_NS_CC;
using namespace ui;
using namespace std;

PictureLayer::PictureLayer()
	:_preIndex(none)
{
}

PictureLayer::~PictureLayer()
{
}

bool PictureLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	loadUI();

	addTouchLayer();

	return true;
}

void PictureLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_tips = node->getChildByName<Text*>(tipsName);
	_btnTian = node->getChildByName<Button*>(btnTianName);
	_btnDi = node->getChildByName<Button*>(btnDiName);
	_pageView = node->getChildByName<PageView*>(pageViewName);

	_btnTian->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			_pageView->setCurrentPageIndex(0);
		}
	});

	_btnDi->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			_pageView->setCurrentPageIndex(6);
		}
	});
}

void PictureLayer::addTouchLayer()
{
	//����������
	auto touchLayer = TouchLayer::create();
	touchLayer->setOnTouchBegan([&](int selectIndex) {
		//ѡ����item����Сѡ�е�item
		auto item = dynamic_cast<PictureItem*>(_pageView->getItem(_preIndex));
		item->setSelect(true, selectIndex);
	});

	touchLayer->setOnTouchMoved([&](int selectIndex) {
		//log("moved...");
	});

	touchLayer->setOnTouchEnded([&](int selectIndex, int moveDistance) {
		
		//��item�ָ���δѡ��״̬
		auto item = dynamic_cast<PictureItem*>(_pageView->getItem(_preIndex));
		item->setSelect(false, selectIndex);

		//����ƶ��ľ���С��0.3f��������ƶ�
		if (moveDistance < 0.3f)
		{
			//��ѡ�е�item��ţ�ת����Ӣ��type
			int type = selectIndex + _preIndex * max_battle_hero_num;

			//�����һҳֻ��һ��108��Ӣ�ۣ�����Ҫ�ų�û��Ӣ��λ�õĵ��
			if (type < 109)
			{
				AudioManager::getInstance()->playClickEffect();

				//����Ӣ�۽���ҳ��
				auto infoLayer = HeroInfoLayer::create();
				infoLayer->initWithHerotype(type);
				addChild(infoLayer);
			}
			
		}
	});

	addChild(touchLayer);
}

void PictureLayer::initTypeList(int star, int list[], int length)
{
	for (int index = 0; index < max_battle_hero_num; ++index)
	{
		if (index < length)
		{
			list[index] = star++;
		}
		else
		{
			//��ʼΪ-1
			list[index] = none;
		}
	}
}

void PictureLayer::loadItem()
{
	auto data = Config::getInstance();

	for (int index = 0; index < pageCount; ++index)
	{
		auto hero = data->getHeroCardByIndex(index);

		int typeList[max_battle_hero_num];

		int startIndex = index * max_battle_hero_num;

		//���������һ��Ӣ��ˮ���
		if (index == 18)
		{
			initTypeList(startIndex, typeList, 1);
		}
		else
		{
			initTypeList(startIndex, typeList);
		}
		
		auto layout = PictureItem::create();
		layout->initWithTypeList(typeList);
		_pageView->addPage(layout);
	}

	//Ĭ����ʾ0��λ��
	_pageView->setCurrentPageIndex(0);

	//������ʱ��
	this->scheduleUpdate();
}

void PictureLayer::onEnter()
{
	Layer::onEnter();

	loadItem();
}

void PictureLayer::update(float dt)
{
	int currentIndex = _pageView->getCurrentPageIndex();

	if (_preIndex != currentIndex)
	{
		_preIndex = currentIndex;

		if (currentIndex < tianEndPage)
		{
			_btnTian->setEnabled(false);
			_btnDi->setEnabled(true);
		}
		else
		{
			_btnTian->setEnabled(true);
			_btnDi->setEnabled(false);
		}

		//������ʾ����ǰ�ڵڼ�ҳ
		_tips->setString(StringUtils::format("%d/%d", currentIndex + 1, pageCount));
	}
}


//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* pageview��item                                                       */
/************************************************************************/

PictureItem::PictureItem()
{
	initArrayToNullptr();
}

PictureItem::~PictureItem()
{
	initArrayToNullptr();
}

bool PictureItem::init()
{
	if (!Layout::init())
	{
		return false;
	}

	loadUI();

	return true;
}

void PictureItem::initWithTypeList(int* typeList)
{
	auto data = Config::getInstance();

	for (int pos = 0; pos < max_battle_hero_num; ++pos)
	{
		int type = typeList[pos];

		if (type != none)
		{
			auto hero = data->getHeroCardByIndex(type);

			setHeadSprite(pos, type);
			setName(pos, hero->name);
		}
		else
		{
			//���ض����ͼƬ����
			setHeadSprite(pos);
		}
	}
}

void PictureItem::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	//����ͷ����
	for (int index = 0; index < 6; ++index)
	{
		_headSp[index] = node->getChildByTag<Sprite*>(index);
	}

	//�������ֱ�ǩ
	for (int index = startNameTag; index < endNameTag; ++index)
	{
		_nameLael[index - startNameTag] = node->getChildByTag<Text*>(index);
	}
}

void PictureItem::setHeadSprite(int pos, int type)
{
	if (Tools::betweenAnd(pos, 0, max_battle_hero_num - 1))
	{
		if (type != none)
		{
			_headSp[pos]->setSpriteFrame(StringUtils::format(headName.c_str(), type));
		}
		else
		{
			_headSp[pos]->setVisible(false);
		}
	}
	else
	{
		CCAssert(false, "'pos' out of range...");
	}
}

void PictureItem::setName(int pos, const std::string & name)
{
	if (Tools::betweenAnd(pos, 0, max_battle_hero_num - 1))
	{
		_nameLael[pos]->setString(name);
	}
	else
	{
		CCAssert(false, "'pos' out of range...");
	}
}

void PictureItem::setSelect(bool isTrue, int pos)
{
	if(Tools::betweenAnd(pos, 0, max_battle_hero_num - 1))
	{
		float scaleRate = 1.0f;

		if (isTrue)
		{
			scaleRate = 0.8f;
		}

		_headSp[pos]->setScale(scaleRate);
		_nameLael[pos]->setScale(scaleRate);
	}
	else
	{
		CCAssert(false, "'pos' out of range...");
		
		McLog mc;
		mc.addWaring("'pos' out of range...", __FILE__, __LINE__);
	}
	
}

void PictureItem::initArrayToNullptr()
{
	for (int index = 0; index < max_battle_hero_num; ++index)
	{
		_nameLael[index] = nullptr;
		_headSp[index] = nullptr;
	}
}



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* �ڲ���������������Ϣ                                                  */
/************************************************************************/

bool PictureLayer::TouchLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//��ʼ�������ص�Ϊnullptr
	_onTouchBegan = nullptr;
	_onTouchMoved = nullptr;
	_onTouchEnded = nullptr;

	//�����¼�����
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}

void PictureLayer::TouchLayer::setOnTouchBegan(std::function<void(int selectIndex)> began)
{
	_onTouchBegan = began;
}

void PictureLayer::TouchLayer::setOnTouchMoved(std::function<void(int selectIndex)> moved)
{
	_onTouchMoved = moved;
}

void PictureLayer::TouchLayer::setOnTouchEnded(std::function<void(int selectIndex, float moveDistance)> ended)
{
	_onTouchEnded = ended;
}


int PictureLayer::TouchLayer::isTouchedItem(cocos2d::Point pos)
{
	int result = none;

	for (int index = 0; index < max_battle_hero_num; ++index)
	{
		Rect rect(HeroPosition[index].x, HeroPosition[index].y, 140, 140);

		if (rect.containsPoint(pos))
		{
			result = index;
		}
	}

	return result;
}

bool PictureLayer::TouchLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Point touchPos = touch->getLocation();

	_selectIndex = isTouchedItem(touchPos);

	if (_selectIndex == none)
	{
		return false;
	}

	//�����Զ��崥����ʼ�ص�
	if (_onTouchBegan)
	{
		_onTouchBegan(_selectIndex);
	}

	return true;
}

void PictureLayer::TouchLayer::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	//�����Զ��崥���ƶ��ص�
	if (_onTouchMoved)
	{
		_onTouchMoved(_selectIndex);
	}
}

void PictureLayer::TouchLayer::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Point startPos = touch->getStartLocation();
	Point endPos = touch->getLocation();

	float dis = endPos.distance(startPos);


	//�����Զ��崥����ʼ�ص�
	if (_onTouchEnded)
	{
		_onTouchEnded(_selectIndex, dis);
	}

}
