/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	ConstantDefine.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/10/20
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __CONSTANTDEFINE_H_
#define __CONSTANTDEFINE_H_

#include "string"

using std::string;


//------------������Ӳ��ǵ�zorder����-----------------------------------------------

//��ϷLayer��Zorder����������Ϸ��ʾ���Ⱥ�˳��ֵԽ������ʾ��Խ�ϲ�
const int max_z_order = 9999;
const int particle_z_order = 9990;
const int dialog_z_order = 9980;
const int menu_z_order = 9970;
const int tip_z_order = 9960;


//-----------------------------------------------------

const std::string save_hero_file_name = "myHeroCard.json";			//����������һ��Ӣ�ۿ������ݵ��ļ�����
const std::string save_equipment_file_name = "myEquipment.json";	//����������һ��װ�����ݵ��ļ�����
const std::string equipment_file_name = "datas/equipment.data";		//��������װ���Ļ������ݵ��ļ�����
const std::string hero_file_name = "datas/hero.data";				//��������Ӣ�ۿ��ƻ������ݵ��ļ�����

const int equipment_map_max_size = 50;		//���ӵ�е����װ����
const int hero_card_map_max_size = 50;		//���ӵ��Ӣ�ۿ����������

const int max_gold = 1000000;				//�����ͬʱӵ�е��������
const int max_diamond = 10000;				//�����ͬʱӵ�е����ר����

const int max_level = 100;					//������ȼ�
const int start_exp = 300;					//����ʼ��õľ���ֵ
const float start_exp_rate = 1.1f;			//���㵱ǰ�ȼ��������辭��ʱ�ı���

const int none = -1;						//��ʾû�л���Ӣ��װ��λ��û��װ�����߱�ʾװ��û��ʹ����
const int max_equipment_num = 6;			//��ɫ���������װ��������6�����ͣ�
const int max_battle_hero_num = 6;			//�������6��Ӣ������


const std::string goldName = "gold";		//�������������ǵ�key
const std::string diamondName = "diamond";	//����������ʯ����key
const std::string levelName = "level";		//����ȼ���key
const std::string expName = "exp";			//���澭���key


//-------------------------------------------------------------

//��ϸ��ť������ͼƬ����
const std::string btnDetails1 = "btns/details1.png";
const std::string btnDetails2 = "btns/details2.png";

//����ͼ�꣬�磺������ħ����������....
const std::string hpIco = "icos/hp.png";
const std::string apIco = "icos/ap.png";
const std::string mpIco = "icos/mp.png";
const std::string defineIco = "icos/define.png";
const std::string mDefineIco = "icos/mdefine.png";
const std::string speedIco = "icos/speed.png";
const std::string critIco = "icos/crit.png";
const std::string blockIco = "icos/block.png";


//---------------���ؼ����õı�ǩ���֣�node->setName()��-----------------------------------
const std::string blockTagName = "blockName";		//BlockLayer�ı�ǩ���֣�����ͨ����ǩ���ֻ�ȡʵ������


#endif // __CONSTANTDEFINE_H_
