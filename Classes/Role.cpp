/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	Role.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/11/28
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "Role.h"
#include "Tools.h"
#include "TypeStruct.h"
#include "McLog.h"
#include "AudioManager.h"

USING_NS_CC;
using namespace ui;
using std::string;

Role::Role()
	:_attickNum(1),
	_isAlive(false),
	_audioIndex(none),
	_isNeedPlayEffect(false)
{
	
}

Role::~Role()
{
	AudioManager::getInstance()->unLoadBattleSceneAudio();
}

bool Role::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	
	return true;
}

void Role::initRole(const HeroCardProperty * hero, int pos)
{
	if (!Tools::betweenAnd(pos, 0, 5))
	{
		McLog mc;
		mc.addError("'pos' out of range...", __FILE__, __LINE__);
		return;
	}

	_roleType = RT_HERO;
	_pos = pos;

	_hp = hero->hp;
	_currentHp = _hp;
	_isMagic = hero->isMagic;
	_ap = hero->ap;
	_mp = hero->mp;
	_define = hero->defend;
	_mDefine = hero->magicDefend;
	_block = hero->blockRate;
	_crit = hero->critRate;
	_critDmg = hero->critDamage;
	_speed = hero->speed;
	_skillId = hero->skillId;
	_norAtId = hero->attackId;
	_isAlive = true;

	//������ɫ�����Ѫ��
	initWithFile(*(hero->textureName));
	this->setScale(sprite_scale);
	createHpBar();
}

void Role::initRole(const EnemyProperty * enemy, int pos)
{
	if (!Tools::betweenAnd(pos, 0, 5))
	{
		McLog mc;
		mc.addError("'pos' out of range...", __FILE__, __LINE__);
		return;
	}

	_roleType = RT_ENEMY;
	_pos = pos;

	_hp = enemy->hp;
	_currentHp = _hp;
	_isMagic = enemy->isMagic;
	_ap = enemy->ap;
	_mp = enemy->mp;
	_define = enemy->defend;
	_mDefine = enemy->mDefend;
	_block = enemy->block;
	_crit = enemy->crit;
	_critDmg = Tools::intToPercent(enemy->critDmg);
	_speed = enemy->speed;
	_skillId = enemy->skillId;
	_norAtId = enemy->attackId;
	_isAlive = true;

	//������ɫ�����Ѫ��
	initWithFile(StringUtils::format("%d.png", enemy->type));
	this->setScale(sprite_scale);
	createHpBar();
}

ActionInterval* Role::createBulletAnimation(Point pos)
{
	int attackId = getAttackId();
	ActionInterval* action = nullptr;

	if (0 < attackId && attackId < 5)
	{
		//��һ�ֹ�������
		//���㶯������Ҫ��ʱ��
		float distance = getPosition().distance(pos);
		
		//��֤������ʱ�䲻��̫��Ҳ����̫���ڡ�0.5f�� 0.8��֮��
		float animationTime = Tools::maxFloat(0.35f, Tools::minFloat(0.8f, distance / bullet_speed));

		action = MoveTo::create(animationTime, pos);

		//��Ч�������Ǵ�0��ʼ��attackId�Ǵ�1��ʼ������Ҫ��һ
		_audioIndex = attackId - 1;
	}
	else if (attackId <= 100)
	{
		action = createAnimationWithName("140", animation_time);
		_audioIndex = 8;
	}
	else if (100 < attackId && attackId <= 200)
	{
		action = createAnimationWithName("160", animation_time);
		_audioIndex = 4;
	}
	else if (200 < attackId && attackId <= 300)
	{
		action = createAnimationWithName("150", animation_time);
		_audioIndex = 5;
	}
	else if (300 < attackId && attackId <= 400)
	{
		action = createAnimationWithName("110", animation_time);
		_audioIndex = 6;
	}
	else if (400 < attackId && attackId <= 500)
	{
		action = createAnimationWithName("170", animation_time);
		_audioIndex = 7;
	}

	return action;
}

