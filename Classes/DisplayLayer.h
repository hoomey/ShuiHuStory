/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	DisplayLayer.h
// Author:		 Metoor
// Version: 	1.0
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __DISPLAYLAYER_H__
#define __DISPLAYLAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>
#include <functional>
#include <unordered_map>

enum ObjectType
{
	OT_NONE,
	OT_EQUIPMENT,
	OT_HERO,
};

//ǰ������
class DisplayListItem;
class Equipment;
class HeroCard;
struct EquipmentProperty;
struct HeroCardProperty;


class DisplayLayer : public cocos2d::Layer {
public:
	DisplayLayer();
	~DisplayLayer();
	CREATE_FUNC(DisplayLayer);
	virtual bool init() override;

	int getObjectIdByIndex(int index);

	std::vector<int>* getObjectIdVector();

	DisplayListItem* getObjectItemByIndex(int index);

	//����Ҫ��ʾ�����ͣ���ʾװ����Ӣ�ۿ���
	void setDisplayType(ObjectType type);

	//����item����İ�ť����¼��ص�
	void setBtnCallBack(std::function<void(cocos2d::Ref * pSender)> func);

	//����item���水ť��ͼƬ
	void setBtnTexture(const std::string& normal, const std::string& pressed);

	//������������������Դ
	void endAnimation();

private:
	void loadUI();

	void load();

	//ͨ��map������item
	void loadItem(const std::unordered_map<int, Equipment*>* equipmentMap);
	void loadItem(const std::unordered_map<int, HeroCard*>* heroMap);

	//�����б���ʾ�ĵ�ǰ�����������ܵ���������:30/50
	void setTipLabel();

	//ע������б�ĳһ�������
	void addUpdateDisplayItemEventListener();

	//ɾ��item
	void deleteItem();

	//����Item������
	void setItemAttribute(const HeroCardProperty* property, DisplayListItem* item);

	//����Item������
	void setItemAttribute(const EquipmentProperty* property, DisplayListItem* item);

	//����ָ����Ʒ(װ����Ӣ��)id��item������
	void updateItemAttribute();

	void setItemColor(DisplayListItem* item, int star);

	virtual void onEnter() override;

	//��ť�ص�����
	void btnCloseCallBack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	//��������
	void startAnimation();

private:
	const std::string csbName = "layers/homeLayer/displayLayer.csb";
	const std::string listViewName = "listView";
	const std::string tipLabelName = "tip";
	const std::string btnCloseName = "btnClose";

private:
	//�Ƿ���Ҫ�����û�����
	bool _isNeedUpadateUserData;

	//��¼�����ť���������
	int _clickedIndex;

	//����Ҫ��ʾ����Ʒ����
	ObjectType _type;

	//����item����İ�ť����ͼƬ
	std::string _normalTexture;
	std::string _pressedTexture;

	cocos2d::ui::ListView*	_listView;
	cocos2d::ui::Button*	_btnClose;
	cocos2d::ui::Text*		_tipLabel;

	//������listView��Ӧ�����磺_equipmendIdVector[0], �������_listview�е�һ��item��Ӧ��װ��ΨһId
	std::vector<int> _objectIdVector;

	//����item��ť�ĵ���¼��ص�
	std::function<void(cocos2d::Ref * pSender)> _func;
};

#endif // DISPLAYLAYER_H_
