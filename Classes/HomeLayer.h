/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	HomeLayer.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __HOMELAYER_H__
#define __HOMELAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#define ARRAY_SIZE 6	//�˵��ĸ���


enum HomeMenuType
{
	HMT_EQUIPMENT,
	HMT_HERO,
	HMT_LOGIN,
	HMT_LEVEL_UP,
	HMT_ABOUT,
	HMT_AUDIO
};

class HomeLayer : public cocos2d::Layer{
public:
	HomeLayer();
	~HomeLayer();
	virtual bool init() override;
	CREATE_FUNC(HomeLayer);

private:
	void loadUI();

	//ע������û������¼�
	void addUpdateUserDataEventListener();

	//�����û�����
	void updateUserData();

	//�����˵���Ӧ�Ĳ˵���
	cocos2d::Layer* createMenuLayer(HomeMenuType type);
	
	void menuCallBack(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type);

private:
	//��������
	const std::string csbName = "layers/homeLayer/homeLayer.csb";
	const std::string levelNumName = "levelNum";
	const std::string expNumName = "expNum";
	const std::string goldNumName = "goldNum";
	const std::string diamodNumName = "diamondNum";
	const std::string expBarName = "expBar";

	const int start = -1;

private:
	//��¼���ϴε���Ĳ˵�ָ��
	cocos2d::ui::Button* _preMenu;

	cocos2d::ui::Text *_goldLabel, *_dianmodLabel, *_levelLabel, *_expLabel;
	cocos2d::ui::LoadingBar* _expBar;

	//�洢ÿ���˵���Ӧ�Ĳ�ָ��
	cocos2d::Layer* _layerPointer[ARRAY_SIZE];
};

#endif // HOMELAYER_H_
