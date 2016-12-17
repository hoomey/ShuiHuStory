/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	Role.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/28
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef ROLE_H_  
#define ROLE_H_  

#include "cocos2d.h"
#include "ConstantDefine.h"
#include "ui/CocosGUI.h"

//ǰ������
struct HeroCardProperty;
struct EnemyProperty;

enum RoleType{
	RT_HERO,
	RT_ENEMY
};

class Role : public cocos2d::Sprite
{
public:
	Role();
	~Role();
	virtual bool init();
	CREATE_FUNC(Role);

	void initRole(const HeroCardProperty* hero, int pos);
	void initRole(const EnemyProperty* enemy, int pos);

	void attack(cocos2d::Vector<Role*> * attackList);

	//��ù����ķ�ʽId
	int getAttackId();

private:
	//��ý�ɫʵ�ʵĹ�����
	int getDamage();

	//��Ѫ,����ֵΪ�ܵ�����ʵ�˺�
	void hurt(int dmg);

	//������������
	void attack(Role* enemy);

	//�����ӵ���ת�ĽǶ�
	float calDirection(cocos2d::Point pos);

	//��ɫ����Ĺ�������
	void attackAnimation();

	cocos2d::Sprite* createBllet(cocos2d::Point pos);

	//�����ӵ��˶��Ķ���
	cocos2d::ActionInterval* createBulletAnimation(cocos2d::Point pos);

	cocos2d::ActionInterval* createAnimationWithName(const std::string &name, float delay);

	void flyWords(int damg, float scale = 2.0f);

	void createHpBar();

	void updateHpBar();

	//����ܵ�����ʵ�˺� �з����� - �ҷ�����(����������Ч��)
	int getRealDmg(int dmg, bool isMagic);

private:
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

	CC_SYNTHESIZE(bool, _isMagic, IsMagic);
	CC_SYNTHESIZE(int, _ap, Ap);
	CC_SYNTHESIZE(int, _mp, Mp);
	CC_SYNTHESIZE(int, _define, Define);
	CC_SYNTHESIZE(int, _mDefine, mDefine);
	CC_SYNTHESIZE(int, _block, Block);
	CC_SYNTHESIZE(int, _crit, Crit);
	CC_SYNTHESIZE(float, _critDmg, CritDmg);
	CC_SYNTHESIZE(int, _speed, Speed);
	CC_SYNTHESIZE(int, _hp, Hp);
	CC_SYNTHESIZE(int, _skillId, SkillId);	//���ܹ���Id
	CC_SYNTHESIZE(int, _norAtId, NorAtId);	//��ͨ����Id

	//��¼�ǵڼ��ι���
	int _attickNum;

	//�Ƿ���Ҫ���Ź�����Ч�������ڹ������Ŀ������Ч���ظ�����
	bool _isNeedPlayEffect;

	//��Ч������
	int _audioIndex;

	//Ѫ��
	cocos2d::ui::LoadingBar* m_hpBar;
};

#endif // ROLE_H_
