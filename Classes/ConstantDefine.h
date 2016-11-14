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

const std::string save_hero_file_name = "myHeroCard.me";			//����������һ��Ӣ�ۿ������ݵ��ļ�����
const std::string save_equipment_file_name = "myEquipment.me";	//����������һ��װ�����ݵ��ļ�����
const std::string equipment_file_name = "datas/equipment.data";		//��������װ���Ļ������ݵ��ļ�����
const std::string hero_file_name = "datas/hero.data";				//��������Ӣ�ۿ��ƻ������ݵ��ļ�����

const int equipment_map_max_size = 50;		//���ӵ�е����װ����
const int hero_card_map_max_size = 50;		//���ӵ��Ӣ�ۿ����������

const int max_gold = 100000;				//�����ͬʱӵ�е��������
const int max_diamond = 10000;				//�����ͬʱӵ�е����ר����

const int max_level = 100;					//������ȼ�
const int start_exp = 300;					//����ʼ��õľ���ֵ
const float start_exp_rate = 1.1f;			//���㵱ǰ�ȼ��������辭��ʱ�ı���
const int init_unique_num = 1000;			//Ψһ������ʼ��С

const int none = -1;						//��ʾû�л���Ӣ��װ��λ��û��װ�����߱�ʾװ��û��ʹ����
const int max_equipment_num = 6;			//��ɫ���������װ��������6�����ͣ�
const int max_battle_hero_num = 6;			//�������6��Ӣ������

const int init_glod = 5000;					//��ҳ�ʼ��õĽ��
const int init_level = 1;					//��ҳ�ʼ�ĵȼ�
const int init_diamond = 1200;				//��ҳ�ʼ��õ���ʯ

const int intensify_base_diamond = 25;		//ǿ��װ���Ϳ��Ƶ�ʱ����Ҫ�Ļ�����ʯ
const int levelup_base_gold = 300;		//����װ����ǿ����ʱ����Ҫ�Ļ������

const int login_gold_base = 1000;		//ÿ�ս����Ļ����������
const int login_diamond_base = 10;		//ÿ�ս����Ļ���������ʯ

const std::string goldName = "gd";		//�������������ǵ�key
const std::string diamondName = "dd";	//����������ʯ����key
const std::string levelName = "ll";		//����ȼ���key
const std::string expName = "ep";			//���澭���key
const std::string uniqueNumName = "uqm"; //��������Id��Ψһ��

const std::string is_effect_mute_name = "et"; //�����Ƿ�������Ч��key
const std::string is_bg_mute_name = "et"; //�����Ƿ����ñ������ֵ�key

//�Զ�����Ϣ
const string msg_update_user_data = "MSG_UPDATE_USER_DATA";	//�����û����ݵ���Ϣ��
const string msg_update_display_item = "MSG_UPDATE_DISPLAY_ITEM";	//����ǿ�������������DisplayLayer�б��item������ʾ


//�����Զ�����Ϣʱ�Ĳ���
const int msg_update_display_item_parameter_update = 0; //������ǿ��
const int msg_update_display_item_parameter_abandon = 1; //����
const int msg_update_display_item_parameter_sell = 2; //����

//��սӢ�۱���ʱ��key
const std::string battleSaveKey[max_battle_hero_num] = { "0", "1", "2", "3", "4", "5" };

//ÿ�յ�½����
const std::string preGetTime = "pgt"; //�ϴ���ȡ������ʱ��

//-------------------------------------------------------------

//��ϸ��ť������ͼƬ����
const std::string btnDetails1 = "btns/details1.png";
const std::string btnDetails2 = "btns/details2.png";
const std::string sound_off_1 = "btns/menu_sound_off_1.png";
const std::string sound_off_2 = "btns/menu_sound_off_2.png";
const std::string sound_on_1 = "btns/menu_sound_on_1.png";
const std::string sound_on_2 = "btns/menu_sound_on_2.png";


