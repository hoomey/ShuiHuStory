#ifndef __DIALOGMANAGER_H__
#define __DIALOGMANAGER_H__

#include "cocos2d.h"

class DialogManager{
public:
	~DialogManager();

	//���ʵ��
	static DialogManager* getInstance();

	//��ʾһ����ʾ��
	void showTipDialog(std::string text, float second = 3.0f, cocos2d::Color4B color = cocos2d::Color4B(255, 0, 0, 255), int size = 35);

	//����ʵ��
	void destoryInstance();

private:
	DialogManager();

	//����һ����ʾ�Ի���
	cocos2d::Node* createTip(std::string text, cocos2d::Color4B color, int size);

private:
	//��������
	const std::string csbName_TipLayer = "layers/Tools/tipDialog.csb";

private:
	static DialogManager* _instance;
};

#endif // DIALOGMANAGER_H_
