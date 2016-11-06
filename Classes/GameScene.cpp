#include "GameScene.h"
#include "ParticleLayer.h"
#include "cocostudio/CocoStudio.h"
#include "GameData.h"
#include "HomeLayer.h"
#include "AudioManager.h"
#include "ConstantDefine.h"

USING_NS_CC;
using namespace ui;
using namespace std;


GameScene::GameScene()
	:_preMenu(nullptr)
{
	auto gameData = GameData::getInstance();
	gameData->readHeroCard();
	gameData->readEquipment();

	AudioManager::getInstance()->preLoadGlobalAudio();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("head.plist", "head.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("equipment.plist", "equipment.png");
}

GameScene::~GameScene()
{
	auto gameData = GameData::getInstance();
	gameData->saveUniqueIdentifierNumToFile();
	gameData->saveEquipment();
	gameData->saveHeroCard();

	auto audio = AudioManager::getInstance();
	audio->unLoadGlobalEffect();

	gameData->destoryInstance();
	audio->destoryInstance();

	//��ΪButton�����ü��������Խ�����ȫ���ÿ�
	initArrayToNullptr();
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
	if (!Layer::init())
	{
		return false;
	}

	loadUI();

	initArrayToNullptr();

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
	_preMenu->setEnabled(false);

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

void GameScene::initArrayToNullptr()
{
	//��ʼ������Ϊnullptr
	for (int index = 0; index < ARRAY_SIZE; ++index)
	{
		_layerPointer[index] = nullptr;
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

		//��Ϊ��ʼĬ��ѡ�е�һ����ť
		if (index == 0)
		{
			_preMenu = menu;
		}
	}
}

void GameScene::menuCallBack(Ref * pSender, Widget::TouchEventType type)
{

	if (type == Widget::TouchEventType::BEGAN)
	{
		//���ŵ����Ч
		auto audio = AudioManager::getInstance();
		audio->playEffect(audio->clickEffect);
	}

	if (type == Widget::TouchEventType::ENDED)
	{
		//��ȡ��ǰ�ĵ���˵���tag���ϴε����Tag
		auto currentMenu = dynamic_cast<Button*>(pSender);
		int currentTag = currentMenu->getTag();
		int preTag = _preMenu->getTag();

		if (preTag != currentTag && preTag != none)
		{
			//����ϴε���������εĲ�һ�����Ҳ�����none������Ҫ������ǰ�����㣬Ȼ���ͷ��ϴε�������
			log("--current:%d--pre:%d", currentTag, preTag);
		}

		//�������������ͬ�Ĳ˵������õ�ǰ�Ĳ˵��������һ�εĲ˵�
		_preMenu->setEnabled(true);
		currentMenu->setEnabled(false);

		//������ε���Ĳ˵�ָ������
		_preMenu = currentMenu;

	}
}
