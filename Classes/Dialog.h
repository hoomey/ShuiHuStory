/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	Dialog.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/09
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef DIALOG_H_  
#define DIALOG_H_  
  
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <functional>

class Dialog : public cocos2d::Layer
{
public:
	Dialog();
	~Dialog();
	virtual bool init() override;
	CREATE_FUNC(Dialog);


	//������ʾ�ı�����ɫ
	void setContentColor(cocos2d::Color4B color);

	//�����Ƿ���ʾȡ����ť
	void setCanceBtnlDisplay(bool isDisplay);

	//������ʾ�ı�
	void setContent(const std::string & content);

	//������ʾ�ı�
	void setFontSize(int contentTextSize);

	//���öԻ���ı���
	void setTitle(const std::string& title);

	//����ȷ�ϰ�ť�ص�
	void setBtnOkCallBack(std::function<void(cocos2d::Ref * pSender)> func);

	//���������ĳ�ʼ�������㴴��
	void initDialog(const std::string & title, const std::string & content, std::function<void(cocos2d::Ref * pSender)> func);

private:
	void loadUI();

	void startAnimation();

	void onEnterTransitionDidFinish() override;

	//�Ƴ�������������Դ
	void endAnimation();

private:
	const std::string csbName = "layers/Tools/dialogLayer.csb";
	const std::string btnCloseName = "btnClose";
	const std::string btnOkName = "btnOk";
	const std::string titleName = "title";
	const std::string contentName = "content";

private:
	cocos2d::ui::Button* _btnClose;
	cocos2d::ui::Button* _btnOk;
	cocos2d::ui::Text* _title;
	cocos2d::ui::Text* _content;
};
  
#endif // DIALOG_H_ 
