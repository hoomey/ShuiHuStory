/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	PictureLayer.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/20
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef PICTURELAYER_H_  
#define PICTURELAYER_H_  
  
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ConstantDefine.h"
#include <functional>

class PictureLayer : public cocos2d::Layer
{
public:
	PictureLayer();
	~PictureLayer();
	virtual bool init() override;
	CREATE_FUNC(PictureLayer);

private:
	void loadUI();

	void addTouchLayer();

	//��ʼһ����ʼֵΪstar������Ϊlength��typeList����
	void initTypeList(int min, int list[], int length = max_battle_hero_num);

	void loadItem();

	void onEnter() override;

	void update(float dt);

private:
	const std::string csbName = "layers/pictureLayer/pictureLayer.csb";
	const std::string btnTianName = "btnTian";
	const std::string btnDiName = "btnDi";
	const std::string pageViewName = "pageView";
	const std::string tipsName = "tips";

	const int pageCount = 19;

	const int tianEndPage = 6;

private:
	//��¼��һ�ε�index
	int _preIndex;

	cocos2d::ui::Button *_btnTian, *_btnDi;
	cocos2d::ui::PageView* _pageView;
	cocos2d::ui::Text* _tips;

private:
	//�ڲ��࣬������������Ϣ
	class TouchLayer : public cocos2d::Layer
	{
	public:
		virtual bool init();
		CREATE_FUNC(TouchLayer);

		void setOnTouchBegan(std::function<void(int selectIndex)> began);
		void setOnTouchMoved(std::function<void(int selectIndex)> moved);
		void setOnTouchEnded(std::function<void(int selectIndex, float moveDistance)> ended);

	private:
		const cocos2d::Point HeroPosition[max_battle_hero_num] = { cocos2d::Point(50, 530), cocos2d::Point(250, 530), cocos2d::Point(450, 530),
			cocos2d::Point(50, 290), cocos2d::Point(250, 290), cocos2d::Point(450, 290) };

	private:
		//�ж��Ƿ�ѡ��Ӣ��ͷ��
		int isTouchedItem(cocos2d::Point pos);

		bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
		void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
		void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	
	private:
		//��¼��ǰѡ�е�index
		int _selectIndex;

		//�����ص�
		std::function<void(int selectIndex)> _onTouchBegan;
		std::function<void(int selectIndex)> _onTouchMoved;
		std::function<void(int selectIndex, float moveDistance)> _onTouchEnded;
	};
};

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*   pageview��item                                                     */
/************************************************************************/

class PictureItem : public cocos2d::ui::Layout
{
public:
	PictureItem();
	~PictureItem();
	virtual bool init() override;
	CREATE_FUNC(PictureItem);

	//����typeList��ʼ��item
	void initWithTypeList(int* typeList);

	//�����Ƿ�ѡ��item��ѡ��item�����С
	void setSelect(bool isTrue, int pos);

private:
	void loadUI();

	//����ָ��λ�õ�ͷ��,���type == none ������ͼƬ����
	void setHeadSprite(int pos, int type = none);

	//����ָ��λ�õ����ֱ�ǩ����
	void setName(int pos, const std::string& name);

	//�����������ֵֵȫ���ÿ�
	void initArrayToNullptr();

private:
	const std::string csbName = "layers/pictureLayer/pictureItemLayer.csb";
	const std::string headName = "head%d.png";
	const int startSpTag = 0;
	const int startNameTag = 10;
	const int endSpTag = 6;
	const int endNameTag = 16;

private:
	cocos2d::ui::Text* _nameLael[max_battle_hero_num];
	cocos2d::Sprite* _headSp[max_battle_hero_num];
};


#endif // PICTURELAYER_H_ 
