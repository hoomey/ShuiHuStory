/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	ClientLayer.h
// Author:		 Metoor
// Version: 	1.0 
// Date: 		2016/12/03
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef CLIENTLAYER_H_  
#define CLIENTLAYER_H_  

#include "cocos2d.h"
#include "SocketClient.h"
#include "TypeStruct.h"
#include <string>

class ClientLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(ClientLayer);

	void sendMessage(std::string& content, int cmd);
	
	//�������ӵĶ˿ں�
	void initSocket(int port);

protected:
	void connectThread();

	//���socket������Ϣ
	void addConnectMessageListener();

	void onRecv(const char* data, int count);
	void onDisconnect();

	int check(MyMSG * msg);

	void onEnter() override;
	void onExit() override;

private:
	std::string _ip;
	int _port;
	PVPData _data;

protected:
	SocketClient* _client;
};

#endif // CLIENTLAYER_H_ 
