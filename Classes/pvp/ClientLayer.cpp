/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	ClientLayer.cpp
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/12/03
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#include "ClientLayer.h"
#include <thread>
#include "McLog.h"

USING_NS_CC;
using std::string;


bool ClientLayer::init()
{
	if ( !(Layer::init()))
	{
		return false;
	}
	addConnectMessageListener();


	return true;
}

void ClientLayer::initSocket(int port)
{
	_port = port;

	_client = SocketClient::construct();
	_client->onRecv = CC_CALLBACK_2(ClientLayer::onRecv, this);
	_client->onDisconnect = CC_CALLBACK_0(ClientLayer::onDisconnect, this);
}

void ClientLayer::connectThread()
{
	//���ļ�����������ip�����Ϊ������Ϊ��������
	if (_ip.empty())
	{
		_ip = FileUtils::getInstance()->getStringFromFile("datas/ipconfig.mc");

		if (_ip.empty())
		{
			_ip += "127.0.0.1";
		}
	}

	int result = 1;

	if (_client->connectServer(_ip.c_str(), _port))
	{
		result = 0;
	}
	else
	{
		McLog mc;
		mc.addWaring("connect server failed...", __FILE__, __LINE__);
	}

	//��cocos���߳��з�������״̬��Ϣ 0/��ʾ�ɹ� 1/��ʾʧ��
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, result]() {
		_eventDispatcher->dispatchCustomEvent(msg_socket_connect, (void*)result);

		//McLog mc;
		//mc.addWaring("get data success, rung pvp scene...", __FILE__, __LINE__);
	});
}

void ClientLayer::onEnter()
{
	Layer::onEnter();

	//�첽���ӷ�����
	std::thread th(&ClientLayer::connectThread, this);
	th.detach();
}

void ClientLayer::onExit()
{
	Layer::onExit();

	if (_client)
	{
		_client->destroy();
		_client = nullptr;
	}
}

void ClientLayer::addConnectMessageListener()
{
	//ע�ᣬsocket��ʼ����״̬��Ϣ��0��ʾ�ɹ���1��ʾʧ��
	auto listen = EventListenerCustom::create(msg_socket_connect, [&](EventCustom* event) {
		int result = (int)(event->getUserData());

		//����ʧ�ܣ����Լ��Ӹ��ڵ��Ƴ�
		if (result == 0)
		{
			//�ɹ�
		}
		else
		{
			McLog mc;
			mc.addWaring("can not init socket...", __FILE__, __LINE__);

			this->removeFromParentAndCleanup(true);
		}
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
}

void ClientLayer::onRecv(const char* data, int count)
{
	std::string*  content;

	auto msg = (MyMSG*)data;

	if (sizeof(*msg) == count)
	{
		if (msg->cmd == 0)  //���cmd����0����ѽ��յ������ݴ�����m_enemyData��
		{
			content = &_data.enemyData;
		}
		else if (msg->cmd == 1 || msg->cmd == 2 || msg->cmd == 3)	//���cmd����1��2��3����ѽ��յ������ݴ�����m_batteData��
		{
			content = &_data.battleData;
		}

		if (msg->checknum == check(msg) && strcmp(msg->head, "com.metoor.cai") == 0)
		{
			//����Ӣ������
			*content += msg->content;

			if (content->length() == msg->length)
			{
				switch (msg->cmd)
				{
				case 0:
					//���ܵз�Ӣ������
					return;
					break;
				case 1:
				case 2:
				case 3:
					//���idΪ3�����ʾ���ͻ��˻�ʤ���Է�������
					//idΪ1����2����ʾ�ÿͻ��������1�������2
					_data.playerId = msg->cmd;
					break;
				default:
					break;
				}

				//��cocos���߳�������PVP����
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([&]() {
					cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(msg_create_pvp_scene, (void*)&_data);
					_client->destroy();
					_client = nullptr;
					this->removeFromParentAndCleanup(true);
					//McLog mc;
					//mc.addWaring("get data success, rung pvp scene...", __FILE__, __LINE__);
				});
			}
		}
		else
		{
			McLog mc;
			mc.addWaring("data head error...", __FILE__, __LINE__);
		}
	}
	else
	{
		McLog mc;
		mc.addWaring("receive data size error...", __FILE__, __LINE__);
	}
}

void ClientLayer::onDisconnect()
{
	//���ͶϿ�������Ϣ
	_eventDispatcher->dispatchCustomEvent(msg_socket_disconnect);
	this->removeFromParentAndCleanup(true);
}

void ClientLayer::sendMessage(std::string& content, int cmd)
{
	MyMSG msg;
	strcpy(msg.head, "com.metoor.cai");
	msg.cmd = cmd;
	msg.length = content.length();
	strcpy(msg.content, content.c_str());
	msg.checknum = check(&msg);

	_client->sendMessage((char*)&msg, sizeof(msg));
}

int ClientLayer::check(MyMSG* msg)
{
	return strlen(msg->content);
}