/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	DetialsLayer.h
// Author:		 Metoor
// Version: 	1.0
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __DETIALSLAYER_H__
#define __DETIALSLAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <functional>

//ǰ������
struct EquipmentProperty;
struct HeroCardProperty;
class I18N;
class GameData;

enum DisplayType
{
	DT_EQUIPMENT,
	DT_HERO
};

enum BtnType{
	BT_LEVEL_UP,
	BT_INTENSIFY
};
 
//��ʾװ����Ӣ�۵���ϸ��Ϣ
class DetialsLayer : public cocos2d::Layer
{
public:
	DetialsLayer();
	~DetialsLayer();
	virtual bool init() override;
	CREATE_FUNC(DetialsLayer);

	//ͨ��װid��ʼ��Ui����
	void initUiWithId(int id, DisplayType type);

private:
	void loadUI();

	//������Ʒ��Ҫ�Ļ��ѣ����� BT_LEVEL_UP������ʯ����ʯ BT_INTENSIFY��
	int calculateCost(BtnType type);

	//����������Ҫ�Ľ��
	int calculateGold();

	//����ǿ����Ҫ����ʯ
	int calculateDiamond();

	//��ѯ�Ƿ��ж����ͬ���͵���Ʒ
	int findSameTypeObject();

	//����װ��
	void levelupEquiupment();

	//����Ӣ��
	void levelupHero();

	//ǿ��װ��
	void intensifyEquipment();

	//ǿ��Ӣ��
	void intensifyHero();

	//������Ʒ�����Դ��������ַ�
	std::string propertyToString(const EquipmentProperty* property);
	std::string propertyToString(const HeroCardProperty* property);

	//������ʾ������
	void updateAttribute();

	//����Ҫ��ʾ��Ӣ�ۻ�װ��������
	void setName(const std::string name);

	//�����Ǽ��������ֵ���ɫ
	void setNameColor(int star);

	//����Ҫ��ʾ�������ַ�������
	void setAttributeString(const std::string& content);

	//����Ӣ�ۻ�װ��ͼƬ
	void setIco(const std::string& icoName);
	
	//ǿ���������Ļص�
	void intensify();
	void levelup();

	//��������
	void startAnimation();

	//������������������Դ
	void endAnimation();

	void onEnterTransitionDidFinish() override;

	//���۴�����
	void sell();

	//����װ��
	void sellOEquipment();

	//����Ӣ�ۿ���
	void sellOHero();
	
	//����
	void abandon();

	//����װ��
	void abandonEquipment();
	
	//����װ��
	void abandonHero();

	//��ť�ص�����
	void btnCloseCallBack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

private:
	const std::string csbName = "layers/homeLayer/detialsLayer.csb";
	const std::string icoName = "ico";
	const std::string nameLabelName = "nameLabel";
	const std::string attributeLabelName = "attributeLabel";
	const std::string btnIntensifyName = "btnIntensify";
	const std::string btnLevelupName = "btnLevelup";
	const std::string btnCloseName = "btnClose";
	const std::string btnSellName = "btnSell";
	const std::string btnAbandonName = "btnAbandon";

private:
	//��·��ʾ����ƷId
	int _objectId;

	//��¼��ʾ����Ʒ����
	DisplayType _type;

	GameData* _data;
	I18N* _i18n;
	

	cocos2d::ui::ImageView* _ico;
	cocos2d::ui::Text* _nameLabel;
	cocos2d::ui::Text* _attributeLabel;
	cocos2d::ui::Button* _btnIntensify;
	cocos2d::ui::Button* _btnLevelup;
	cocos2d::ui::Button* _btnClose;
	cocos2d::ui::Button* _btnSell;
	cocos2d::ui::Button* _btnAbandon;

	std::function<void(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)> _intensifyFun, _levelupFunc;
};

#endif // DETIALSLAYER_H_

