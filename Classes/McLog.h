/*************************************************
// Copyright (C), 2016-2020, CS&S. Co., Ltd.
// File name: 	McLog.h
// Author:		 Metoor
// Version: 	1.0
// Date: 		2016/11/07
// Contact: 	caiufen@qq.com
// Description: 	create by vs2015pro
*************************************************/

#ifndef __MCLOG_H__
#define __MCLOG_H__

#include <string>
#include <cstdio>

class McLog {
public:
	McLog(std::string fileName = "log.mc");
	~McLog();

	//msg:����������fileName:������ļ�����line:���������
	void addWaring(const std::string& msg, const std::string& fileName, int line);
	void addError(const std::string& msg, const std::string& fileName, int line);

private:
	void addLog(const std::string& msg, bool isWaring, const std::string& fileName, int line);
	void saveLog();

private:
	bool _isError;

	//���������Ϣ
	std::string _log;
	std::string _fileName;
};
#endif // MCLOG_H_
