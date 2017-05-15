/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	PVPStartLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/12/03
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "PVPStartLayer.h"
#include "cocostudio/CocoStudio.h"
#include "BlockLayer.h"
#include "GameData.h"
#include "AudioManager.h"
#include "I18N.h"
#include "TypeStruct.h"
#include "ClientLayer.h"
#include "HeroCard.h"
#include "McLog.h"
#include "PVPBattleScene.h"
#include "Tools.h"

USING_NS_CC;
using namespace ui;

PVPStartLayer::PVPStartLayer()
	:_isStartBtn(true),
	_ball(nullptr)
{
}

PVPStartLayer::~PVPStartLayer()
{
}

bool PVPStartLayer::init()
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

	//ע����Ϣ
	addCreteSceneMessageListener();
	addDisconnectMessageListener();
	addConnectMessageListener();

	auto data = GameData::getInstance();
	auto i18n = I18N::getInstance();

	//���㱾�α�����Ҫ���ĵĽ��������ʽ����1 + �ȼ�/10��*base_gold
	_gold = (1 + data->getLevel() / 10) * base_gold;

	if (data->getGold() < _gold)
	{
		//��Ҳ��������ð�ť����ʾ��ʾ��
		_btnStart->setEnabled(false);
		disPlayTips(StringUtils::format(i18n->getStringByKey(pvpNoMoney).c_str(), _gold), Color4B::RED);
	}
	else
	{
		//��ʾ��ʾ��
		disPlayTips(StringUtils::format(i18n->getStringByKey(pvpTips).c_str(), _gold, (int)(_gold * 2 * 0.9f)), Color4B::BLUE);
	}

	return true;
}

void PVPStartLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_btnClose = node->getChildByName<Button*>(btnCloseName);
	_btnStart = node->getChildByName<Button*>(btnStartName);
	_tips = node->getChildByName<Text*>(tipsName);
	_ball = node->getChildByName<Sprite*>(ballName);

	//�رհ�ť�¼��ص�
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

	//��ʼƥ�䰴ť�ص�
	_btnStart->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::BEGAN == type)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (Widget::TouchEventType::ENDED == type)
		{
			auto i18n = I18N::getInstance();

			if (_isStartBtn)
			{
				auto layer = ClientLayer::create();
				layer->setTag(socketLayerTag);
				layer->initSocket(6010);
				addChild(layer);

				//������ĳɡ�ȡ����
				_btnStart->loadTextures(btnCancel1, btnCancel2, btnCancel2, Widget::TextureResType::PLIST);

				//��ʾһʱ�ƥ������С�
				disPlayTips(i18n->getStringByKey(connecting), Color4B::MAGENTA);
				ballRunAction();
			}
			else
			{
				//������Ӳ��Ѿ���ӵ���ǰ�����Ƴ�
				auto layer = dynamic_cast<ClientLayer*>(getChildByTag(socketLayerTag));
				if (layer != nullptr)
				{
					layer->removeFromParentAndCleanup(true);
				}

				//������ĳɡ���ʼƥ�䡱
				_btnStart->loadTextures(btnStart1, btnStart2, btnStart2, Widget::TextureResType::PLIST);

				stopBallAction();

				//��ʾһʱ��û�ȡ����
				disPlayTips(i18n->getStringByKey(userCancel), Color4B::BLUE);
			}

			_isStartBtn = !_isStartBtn;
		}
	});
}

void PVPStartLayer::ballRunAction()
{
	//�����ƶ�����
	auto move = MoveBy::create(3.0f, Vec2(ball_end_pos_x - ball_start_pos_x, 0));
	auto move_back = move->reverse();

	//���������˶�
	auto move_ease = EaseBounceInOut::create(move);
	auto move_ease_back = move_ease->reverse();

	//��ʱ
	auto delay = DelayTime::create(0.25f);

	auto seq = Sequence::create(move_ease, delay, move_ease_back, delay->clone(), NULL);
	auto action = RepeatForever::create(seq);
	action->setTag(actionTag);

	_ball->setVisible(true);
	_ball->runAction(action);
}

void PVPStartLayer::stopBallAction()
{
	_ball->stopActionByTag(actionTag);
	_ball->setVisible(false);
	_ball->setPosition(Point(ball_start_pos_x, ball_pos_y));
}

