/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	PVPRole.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/12/04
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef PVPROLE_H_  
#define PVPROLE_H_  

#include "cocos2d.h"
#include "ConstantDefine.h"
#include "ui/CocosGUI.h"

//ǰ������
struct HeroCardProperty;
struct EnemyProperty;
struct PVPEnemy;

enum RoleType{
	RT_HERO,
	RT_ENEMY
};

struct PVPEnemy
{
	bool isExist;
	int totalhp;
	int attackid;
	int skillsid;
	int totaldefend;
	int totalap;
	std::string textureName;
};

class PVPRole : public cocos2d::Sprite
{
public:
	PVPRole();
	~PVPRole();
	virtual bool init();
	CREATE_FUNC(PVPRole);

	void initRole(const HeroCardProperty* hero, int pos);

	void initRole(const PVPEnemy * enemy, int pos);

	void attack(PVPRole attackList[], int attackId, int dmgList[]);

private:
	//��Ѫ
	void hurt(int dmg);

	//������������
	void attack(int attackId, int dmg, PVPRole* enemy);

	//�����ӵ���ת�ĽǶ�
	float calDirection(cocos2d::Point pos);

	//��ɫ����Ĺ�������
	void attackAnimation();

	cocos2d::Sprite* createBllet(int attackId, cocos2d::Point pos);

	//�����ӵ��˶��Ķ���
	cocos2d::ActionInterval* createBulletAnimation(int attackId, cocos2d::Point pos);

	cocos2d::ActionInterval* createAnimationWithName(const std::string &name, float delay);

	void flyWords(int damg, float scale = 2.0f);

	void createHpBar();

	void updateHpBar();

	//�����ʵ���˺� �з����� - �ҷ�����
	int getRealDmg(int dmg);

private:
	const float PI = 3.1415926f;
	const int sprite_height = 150;
	const int sprite_width = 200;
	const int hp_bar_height_pos = 30;

	//ʹ�ü�����Ҫ�����ͨ�����Ĵ���
	const int using_skill = 2;

	const float hp_bar_scale = 1.2f;
	const float sprite_scale = 0.6f;

	const float attack_animation_time = 0.15f;
	const float animation_time = 0.5f;
	const float bullet_speed = 900.0f;

	const std::string hp_bar_bg_name = "icos/hpBarBg.png";
	const std::string hp_bar_name = "icos/hpBar.png";

private:
	//get��set����
	CC_SYNTHESIZE(int, _currentHp, CurrentHp);
	CC_SYNTHESIZE(bool, _isAlive, IsAlive);
	CC_SYNTHESIZE(RoleType, _roleType, RoleType);
	CC_SYNTHESIZE(int, _pos, Pos)

	CC_SYNTHESIZE(int, _define, Define);
	CC_SYNTHESIZE(int, _hp, Hp);

	//�Ƿ���Ҫ���Ź�����Ч�������ڹ������Ŀ������Ч���ظ�����
	bool _isNeedPlayEffect;

	//��Ч������
	int _audioIndex;

	//Ѫ��
	cocos2d::ui::LoadingBar* m_hpBar;
};

#endif // PVPROLE_H_ 
