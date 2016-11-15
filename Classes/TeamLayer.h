/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	TeamLayer.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/14
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef TEAMLAYER_H_  
#define TEAMLAYER_H_  
  
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ConstantDefine.h"

class DisplayLayer;

class TeamLayer : public cocos2d::Layer
{
public:
	TeamLayer();
	~TeamLayer();
	virtual bool init() override;
	CREATE_FUNC(TeamLayer);

private:
	void loadUI();

	//��ʾ��սӢ��
	void updateData();

	//���Ѿ��ϳ���Ӣ��item�İ�ť����������
	void setUnBattleBtn();

	//���pointѡ�����Ǹ�Ӣ��ͷ�񣬷���-1��ʾû��ѡ���κ�ͷ��
	int getHeroIcoisContainPoint(cocos2d::Point& point);

	//ע�ᴥ���¼������ص�
	void addTouchEventListener();

	//������ʼ�ص�
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	//�����ƶ��ص�
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);

	//���������ص�
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

private:
	//csb�����ļ�����Ŀؼ�����
	const std::string csbName = "layers/teamLayer/teamLayer.csb";
	const std::string nameLabel = "name_%d";
	const std::string heroIcoSprite = "hero_%d";
	const std::string heroName = "head%d.png";
	const std::string btnSaveName = "btnSave";
	const int default_z_order = 10;
	const int select_z_order = 1000;

	//Ӣ��ͼ���λ��
	const cocos2d::Point HeroIcoPos[max_battle_hero_num] = { cocos2d::Point(160, 660), cocos2d::Point(320, 660), cocos2d::Point(480, 660),
		cocos2d::Point(160, 440) , cocos2d::Point(320, 440) , cocos2d::Point(480, 440) };

	//Ӣ�����ֵ�λ��
	const cocos2d::Point HeroNamePos[max_battle_hero_num] = { cocos2d::Point(160, 550), cocos2d::Point(320, 550), cocos2d::Point(480, 550),
		cocos2d::Point(160, 330) , cocos2d::Point(320, 330) , cocos2d::Point(480, 330) };

	//Ӣ�����ֵ�Ӣ��ͼ��ľ���
	const cocos2d::Point distanceNameToIco = cocos2d::Point(0, 110);

private:
	//��¼��ǰѡ�е�ͼ���߼���ǩ��
	int _selectTag;

	DisplayLayer* _displayLayer;
	cocos2d::ui::Text* _nameLabel[max_battle_hero_num];
	cocos2d::Sprite* _heroIco[max_battle_hero_num];

};
  
#endif // TEAMLAYER_H_ 
