#include "DialogManager.h"
#include "McLog.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

DialogManager* DialogManager::_instance = nullptr;

USING_NS_CC;


/************************************************************************/
/*         ����������                                                     */
/************************************************************************/
class BlockLayer : public Layer
{
public:
	CREATE_FUNC(BlockLayer);

	bool init() override
	{
		if (!Layer::init())
			return false;

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(BlockLayer::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		return true;
	}

	virtual bool onTouchBegan(Touch* touch, Event* event) override
	{
		return true;
	}
};



/************************************************************************/
/*    �Ի��������                                                        */
/************************************************************************/
DialogManager::DialogManager()
{
}

cocos2d::Node * DialogManager::createTip(std::string text, cocos2d::Color4B color, int size)
{
	//��ȡcocos stuido�༭�õ�ui�ļ�
	auto tipLayer = (CSLoader::createNode(csbName_TipLayer));

	//��ȡ��ʾ�ı����ݵ�Text�ؼ�
	auto label = tipLayer->getChildByName<ui::Text*>("text");

	Size visibleSize = Director::getInstance()->getVisibleSize();

	label->setString(text);
	label->setTextColor(color);
	label->setFontSize(size);
	tipLayer->setAnchorPoint(Point::ANCHOR_MIDDLE);
	tipLayer->setPosition(visibleSize / 2);
	
	return tipLayer;
}

DialogManager::~DialogManager()
{
}

DialogManager * DialogManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new DialogManager();

		if (!_instance)
		{
			//������־��¼
			McLog mLog;
			mLog.addError("_instance create failed...", __FILE__, __LINE__);
		}
	}

	return _instance;
}

void DialogManager::showTipDialog(std::string text, float second, cocos2d::Color4B color, int size)
{
	auto blockLayer = BlockLayer::create();
	
	//������Ļ����
	Director::getInstance()->getRunningScene()->addChild(blockLayer, 9999);

	blockLayer->addChild(createTip(text, color, size));
}

void DialogManager::destoryInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}
