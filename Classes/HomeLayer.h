#ifndef __HOMELAYER_H__
#define __HOMELAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#define ARRAY_SIZE 6	//�˵��ĸ���


enum HomeMenuType
{
	EQUIPMENT,
	HERO,
	LOGIN,
	LEVEL_UP,
	ABOUT,
	AUDIO
};

class HomeLayer : public cocos2d::Layer{
public:
	HomeLayer();
	~HomeLayer();
	virtual bool init() override;
	CREATE_FUNC(HomeLayer);

private:
	void loadUI();
	cocos2d::Layer* createMenuLayer(HomeMenuType type);
	void menuCallBack(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type);

private:
	//��������
	const std::string csbName = "layers/homeLayer/homeLayer.csb";
	const int start = -1;

private:
	//��¼���ϴε���Ĳ˵�ָ��
	cocos2d::ui::Button* _preMenu;

	//�洢ÿ���˵���Ӧ�Ĳ�ָ��
	cocos2d::Layer* _layerPointer[ARRAY_SIZE];
};

#endif // HOMELAYER_H_
