/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	DialogManager.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __DIALOGMANAGER_H__
#define __DIALOGMANAGER_H__

#include "cocos2d.h"
#include <functional>


class DialogManager{
public:
	~DialogManager();

	//���ʵ��
	static DialogManager* getInstance();

	//��ʾһ����ģ̬��ʾ��
	void showTips(const std::string& content, cocos2d::Color4B color = cocos2d::Color4B::RED, int size = 35);

	//��ʾģ̬�Ի���
	void showDialog(const std::string& title, const std::string& content, std::function<void(cocos2d::Ref * pSender)> func, bool isDisplayCancelBtn = true, cocos2d::Color4B color = cocos2d::Color4B::RED, int contentSize = 35);

	//����ʵ��
	void destoryInstance();

private:
	DialogManager();

private:
	//ʵ��
	static DialogManager* _instance;
};

#endif // DIALOGMANAGER_H_
