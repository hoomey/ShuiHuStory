#ifndef __FIRSTSCENE_H__
#define __FIRSTSCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"
#include "json/document.h"

class FirstScene : public cocos2d::Layer
{
public:
	FirstScene();
	~FirstScene();
	virtual bool init();
	CREATE_FUNC(FirstScene);

	static cocos2d::Scene* createScene();

private:
	void setContent(std::string name, std::string text, std::string imgName);
	
	//��ȡjson�еľ���Ի�
	void readChatData();

	//��ȡ��һ���԰�
	void nextMsg();

private:
	/*ui�ļ��ĳ�����
	������ʽ������_�������㣩����*/
	const std::string csbName_firstScene = "layer/firstLogin/firstScene.csb";
	const unsigned heroNameTextTag_firstScene = 33;
	const unsigned heroImageTag_firstScene = 34;
	const unsigned chatContentTextTag_firstScene = 35;
	const std::string storyFileName_firstScene = "data/story.json";

private:
	unsigned _currentIndex;
	rapidjson::Document  _doc;
	cocos2d::ui::Text* _heroName;
	cocos2d::ui::Text* _chatContent;
	cocos2d::ui::ImageView* _heroImage;
};

#endif // FIRSTSCENE_H_