/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	AudioLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/13
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "AudioLayer.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"
#include "BlockLayer.h"
#include "ConstantDefine.h"
#include "AudioManager.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;

AudioLayer::AudioLayer()
{
}

AudioLayer::~AudioLayer()
{
}

bool AudioLayer::init()
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

	initBtnIco();

	return true;
}

void AudioLayer::loadUI()
{
	auto node = CSLoader::createNode(csbName);
	addChild(node);

	_btnClose = node->getChildByName<Button*>(btnCloseName);
	_btnEffect = node->getChildByName<Button*>(btnEffectName);
	_btnMusic = node->getChildByName<Button*>(btnMusicName);

	//�رհ�ť�ص�
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

	//��Ч��ť����ص�
	_btnEffect->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			effect();
		}
	});

	//���ְ�ť����ص�
	_btnMusic->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			AudioManager::getInstance()->playClickEffect();
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			music();
		}
	});

}

void AudioLayer::initBtnIco()
{
	auto audio = AudioManager::getInstance();

	if (audio->getIsBgMute())
	{
		//���óɹر�״̬ͼ��
		_btnMusic->loadTextures(sound_off_1, sound_off_2, sound_off_2, Widget::TextureResType::PLIST);
	}
	else
	{
		//���óɴ�״̬ͼ��
		_btnMusic->loadTextures(sound_on_1, sound_on_2, sound_on_2, Widget::TextureResType::PLIST);
	}

	if (audio->getIsEffectMute())
	{
		_btnEffect->loadTextures(sound_off_1, sound_off_2, sound_off_2, Widget::TextureResType::PLIST);
	}
	else
	{
		_btnEffect->loadTextures(sound_on_1, sound_on_2, sound_on_2, Widget::TextureResType::PLIST);
	}
}

void AudioLayer::music()
{
	auto audio = AudioManager::getInstance();

	//�����״̬ȡ��
	bool isBgMute = !audio->getIsBgMute();

	audio->setBgMute(isBgMute);

	if (isBgMute)
	{
		if (audio->_simpleAudioEngine->isBackgroundMusicPlaying())
		{
			audio->_simpleAudioEngine->stopBackgroundMusic();
		}
		//�������ֹر�״̬ͼ��
		_btnMusic->loadTextures(sound_off_1, sound_off_2, sound_off_2, Widget::TextureResType::PLIST);
	}
	else
	{
		if (!audio->_simpleAudioEngine->isBackgroundMusicPlaying())
		{
			audio->playBackgroundMusic(firstSceneMusicName);
		}

		//���ñ������ִ�״̬ͼ��
		_btnMusic->loadTextures(sound_on_1, sound_on_2, sound_on_2, Widget::TextureResType::PLIST);
	}
}

void AudioLayer::effect()
{
	auto audio = AudioManager::getInstance();

	bool isEffectMute = !audio->getIsEffectMute();

	audio->setEffectMute(isEffectMute);

	if (isEffectMute)
	{
		//������Ч�ر�״̬ͼ��
		_btnEffect->loadTextures(sound_off_1, sound_off_2, sound_off_2, Widget::TextureResType::PLIST);
	}
	else
	{
		//������Ч��״̬ͼ��
		_btnEffect->loadTextures(sound_on_1, sound_on_2, sound_on_2, Widget::TextureResType::PLIST);
	}
}

void AudioLayer::startAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//����λ������Ļ����
	this->setPosition(visibleSize.width, 0);
	
	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(0, 0)), 0.2f);

	//���ƶ���ɺ���ʾ����������
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		//��ʾ����������
		dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(160.0f);
	}));

	this->runAction(ani);
}

void AudioLayer::endAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�����ش�������
	dynamic_cast<BlockLayer*>(this->getChildByName(blockTagName))->setOpacity(0.0f);

	//�ƶ�����Ļ����
	auto move = EaseIn::create(MoveTo::create(0.5f, Point(visibleSize.width, 0)), 0.2f);

	//������ƶ����ͷ���Դ
	auto ani = Sequence::createWithTwoActions(move, CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
	}));

	this->runAction(ani);
}

void AudioLayer::onEnterTransitionDidFinish()
{
	startAnimation();
}
