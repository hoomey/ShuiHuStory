#include "WorldMapLayer.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "BlockLayer.h"
#include "ConstantDefine.h"
#include "MapListLayer.h"

USING_NS_CC;
using namespace ui;
using namespace std;

WorldMapLayer::WorldMapLayer()
{
}

WorldMapLayer::~WorldMapLayer()
{
}

bool WorldMapLayer::init()
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

void WorldMapLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_scrollView = node->getChildByName<ScrollView*>(scrollViewName);
	_btnClose = dynamic_cast<Button*>(_scrollView->getChildByName(btnCancelName));

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

	for (int index = 0; index < btnMenuEndTag; ++index)
	{
		auto btn = dynamic_cast<Button*>(_scrollView->getChildByTag(index));
		btn->addTouchEventListener(CC_CALLBACK_2(WorldMapLayer::menuCallFun, this));
	}
}

void WorldMapLayer::startAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//����λ������Ļ����
	this->setPosition(-visibleSize.width, 0);

	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(0, 0)), 0.2f);

	//���ƶ���ɺ���ʾ����������
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		//��ʾ����������
		dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(160.0f);
	}));

	this->runAction(ani);
}

void WorldMapLayer::endAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�����ش�������
	dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(0.0f);

	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(-visibleSize.width, 0)), 0.2f);

	//������ƶ����ͷ���Դ
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}

void WorldMapLayer::onEnter()
{
	Layer::onEnter();

	startAnimation();
}

void WorldMapLayer::menuCallFun(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	auto btn = dynamic_cast<Button*>(pSender);
	
	if (type == Widget::TouchEventType::BEGAN)
	{
		AudioManager::getInstance()->playClickEffect();
		
		//ѡ����С
		btn->setScale(0.8f);
	}

	if (type == Widget::TouchEventType::CANCELED)
	{
		//ȡ���ָ�ԭʼ��С
		btn->setScale(1.0f);
	}

	if (type == Widget::TouchEventType::ENDED)
	{
		//�����ָ�ԭʼ��С
		btn->setScale(1.0f);

		int tag = btn->getTag();
		
		auto layer = MapListLayer::create();
		layer->initWithMapIndex(tag);
		addChild(layer);
	}
}
