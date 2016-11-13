/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	LevelupRewardItem.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/12
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef LEVELUPREWARDITEM_H_  
#define LEVELUPREWARDITEM_H_  
  
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <functional>

class LevelupRewardItem : public cocos2d::ui::Layout
{
public:
	LevelupRewardItem();
	~LevelupRewardItem();
	virtual bool init() override;
	CREATE_FUNC(LevelupRewardItem);

	//���ð�ť��ǩ
	void setBtnTag(int tag);

	//���ý�������Ϣ
	void setRewardString(int level, int diamond, int gold);

	void setBtnCallback(std::function<void(cocos2d::Ref* pSender)> func);

	//������ȡ��ť
	void setBtnEnable(bool isEnable);

private:
	void loadUI();


private:
	const std::string csbName = "layers/homeLayer/levelupRewardItem.csb";
	const std::string btnGetName = "btnGet";
	const std::string diamondLabelName = "diamondLabel";
	const std::string goldLbaelName = "goldLabel";
	const std::string titleLbaelName = "title";

private:
	cocos2d::ui::Button* _btnGet;
	cocos2d::ui::Text* _diamondLabel;
	cocos2d::ui::Text* _goldLabel;
	cocos2d::ui::Text* _titleLabel;

	//���水ť�ص�
	std::function<void(cocos2d::Ref* pSender)> _func;
};
  
#endif // LevelupRewardItem_H_ 
