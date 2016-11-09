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

	//�����˵���Ӧ�Ĳ˵���
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
