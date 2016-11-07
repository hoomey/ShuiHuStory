/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	ParticleLayer.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/
 
#ifndef __PARTICLELAYER_H__
#define __PARTICLELAYER_H__

#include "cocos2d.h"

class ParticleLayer : public cocos2d::Layer {
public:
	ParticleLayer();
	~ParticleLayer();

	bool init() override;
	CREATE_FUNC(ParticleLayer);

	//���������Ըı�ɱ�����Ч
	void changeToBgParticle();

	//���������Ըı�ɵ�����ƶ��켣��Ч
	void changeToClickParticle();

private:
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
	virtual void onToucheMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	cocos2d::ParticleSystemQuad* _particle;
};

#endif // PARTICLELAYER_H_