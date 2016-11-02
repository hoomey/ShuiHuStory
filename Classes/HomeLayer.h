#ifndef __HOMELAYER_H__
#define __HOMELAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#define ARRAY_SIZE 6	//�˵��ĸ���

class HomeLayer : public cocos2d::Layer{
public:
	HomeLayer();
	~HomeLayer();
	virtual bool init() override;
	CREATE_FUNC(HomeLayer);

private:
	void loadUI();

	void menuCallBack(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type);

private:
	//��������
	const std::string csbName = "layers/homeLayer/homeLayer.csb";
	const int start = -1;

private:
	//��¼�����һ�ε���Ĳ˵�Tag
	int _preTag;

	//�洢ÿ���˵���Ӧ�Ĳ�ָ��
	cocos2d::Layer* _layerPointer[ARRAY_SIZE];
};

#endif // HOMELAYER_H_
