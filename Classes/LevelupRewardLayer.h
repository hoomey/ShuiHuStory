/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	LevelupRewardLayer.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/11
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef LEVELUPREWARDLAYER_H_  
#define LEVELUPREWARDLAYER_H_  
  
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ConstantDefine.h"

class LevelupRewardLayer : public cocos2d::Layer
{
public:
	LevelupRewardLayer();
	~LevelupRewardLayer();
	virtual bool init() override;
	CREATE_FUNC(LevelupRewardLayer);

private:
	void loadUI();

	void loadItem();

	//��ȡ�û���ȡ��¼ 
	void readData();

	//�����û���ȡ��¼
	void saveData();

	void startAnimation();

	void endAnimation();

	void onEnterTransitionDidFinish() override;

private:
	const std::string csbName = "layers/homeLayer/levelupRewardLayer.csb";
	const std::string btnCloseName = "btnClose";
	const std::string listViewName = "listView";
	

private:
	//��������Ƿ���ȡ������
	bool _isGetGift[itemCount];

	cocos2d::ui::Button* _btnClose;
	cocos2d::ui::ListView* _listView;

	
};
  
#endif // LEVELUPREWARDLAYER_H_ 
