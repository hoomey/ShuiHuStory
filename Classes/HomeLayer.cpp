#include "HomeLayer.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace std;

HomeLayer::HomeLayer()
	:_preTag(start)
{
}

HomeLayer::~HomeLayer()
{
}

bool HomeLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	loadUI();

	//��ʼ������Ϊnullptr
	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		_layerPointer[index] = nullptr;
	}

	return true;
}

void HomeLayer::loadUI()
{
	//���ر༭�õ���ҳ�����ļ�
	auto homeLayer = CSLoader::createNode(csbName);
	addChild(homeLayer);

	//�󶨲˵��Ļص�����
	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		auto menu = homeLayer->getChildByTag<Button*>(index);
		menu->addTouchEventListener(CC_CALLBACK_2(HomeLayer::menuCallBack, this));
	}
}

void HomeLayer::menuCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		int currentTag = dynamic_cast<Button*>(pSender)->getTag();
		
		if (start == _preTag)
		{
			//��һ������ֻ��Ҫ������Ӧ�Ĳ�
			log("----%d", currentTag);
		}
		else if (_preTag != currentTag)
		{
			//���ǵ�һ��������Ҫ�����ϴε���Ķ�ӦTag�Ĳ�
			log("--current:%d--pre:%d", currentTag, _preTag);
		}

		
		_preTag = currentTag;
	}
}
