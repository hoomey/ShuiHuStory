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
	void loadUI();

	void setContent(std::string name, std::string text, std::string imgName);
	
	//��ȡjson�еľ���Ի�
	void readChatData();

	//��ȡ��һ���԰�
	void nextMsg();

private:
	//ui�ļ��ĳ�����
	const std::string csbName = "layers/firstLogin/firstScene.csb";
	const unsigned heroNameTextTag = 33;
	const unsigned heroImageTag = 34;
	const unsigned chatContentTextTag = 35;
	const std::string storyFileName = "data/story.json";

private:
	unsigned _currentIndex;
	rapidjson::Document  _doc;
	cocos2d::ui::Text* _heroName;
	cocos2d::ui::Text* _chatContent;
	cocos2d::ui::ImageView* _heroImage;
};

#endif // FIRSTSCENE_H_