//����ͼ�꣬�磺������ħ����������....
const std::string hpIco = "icos/hp.png";
const std::string apIco = "icos/ap.png";
const std::string mpIco = "icos/mp.png";
const std::string defineIco = "icos/define.png";
const std::string mDefineIco = "icos/mdefine.png";
const std::string speedIco = "icos/speed.png";
const std::string critIco = "icos/crit.png";
const std::string critDmg = "icos/critDmg.png";
const std::string blockIco = "icos/block.png";

//��������
const int itemCount = 18;	//�ܹ��ж��ٸ�item
const int item_level_base = 5;	//�ȼ�����������
const int item_level_increaseNum = 5;	//�ȼ�����������
const int item_gold_increaseNum = 5000;	//�������
const int item_diamond_increaseNum = 50;//��ʯ����������
const int gift_base_gold = 10000;	//����Ļ��������
const int gift_base_diamond = 100;	//����Ļ�����ʯ��
const std::string is_get_gift_key = "iggk%d"; //�����û��Ƿ���ȡ�����key


//--------string.plist�ļ��ֵ������ַ���Դ����-------------------------------------------------------------------
const std::string level_d = "level_d";
const std::string intensify_d = "intensify_d";
const std::string star_d = "star_d";
const std::string speed_d = "speed_d";
const std::string block_d = "block_d";
const std::string hp_d = "hp_d";
const std::string critDmg_d = "critDmg_d";
const std::string crit_d = "crit_d";
const std::string ap_d = "ap_d";
const std::string mp_d = "mp_d";
const std::string define_d = "define_d";
const std::string mDefine_d = "mDefine_d";

//����Ի���������ʾ������Դ����
const std::string error = "error";
const std::string errorContent = "errorContent";

const std::string levelupTitle = "levelupTitle";		//�����ַ�'����'��Դ����
const std::string intensifyTitle = "intensifyTitle";	//�����ַ�'ǿ��'��Դ����
const std::string levelTips = "levelTips";				//������ʾ����
const std::string intensifyTips = "intensifyTips";	//ǿ����ʾ����
const std::string notEnoughGold = "notEnoughGold";		//��Ҳ���
const std::string notEnougMaterial = "notEnougMaterial";//���ϲ���
const std::string notEnougDiamond = "notEnoughDiamond";	//��ʯ����
const std::string succed = "succed";					//�ɹ�
const std::string failed = "failed";					//ʧ��


const std::string sellTitle = "sellTitle";					//���۶Ի������
const std::string abandonTitle = "abandonTitle";			//�����Ի������
const std::string sellTips = "sell";					//���۶Ի�����ʾ����
const std::string abandonTips = "abandon";			//�����Կ���ʾ����
const std::string sellSucced = "sellSucced";			//���۳ɹ���ʾ
const std::string abandonSucced = "abandonSucced";		//�����ɹ���ʾ

const std::string levelup_gift = "levelupGift";		//�ȼ����(10�����)


//ÿ�յ�½����
const std::string loginRewardTips = "loginRewardTips"; //��½������ȡ��ʾ
const std::string loginRewardTimeTips1 = "loginRewardTimeTips1"; //��û����ȡʱ����ʾ
const std::string loginRewardTimeTips2 = "loginRewardTimeTips2"; //������ȡʱ����ʾ
const std::string rewardGold = "rewardGold"; //�����Ľ���ַ���
const std::string rewardDiamond = "rewardDiamond"; //��������ʯ���ַ���


//---------------���ؼ����õı�ǩ���֣�node->setName()��-----------------------------------
const std::string blockTagName = "blockName";		//BlockLayer�ı�ǩ���֣�����ͨ����ǩ���ֻ�ȡʵ������
const std::string tipsTagName = "tips";				//��ʾ��ı�ǩ����
const std::string dialogTagName = "dialog";			//ģ̬�Ի���ı�ǩ����


//��������Ч������
const std::string firstSceneMusicName = "audios/wellcomeBg.mp3";
const std::string clickEffectName = "audios/click.mp3";
const std::string rewardGoldEffectName = "audios/reward.mp3";
const std::string dropEffectName = "audios/drop.mp3";


#endif // __CONSTANTDEFINE_H_