cocos2d::Sprite * Role::createBllet(Point pos)
{
	Sprite* bullet = nullptr;
	int attackId = getAttackId();

	if (0 < attackId && attackId < 5)
	{
		//�����ӵ���ͼ
		float angleRotate = calDirection(pos);
		bullet = Sprite::create(StringUtils::format("effect%d.png", attackId));
		bullet->setPosition(this->getPosition());
		bullet->setRotation(angleRotate);
	}else if (attackId <= 100)
	{
		bullet = Sprite::createWithSpriteFrameName("1400.png");
		bullet->setPosition(pos);
	}
	else if (100 < attackId && attackId <= 200)
	{
		bullet = Sprite::createWithSpriteFrameName("1600.png");
		bullet->setPosition(pos);
	}
	else if (200 < attackId && attackId <= 300)
	{
		bullet = Sprite::createWithSpriteFrameName("1500.png");
		bullet->setPosition(pos);
	}
	else if (300 < attackId && attackId <= 400)
	{
		bullet = Sprite::createWithSpriteFrameName("1100.png");
		bullet->setPosition(pos);
	}
	else if (400 < attackId && attackId <= 500)
	{
		bullet = Sprite::createWithSpriteFrameName("1700.png");
		bullet->setPosition(pos);
	}

	//��ӵ�������,
	Director::getInstance()->getRunningScene()->addChild(bullet, 100);

	return bullet;
}

cocos2d::ActionInterval * Role::createAnimationWithName(const std::string & name, float delay)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = NULL;
	int index = 0;

	do
	{
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name.c_str(), index++));

		//���ϵĻ�ȡSpriteFrame����ֱ����ȡ��ֵΪ����ֹͣ
		if (frame == NULL)
		{
			break;
		}

		frameVec.pushBack(frame);
	}while (true);

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setDelayPerUnit(delay / (index - 1));
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);
	auto action = Animate::create(animation);

	return action;
}

void Role::attack(Role * enemy)
{
	Point enemyPos = enemy->getPosition();

	auto bullet = createBllet(enemyPos);
	auto bulletAction = createBulletAnimation(enemyPos);

	//��Ѫ����
	auto displayText = CallFunc::create([&, enemy]() {
		if(_isNeedPlayEffect)
		{
			_isNeedPlayEffect = false;

			//���Ź�����Ч
			AudioManager::getInstance()->playAttackEffect(_audioIndex);
		}
		
		int realDmg = getRealDmg(getDamage(), _isMagic);

		enemy->flyWords(realDmg);
		enemy->hurt(realDmg);
	});

	//�Ƴ��ӵ�����
	auto removeBullet = CallFunc::create([bullet]() {
		bullet->removeFromParentAndCleanup(true);
	});

	auto action = Sequence::create(bulletAction, displayText, removeBullet, NULL);
	
	//��ɫ����ǰҡ
	attackAnimation();

	bullet->runAction(action);
}

void Role::attackAnimation()
{
	auto rotate1 = RotateTo::create(attack_animation_time, 30);

	EaseBounceInOut* bounce1 = EaseBounceInOut::create(rotate1);
	auto *scal = ScaleTo::create(attack_animation_time, 0.5f);

	RotateTo* rotate2 = RotateTo::create(attack_animation_time, 0);
	ScaleTo *scal2 = ScaleTo::create(attack_animation_time, sprite_scale);

	EaseBounceInOut* bounce2 = EaseBounceInOut::create(rotate2);

	Sequence* rotateSequence = Sequence::create(bounce1, scal, bounce2, scal2, NULL);
	this->runAction(rotateSequence);
}

void Role::createHpBar()
{
	auto hpBarBg = Sprite::createWithSpriteFrameName(hp_bar_bg_name);
	hpBarBg->setPosition(this->getContentSize().width / 2, hp_bar_height_pos);
	hpBarBg->setScaleX(hp_bar_scale);
	addChild(hpBarBg);

	m_hpBar = LoadingBar::create(hp_bar_name, Widget::TextureResType::PLIST, 100.0f);
	m_hpBar->setPosition(Point(this->getContentSize().width / 2, hp_bar_height_pos));
	m_hpBar->setScaleX(hp_bar_scale);
	addChild(m_hpBar, 10);
}

int Role::getAttackId()
{
	int  attickId = _norAtId;
	
	//ÿ��ͨ����2�κ����ʹ���ؼ�����
	if (_attickNum % using_skill == 0)
	{
		attickId = _skillId;
	}

	return attickId;
}

