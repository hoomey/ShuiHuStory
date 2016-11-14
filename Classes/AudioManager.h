/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	AudioManager.h
// Author:		 Metoor
// Version: 	1.0
// Date: 		2016/10/20
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __AUDIOMANAGER_H__
#define __AUDIOMANAGER_H__

#include <string>
#include "SimpleAudioEngine.h"

class AudioManager{
public:
	~AudioManager();

	static AudioManager* getInstance();
	
	//�ж��Ƿ��Ѿ����ɸõ�����
	static bool isNullptr();
	
	//ͨ�����ֲ�����Ч
	unsigned int playEffect(std::string name);

	//ͨ�����ֲ��ű�������
	unsigned int playBackgroundMusic(std::string name, bool isLoop = true);

	void destoryInstance();

	//���ŵ�һ�ε�½ʱ�ı�������
	unsigned int playFirstSceneBgMusic();

	//���Ų˵������Ч
	unsigned int playClickEffect();

	//Ԥ����ȫ����Ч�ͱ�������
	void preLoadGlobalAudio();

	//ж��ȫ����Ч�ͱ�������
	void unLoadGlobalEffect();

	//����Ƿ�����־
	bool getIsEffectMute();
	bool getIsBgMute();
	
	//�����Ƿ���
	void setEffectMute(bool isEffectMute);
	void setBgMute(bool isBgMute);

public:

	//���ֲ�������ʵ��
	CocosDenshion::SimpleAudioEngine* _simpleAudioEngine;

private:
	AudioManager();

private:
	//�Ƿ�������Ч
	bool _isEffectMute;
	//�Ƿ����ñ�������
	bool _isbgMusicMute;

	static AudioManager* _instance;
};

#endif // AUDIOMANAGER_H_
