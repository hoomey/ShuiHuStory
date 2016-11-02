#include "GameScene.h"
#include "ParticleLayer.h"
#include "cocostudio/CocoStudio.h"
#include "GameData.h"
#include "HomeLayer.h"


#include "TypeStruct.h"

USING_NS_CC;
using namespace ui;
using namespace std;


GameScene::GameScene()
	:_preTag(0)
{
	GameData::getInstance()->readHeroCard();
	GameData::getInstance()->readEquipment();
}

GameScene::~GameScene()
{
	GameData::getInstance()->saveUniqueIdentifierNumToFile();
	GameData::getInstance()->saveEquipment();
	GameData::getInstance()->saveHeroCard();
}

Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	loadUI();

	//��ʼ������Ϊnullptr
	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		_layerPointer[index] = nullptr;
	}

	//�����ֻ����ؼ��ĵ���¼�
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//����������Ч
	auto paricle = ParticleLayer::create();
	addChild(paricle, particle_z_order);

	//����Ĭ��ת��Home����
	_layerPointer[0] = HomeLayer::create();
	addChild(_layerPointer[0]);

	return true;
}

//�ֻ����ؼ�����ص�
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::getInstance()->end();
	}
}

void GameScene::loadUI()
{
	//������Ϸ����
	auto bgLayer = CSLoader::createNode(csbName);
	addChild(bgLayer);

	//���ز˵���
	auto menuLayer = CSLoader::createNode(csbMenuName);
	addChild(menuLayer, menu_z_order);

	//Ϊ�˵��󶨻ص�����
	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		auto menu = menuLayer->getChildByTag<Button*>(index);
		menu->addTouchEventListener(CC_CALLBACK_2(GameScene::menuCallBack, this));
	}
}

void GameScene::menuCallBack(Ref * pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		int currentTag = dynamic_cast<Button*>(pSender)->getTag();

		if(_preTag != currentTag && _preTag != none)
		{
			//����ϴε���������εĲ�һ�����Ҳ�����none������Ҫ������ǰ�����㣬Ȼ���ͷ��ϴε�������
			log("--current:%d--pre:%d", currentTag, _preTag);
		}

		_preTag = currentTag;

	}
}
