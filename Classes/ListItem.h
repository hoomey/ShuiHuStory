#ifndef __LISTITEM_H__
#define __LISTITEM_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <functional>

enum ItemLabelType{
	LEVEL,
	NAME,
	TEXT1,
	TEXT2
};


class ListItem : public cocos2d::ui::Layout{
public:
	ListItem();
	~ListItem();
	CREATE_FUNC(ListItem);
	virtual bool init() override;

	//���ð�ť�ص�
	void setBtnCallBack(std::function<void(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)> func);

	//���ö�Ӧ���͵ı�ǩ����
	void setLabelText(ItemLabelType type, const std::string content);
	
	//���ö�Ӧ���͵ı�ǩ��ɫ
	void setLabelColor(ItemLabelType type, cocos2d::Color4B color);
	
	//����Item��ͼ��
	void setIco(const std::string icoName, const std::string img1Name, const std::string img2Name);
	
	//����Ʒ���Ǽ�
	void setStarNum(const int n);

private:
	const std::string csbName = "layers/homeLayer/listItem.csb";
	const std::string icoName = "ico";
	const std::string levelLabelName = "levelLabel";
	const std::string nameLabelName = "nameLabel";
	const std::string starName = "star";
	const std::string img1Name = "img1";
	const std::string img2Name = "img2";
	const std::string text1Name = "text1";
	const std::string text2Name = "text2";
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
	cocos2d::ui::Text*		_text1;		//���Ա�ǩ
	cocos2d::ui::Text*		_text2;		//���Ա�ǩ
	cocos2d::ui::Button*	_btn;		//��ť
};

#endif // LISTITEM_H_