#ifndef __AUDIOMANAGER_H__
#define __AUDIOMANAGER_H__

#include <string>
#include "SimpleAudioEngine.h"

class AudioManager{
public:
	~AudioManager();

	static AudioManager* getInstance();
	void destoryInstance();

	//ͨ�����ֲ�����Ч
	void playEffect(std::string name);

	//ͨ�����ֲ��ű�������
	void playBackgroundMusic(std::string name, bool isLoop = true);

	//����Ƿ�����־
	bool getIsMute();
	
	//�����Ƿ���
	void setIsMute(bool isMute);

public:
	//����/��Ч������
	const std::string bgFirstScene = "audio/wellcomeBg.mp3";


	//���ֲ�������ʵ��
	CocosDenshion::SimpleAudioEngine* _simpleAudioEngine;

private:
	AudioManager();

private:
	bool _isMute;
	static AudioManager* _instance;
};

#endif // AUDIOMANAGER_H_
