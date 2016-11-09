/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	DisplayListItem.h
// Author:		 Metoor
// Version: 	1.0
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __DISPLAYLISTITEM_H__
#define __DISPLAYLISTITEM_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <functional>

enum ItemLabelType {
	ILT_LEVEL,
	ILT_NAME,
	ILT_ATTRIBUTE1,
	ILT_ATTRIBUTE2
};


class DisplayListItem : public cocos2d::ui::Layout {
public:
	DisplayListItem();
	~DisplayListItem();
	CREATE_FUNC(DisplayListItem);
	virtual bool init() override;

	//���ð�ť�ص�
	void setBtnCallBack(std::function<void(cocos2d::Ref * pSender)> func);

	//���ð�ť�ı�ǩ
	void setBtnTag(const int tag);

	//���ð�ťͼƬ
	void setBtnTexture(const std::string& normal, const std::string& pressed);

	//���ö�Ӧ���͵ı�ǩ����
	void setLabelText(ItemLabelType type, const std::string& content);

	//���ö�Ӧ���͵ı�ǩ��ɫ
	void setLabelColor(ItemLabelType type, cocos2d::Color4B color);

	//����Item��ͼ��
	void setIco(const std::string& icoName, const std::string& img1Name, const std::string& img2Name);

	//����Ʒ���Ǽ�
	void setStarNum(const int n);

private:
	const std::string csbName = "layers/homeLayer/displayListItem.csb";
	const std::string icoName = "ico";
	const std::string levelLabelName = "levelLabel";
	const std::string nameLabelName = "nameLabel";
	const std::string starName = "star";
	const std::string img1Name = "img1";
	const std::string img2Name = "img2";
	const std::string text1Name = "attribute1";
	const std::string text2Name = "attribute2";
	const std::string btnName = "btn";

private:
	void loadUI();


private:
	cocos2d::ui::ImageView* _ico;		//��Ʒͼ��
	cocos2d::ui::ImageView* _star;		//�Ǽ�ͼ��
	cocos2d::ui::ImageView* _img1;		//����ͼ��
	cocos2d::ui::ImageView* _img2;		//����ͼ��
	cocos2d::ui::Text*		_level;		//�ȼ���ǩ
	cocos2d::ui::Text*		_name;		//���ֱ�ǩ
	cocos2d::ui::Text*		_attribute1;//���Ա�ǩ
	cocos2d::ui::Text*		_attribute2;//���Ա�ǩ
	cocos2d::ui::Button*	_btn;		//��ť
};

#endif // DisplayListItem_H_
