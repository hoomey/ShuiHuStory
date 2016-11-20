/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	DisplayEquipmentByType.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/19
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef DISPLAYEQUIPMENTBYTYPE_H_  
#define DISPLAYEQUIPMENTBYTYPE_H_  
  
#include "cocos2d.h"
#include "ui/CocosGUI.h"

//ǰ������
class DisplayListItem;
class Equipment;
struct EquipmentProperty;

//װ��������
enum ET
{
	ET_HAT = 1,
	ET_CLOTH,
	ET_WEAPON,
	ET_JADE,
	ET_SHOES,
	ET_HORSE
};

class DisplayEquipmentByType : public cocos2d::Layer
{
public:
	DisplayEquipmentByType();
	~DisplayEquipmentByType();
	virtual bool init() override;
	CREATE_FUNC(DisplayEquipmentByType);

	void setDisPlayEquipmentType(ET et, int heroid);

	//����item����İ�ť����¼��ص�
	void setBtnCallBack(std::function<void(cocos2d::Ref * pSender, int equipmentPos, int equipmentId, bool isAdd)> func);

private:
	void loadUI();

	void loadItem();

	void setItemColor(DisplayListItem* item, int star);

	//��֪��ԭ����ʲôonEnterTransitionDidFinish�����ﲻ�ᱻ������˸�ΪonEnter
	void onEnter() override;
	
	void setItemAttribute(const EquipmentProperty* property, DisplayListItem* item);

	//��ť�ص�����
	void btnCloseCallBack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	//��������
	void startAnimation();

	//������������������Դ
	void endAnimation();

private:
	const std::string csbName = "layers/homeLayer/displayLayer.csb";
	const std::string listViewName = "listView";
	const std::string tipLabelName = "tip";
	const std::string btnCloseName = "btnClose";
private:
	//��¼�����ť���������
	int _clickedIndex;
	//Ҫװ��װ����Ӣ��id
	int _heroId;

	//ʾ������
	ET _et;

	cocos2d::ui::ListView*	_listView;
	cocos2d::ui::Button*	_btnClose;
	cocos2d::ui::Text*		_tipLabel;

	//����item��ť�ĵ���¼��ص�
	std::function<void(cocos2d::Ref * pSender, int equipmentPos, int equipmentId, bool isAdd)> _func;

	//������listView��Ӧ�����磺_equipmendIdVector[0], �������_listview�е�һ��item��Ӧ��װ��ΨһId
	std::vector<int> _objectIdVector;
};
  
#endif // DISPLAYEQUIPMENTBYTYPE_H_ 
