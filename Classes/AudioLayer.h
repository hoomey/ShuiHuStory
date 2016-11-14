/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	AudioLayer.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/13
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef AUDIOLAYER_H_  
#define AUDIOLAYER_H_  
  
#include "cocos2d.h"
#include "ui/CocosGUI.h"


class AudioLayer : public cocos2d::Layer
{
public:
	AudioLayer();
	~AudioLayer();
	virtual bool init() override;
	CREATE_FUNC(AudioLayer);

private:
	void loadUI();

	//���ø��ݱ�����������ð�ťͼ���ʼ״̬
	void initBtnIco();

	//���ְ�ť����߼����������ǰ���ֿ��ã���������á� �����ã����������
	void music();
	
	//��Ч��ť������������ǰ���ֿ��ã���������á������ã����������
	void effect();

	void startAnimation();
	void endAnimation();
	void onEnterTransitionDidFinish() override;

private:
	const std::string csbName = "layers/homeLayer/audioLayer.csb";
	const std::string btnCloseName = "btnClose";
	const std::string btnMusicName = "btnMusic";
	const std::string btnEffectName = "btnEffect";

private:
	cocos2d::ui::Button *_btnClose, *_btnMusic, *_btnEffect;
};
  
#endif // AUDIOLAYER_H_ 
