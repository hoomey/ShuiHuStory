/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	PageViewItem.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/15
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef PAGEVIEWITEM_H_  
#define PAGEVIEWITEM_H_  
  
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ConstantDefine.h"
#include <functional>

class HeroCard;


class PageViewItem : public cocos2d::ui::Layout
{
public:
	PageViewItem();
	~PageViewItem();
	virtual bool init() override;
	CREATE_FUNC(PageViewItem);

	//����Ӣ�۵�Id����ʼ��item����ʾ����
	void initWithHeroId(int heroId);

	void setBtnCallBack(std::function<void(cocos2d::Ref * pSender)> func);

	//������ʾ������
	void updateData(int id = none);

private:
	void loadUI();

	//��ʼ��_btnArray Ϊnullptr
	void initBtnArrayToNullptr();

	//���°�ť��װ��ͼ����
	void updateEquipmentBtnTexture();

	//��ȡstar��Ӧ����ɫ
	cocos2d::Color4B getColorByStar(int star);

	//װ����ť�ص��������ť����һ���ص�
	void BtnCallBack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

private:
	const std::string csbName = "layers/heroLayer/pageViewItemLayer.csb";
	const std::string titleLabelName = "titleLabel";
	const std::string heroImgName = "heroImg";
	const std::string hpLabelName = "hpLabel";
	const std::string apLabelName = "apLabel";
	const std::string apIcoName = "apIco";

private:
	cocos2d::ui::Text *_title, *_apLabel, *_hpLabel;
	cocos2d::ui::ImageView *_heroImg, *_apIco;
	HeroCard*				_heroCard;

	cocos2d::ui::Button* _btnArray[max_equipment_num];

	//��¼��ǰҪ��ʾ��Ӣ��id
	int _heroId;

	//����item��ť�ĵ���¼��ص�
	std::function<void(cocos2d::Ref * pSender)> _func;
};
  
#endif // PAGEVIEWITEM_H_ 
