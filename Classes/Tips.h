/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	Tips.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/09
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef TIPS_H_  
#define TIPS_H_  
  
#include "cocos2d.h"
#include "ui/CocosGUI.h"


class Tips : public cocos2d::Layer
{
public:
	Tips();
	~Tips();
	virtual bool init() override;
	CREATE_FUNC(Tips);

	//�����ı�
	void setContent(const std::string& content);

	//�����ı���С
	void setContentFontSize(int contentSize);
	
	//�����ı���ɫ
	void setContentColor(cocos2d::Color4B &color);

	//������������
	void initTips(const std::string& content, cocos2d::Color4B color = cocos2d::Color4B::RED, int contentSize = 35);

private:
	void loadUI();
	
	void onEnterTransitionDidFinish() override;

private:
	const std::string csbName = "layers/Tools/tipLayer.csb";
	const std::string  contenName = "content";

private:
	cocos2d::ui::Text* _content;

};
  
#endif // TIPS_H_ 
