/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	StoreLayer.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/24
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef STORELAYER_H_  
#define STORELAYER_H_  
  
#include "cocos2d.h"
#include "ui/CocosGUI.h"

//ǰ������
class DisplayListItem;
class HeroCard;
class Equipment;
struct EquipmentProperty;
struct HeroCardProperty;
struct SaveEquipmentData;
struct SaveHeroCardData;


class StoreLayer : public cocos2d::Layer
{
public:
	StoreLayer();
	~StoreLayer();
	virtual bool init() override;
	CREATE_FUNC(StoreLayer);

private:
	void loadUI();

	int getRandomHeroType();
	int getRandomEquipment();

	//����װ����Ӣ������
	void saveEquipment();
	void saveHeroCard();

	//��ñ����װ����Ӣ������
	void getSaveEquipment(SaveEquipmentData& sd);
	void getSaveHeroCard(SaveHeroCardData& sd);

	//������̬��item��װ����Ӣ�ۣ�������������������߸�������һ�������ʾ����Ҫ�������ݣ����ر��������
	void createRandomItem(int heroType = -1, int equipmentType = -1);

	//����Item������
	void setItemAttribute(const HeroCardProperty* property, DisplayListItem* item);

	//����Item������
	void setItemAttribute(const EquipmentProperty* property, DisplayListItem* item);

	void setItemColor(DisplayListItem* item, int star);

	//��ʾ��ҵ�ǰӵ�е���ʯ��
	void updateDiamond();

	//��ʾ��ҵ�ǰӵ�еĽ����
	void updateGold();

	//listViewĬ������item����İ�ť�ص�
	void btnOkCallBack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	void onEnter() override;

private:
	const std::string csbName = "layers/storeLayer/storeLayer.csb";
	const std::string goldLabelName = "gold";
	const std::string diamondLabelName = "diamond";
	const std::string listViewName = "listView";
	const std::string itemName = "item_%d";
	const std::string btnOkName = "btnOk";

	//�����̵���µ�ʱ��key
	const std::string preTimeKey = "pst";

	//��������Ƿ������ʱ��װ��
	const std::string isBuyHero = "ibys";
	const std::string isBuyEquipment = "ibes";

	//����װ�����ݵ�key
	const std::string eId = "eds";
	const std::string eStar = "ess";
	const std::string eType = "ets";
	const std::string eRate = "ers";

	//����Ӣ�����ݵ�key
	const std::string hId = "hds";
	const std::string hStar = "hss";
	const std::string hType = "hts";
	const std::string hRate = "hrs";

	//�̵����ĳ�������
	const int tian_d = 300; //��ļ�����Ҫ���ĵ���ʯ
	const int di_d = 120;	//��ļ��ɷ��Ҫ���ĵ���ʯ
	const int gold = 10000;	//������ʱ��õĽ����
	const int gold_d = 10;	//������ʱ���ĵ���ʯ
	const int diamond = 100;	//������ʯʱ��õ���ʯ��
	const int diamond_g = 120000;	//������ʯʱ���ĵĽ����

	const unsigned int intervalTime = 21600;	//6Сʱ
	const int numCount = 2;	//��̬�����������Ʒ����

private:
	HeroCard* _hero;
	Equipment* _equipment;

	bool _isBuyHero;
	bool _isBuyEquipment;

	cocos2d::ui::ListView* _listView;
	cocos2d::ui::Text *_goldLabel, *_diamondLabel;
};
  
#endif // STORELAYER_H_ 