string PVPStartLayer::getBattleHeroData()
{
	std::string json = "{\"role\":[";
	char buffer[255];

	memset(buffer, 0, sizeof(buffer));

	//Ӣ�۳�ս�б�
	auto data = GameData::getInstance();

	for (unsigned pos = 0; pos < max_battle_hero_num; ++pos)
	{
		int heroId = data->getBattleHeroId(pos);

		if (heroId != -1)
		{
			auto property = data->getHeroCardById(heroId)->getProperty();

			//���������͵�ֵת�����ַ���
			string isMagic = "false";
			if (property->isMagic)
			{
				isMagic = "true";
			}

			std::sprintf(buffer, "{\"t\":%d,\"p\":%d,\"hp\":%d,\"ap\":%d,\"mp\":%d,\"df\":%d,\"mdf\":%d,\"ai\":%d,\"si\":%d,\"sp\":%d,\"cr\":%d,\"br\":%d,\"cd\":%d,\"im\":%s},",
				property->type, pos, property->hp, property->ap, property->mp,
				property->defend, property->magicDefend, property->attackId, property->skillId, property->speed, 
				property->critRate, property->blockRate, Tools::percentToInt(property->critDamage), isMagic.c_str());
		}
		else
		{
			std::sprintf(buffer, "{\"t\":%d,\"p\":%d,\"hp\":%d,\"ap\":%d,\"mp\":%d,\"df\":%d,\"mdf\":%d,\"ai\":%d,\"si\":%d,\"sp\":%d,\"cr\":%d,\"br\":%d,\"cd\":%d,\"im\":%s},",
				none, pos, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "false");
		}

		json += buffer;
	}

	json.pop_back();

	json += "]}";

	return json;
}

void PVPStartLayer::disPlayTips(const std::string & content, cocos2d::Color4B color)
{
	_tips->setString(content);
	_tips->setTextColor(color);
}

void PVPStartLayer::addCreteSceneMessageListener()
{
	//ע������pvpս���¼�
	auto listen = EventListenerCustom::create(msg_create_pvp_scene, [&](EventCustom* event) {
		_pvpData = *(PVPData*)(event->getUserData());
		_pvpData.gold = _gold;

		auto i18n = I18N::getInstance();
		
		//������ĳɡ���ʼƥ�䡱
		_btnStart->loadTextures(btnStart1, btnStart2, btnStart2, Widget::TextureResType::PLIST);
		
		stopBallAction();
		
		disPlayTips(StringUtils::format(i18n->getStringByKey(pvpTips).c_str(), _gold, (int)(_gold * 2 * 0.9f)), Color4B::BLUE);
		
		_isStartBtn = !_isStartBtn;

		//����ս������
		auto scene = PVPBattleScene::createScene(&_pvpData);
		Director::getInstance()->pushScene(scene);
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
}

void PVPStartLayer::addDisconnectMessageListener()
{
	//ע�����ӶϿ��¼�
	auto listen = EventListenerCustom::create(msg_socket_disconnect, [&](EventCustom* event) {
		auto i18n = I18N::getInstance();
		
		//������ĳɡ���ʼƥ�䡱
		_btnStart->loadTextures(btnStart1, btnStart2, btnStart2, Widget::TextureResType::PLIST);

		stopBallAction();

		disPlayTips(i18n->getStringByKey(netError), Color4B::RED);

		_isStartBtn = !_isStartBtn;
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
}

void PVPStartLayer::addConnectMessageListener()
{
	//ע�ᣬsocket��ʼ����״̬��Ϣ��0��ʾ�ɹ���1��ʾʧ��
	auto listen = EventListenerCustom::create(msg_socket_connect, [&](EventCustom* event) {
		int result = ((int)event->getUserData());
		
		if (result == 0)
		{
			//���ӳɹ����������ݸ�������
			auto layer = dynamic_cast<ClientLayer*>(getChildByTag(socketLayerTag));
			if (layer != nullptr)
			{
				auto data = getBattleHeroData();
				layer->sendMessage(data, 0);
			}
			else
			{
				//���ӳɹ�������û�л�ȡ��socket����Layer����
				McLog mc;
				mc.addError("socket ready, but can not get socket layer...", __FILE__, __LINE__);
			}
		}
		else
		{
			//����ʧ��
			auto i18n = I18N::getInstance();

			//������ĳɡ���ʼƥ�䡱
			_btnStart->loadTextures(btnStart1, btnStart2, btnStart2, Widget::TextureResType::PLIST);

			stopBallAction();

			disPlayTips(i18n->getStringByKey(netError), Color4B::RED);

			_isStartBtn = !_isStartBtn;
		}
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
}

void PVPStartLayer::onEnter()
{
	Layer::onEnter();

	startAnimation();
}

void PVPStartLayer::startAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//����λ������Ļ����
	this->setPosition(visibleSize.width, 0);

	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(0, 0)), 0.2f);

	//���ƶ���ɺ���ʾ����������
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		//��ʾ����������
		dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(bl_opacity_on);
	}));

	this->runAction(ani);
}

void PVPStartLayer::endAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�����ش�������
	dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(bl_opacity_off);

	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(visibleSize.width, 0)), 0.2f);

	//������ƶ����ͷ���Դ
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}
