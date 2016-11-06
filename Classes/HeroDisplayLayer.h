#ifndef __HERODISPLAYLAYER_H__
#define __HERODISPLAYLAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

//ǰ������
class ListItem;
struct HeroCardProperty;

class HeroDisplayLayer : public cocos2d::Layer{
public:
	HeroDisplayLayer();
	~HeroDisplayLayer();
	virtual bool init() override;
	CREATE_FUNC(HeroDisplayLayer);

private:
	void loadUI();

	// ��ʼ��5��Item
	void loadItem(int n = 5);

	//����Item������
	void setItemAttribute(const HeroCardProperty* property, ListItem* item);
	
	//����ָ��id��item������
	void updateItemAttribute(const int heroId, const int itenId);
	
	void setItemColor(ListItem* item, int star);

	//��ť�ص�����
	void btnCloseCallBack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	virtual void onEnterTransitionDidFinish() override;

	//��������
	void startAnimation();

	//������������������Դ
	void endAnimation();

private:
	const std::string csbName = "layers/homeLayer/heroDisplayLayer.csb";
	const std::string listViewName = "listView";
	const std::string btnCloseName = "btnClose";
	const std::string blockName = "blockName";
	const int defaultLoadNum = 5;

private:
	//��¼��һ�����鰴ť���������
	int _preClicked;

	cocos2d::ui::ListView* _listView;
	cocos2d::ui::Button*	_btnClose;
	cocos2d::Vector<ListItem*> _itemVector;
};

#endif // HERODISPLAYLAYER_H_