int Role::getRealDmg(int dmg, bool isMagic)
{
	int realDmg = 0;

	if (_isAlive)
	{
		if (isMagic)
		{
			//ħ���˺�
			realDmg = dmg - _mDefine;
		}
		else
		{
			//�����˺�
			realDmg = dmg - _define;
		}

		if (realDmg < 0)
		{
			//�޷��Ʒ���ǿ�ƿ�Ѫ�����1~20��
			realDmg = Tools::getRandomInt(1, 20);
		}
	}

	return realDmg;
}

void Role::flyWords(int damg, float scale)
{
	auto label = LabelAtlas::create("0123456789", "fonts/fonts.png", 42, 60, '0');
	auto visibleSize = getContentSize();
	
	label->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE);
	label->setString(StringUtils::format("%d", damg));
	label->setScale(scale);
	addChild(label, 100);

	ActionInterval* fade = FadeOut::create(1.2f);

	auto callFun = CallFunc::create([label]() {
		label->removeFromParentAndCleanup(true);
	});

	Sequence* seq = Sequence::createWithTwoActions(fade, callFun);
	label->runAction(seq);
}

//���������ĽǶ�
float Role::calDirection(Point pos)
{
	float accDir = 0;
	float vecX = pos.x - getPositionX();
	float vecY = pos.y - getPositionY();

	if (abs(vecX) < 0.00001f)
	{
		if (vecY > 0)
			accDir = 0;
		else if (vecY < 0)
			accDir = PI;
	}
	else
	{
		accDir = atan(vecY / vecX);

		if (vecX >= 0)
			accDir = PI * 0.5 - accDir;
		else
			accDir = PI * 1.5 - accDir;
	}

	return (float)(accDir * 180.0f / PI);
}

int Role::getDamage()
{
	int dmg = 0;
	int initDmg = 0;
	int attackId = getAttackId();

	if (!_isAlive)
	{
		return 0;
	}
	
	if (_isMagic)
	{
		initDmg = _mp;
	}
	else
	{
		initDmg = _ap;
	}

	if (attackId <= 10)  //��ͨ����������˺� 90%~100%
	{
		dmg = initDmg * Tools::getRandomInt(90, 100) / 100.0f;
	}
	if (10 < attackId && attackId <= 100)  //���ܵ��幥��������˺� 200%~280%
	{
		dmg = initDmg * Tools::getRandomInt(200, 280) / 100.0f;
	}
	if (100 < attackId && attackId <= 200)  //����ȫ�幥��������˺� 70%~90%
	{
		dmg = initDmg * Tools::getRandomInt(70, 90) / 100.0f;
	}
	if (200 < attackId && attackId <= 300)  //���ܺ��Ź��������ȹ���ǰ�ţ�������˺� 120%~150%
	{
		dmg = initDmg * Tools::getRandomInt(120, 150) / 100.0f;
	}
	if (300 < attackId && attackId <= 400)  //���ܺ��Ź��������ȹ������ţ�������˺� 120%~150%
	{
		dmg = initDmg * Tools::getRandomInt(120, 150) / 100.0f;
	}
	if (400 < attackId && attackId <= 500)  //�������Ź���������˺� 150%~180%
	{
		dmg = initDmg * Tools::getRandomInt(150, 180) / 100.0f;
	}

	//�Ƿ���ɱ�������
	if (Tools::getRandomInt(1, 100) < _crit)
	{
		dmg *= _critDmg;
	}

	return dmg;
}

void Role::attack(cocos2d::Vector<Role*>* attackList)
{
	_isNeedPlayEffect = true;

	for (int index = 0; index < attackList->size(); ++index)
	{
		auto enemy = attackList->at(index);
		this->attack(enemy);
	}

	//���Ź�����Ч
	//AudioManager::getInstance()->playAttackEffect(_audioIndex);

	//���غϹ������,�����غ�����һ
	++_attickNum;
}

void Role::hurt(int dmg)
{
	if (_isAlive)
	{
		_currentHp -= Tools::maxInt(0, dmg);
		
		//����Ѫ��
		updateHpBar();
		
		if (_currentHp <= 0)
		{
			//��ɫ�Ѿ�����
			_isAlive = false;
			_currentHp = 0;

			auto fadeout = FadeOut::create(0.5f);
			auto remove = CallFunc::create([&]() {
				this->removeFromParentAndCleanup(true);
			});

			runAction(Sequence::create(fadeout, remove, NULL));
		}
	}
}

void Role::updateHpBar()
{
	m_hpBar->setPercent((_currentHp * 1.0f / _hp) * 100);
}