#include "AudioManager.h"
#include "cocos2d.h"
#include "McLog.h"

AudioManager* AudioManager::_instance = nullptr;

USING_NS_CC;
using namespace std;

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
	//�����Ƿ����ı�־
	UserDefault::getInstance()->setBoolForKey("isMute", _isMute);
}

AudioManager * AudioManager::getInstance()
{
	if (!_instance)
	{
		_instance = new (nothrow)AudioManager();

		if (!_instance)
		{
			McLog log;
			log.addError("_instance create failed...", __FILE__, __LINE__);
		}
		else
		{
			//��ȡ�Ƿ�����־
			bool mute = UserDefault::getInstance()->getBoolForKey("isMute", false);
			_instance->setIsMute(mute);

			//����SimpleAudioEngineʵ��������
			_instance->_simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
		}
	}

	return _instance;
}

void AudioManager::destoryInstance()
{
	if (_instance)
	{
		CC_SAFE_DELETE(_instance);
	}

	_simpleAudioEngine->end();
}

void AudioManager::playEffect(std::string name)
{
	if (!_isMute)
	{
		_simpleAudioEngine->playEffect(name.c_str());
	}
}

void AudioManager::playBackgroundMusic(std::string name, bool isLoop)
{
	if (!_isMute)
	{
		_simpleAudioEngine->playBackgroundMusic(name.c_str(), isLoop);
	}
}

bool AudioManager::getIsMute()
{
	return _isMute;
}

void AudioManager::setIsMute(bool isMute)
{
	_isMute = isMute;
}
