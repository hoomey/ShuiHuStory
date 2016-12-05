/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	PVPStartLayer.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/12/03
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef PVPSTARTLAYER_H_  
#define PVPSTARTLAYER_H_  

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "TypeStruct.h"

class PVPStartLayer : public cocos2d::Layer
{
public:
	PVPStartLayer();
	~PVPStartLayer();
	virtual bool init() override;
	CREATE_FUNC(PVPStartLayer);

private:
	void loadUI();

	void ballRunAction();
	void stopBallAction();

	//����ҷ������Ӣ�����ݣ�json��
	std::string getBattleHeroData();

	//��ʾ�ı�
	void disPlayTips(const std::string &content, cocos2d::Color4B color = cocos2d::Color4B::MAGENTA);

	//��Ӵ���ս����������Ϣ
	void addCreteSceneMessageListener();

	//������ӶϿ���Ϣ
	void addDisconnectMessageListener();

	//���socket������Ϣ
	void addConnectMessageListener();

	void onEnter() override;

	void startAnimation();
	void endAnimation();

private:
	const std::string csbName = "layers/warLayer/pvpLayer.csb";
	const std::string btnCloseName = "btnClose";
	const std::string btnStartName = "btnStart";
	const std::string ballName = "ball";
	const std::string tipsName = "tips";

	const int actionTag = 1236;	//С��Ķ�����ǩ
	const int socketLayerTag = 3216;	//�������ݸ��������Ĳ�ı�ǩ
	const int base_gold = 1000;	//ƥ��������Ľ��

	const int ball_start_pos_x = 100;
	const int ball_end_pos_x = 550;
	const int ball_pos_y = 620;

private:
	//����������Ҫ�Ľ��
	int _gold;

	//�Ƿ��ǿ�ʼƥ�䰴ť
	bool _isStartBtn;

	//����ӷ�������ȡ������
	PVPData _pvpData;

	cocos2d::ActionInterval* _action;
	cocos2d::ui::Text* _tips;
	cocos2d::Sprite* _ball;
	cocos2d::ui::Button* _btnClose, *_btnStart;
};
  
#endif // PVPSTARTLAYER_H_ 