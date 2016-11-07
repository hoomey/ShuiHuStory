/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	EquipmentDisplayLayer.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __EQUIPMENTDISPLAYLAYER_H__
#define __EQUIPMENTDISPLAYLAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>

//ǰ������
class ListItem;
struct EquipmentProperty;

class EquipmentDisplayLayer : public cocos2d::Layer{
public:
	EquipmentDisplayLayer();
	~EquipmentDisplayLayer();
	CREATE_FUNC(EquipmentDisplayLayer);
	virtual bool init() override;


private:
	void loadUI();
	
	//�����б���ʾ�ĵ�ǰ�����������ܵ���������:30/50
	void setTipLabel();

	//����Item������
	void setItemAttribute(const EquipmentProperty* property, ListItem* item);

	//����ָ��id��item������
	void updateItemAttribute(const int equipmentId, const int itenId);

	//��ʼ��5��Item
	void loadItem(int n = 5);

	void setItemColor(ListItem* item, int star);

	virtual void onEnterTransitionDidFinish() override;

	//��ť�ص�����
	void btnCloseCallBack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	//��������
	void startAnimation();

	//������������������Դ
	void endAnimation();

private:
	const std::string csbName = "layers/homeLayer/equipmentDisplayLayer.csb";
	const std::string listViewName = "listView";
	const std::string tipLabelName = "tip";
	const std::string btnCloseName = "btnClose";
	const std::string blockName = "blockName";
	const int defaultLoadNum = 5;

private:
	//��¼��һ�����鰴ť���������
	int _preClicked;

	cocos2d::ui::ListView*	_listView;
	cocos2d::ui::Button*	_btnClose;
	cocos2d::ui::Text*		_tipLabel;
	cocos2d::Vector<ListItem*> _itemVector;
};

#endif // EQUIPMENTDISPLAYLAYER_H_
