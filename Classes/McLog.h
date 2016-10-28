#ifndef __MCLOG_H__
#define __MCLOG_H__

#include <string>
#include <cstdio>

class McLog{
public:
	McLog(std::string fileName = "log.me");
	~McLog();

	//msg:����������fileName:������ļ�����line:���������
	void addWaring(std::string msg, std::string fileName, int line);
	void addError(std::string msg, std::string fileName, int line);
	
private:
	void addLog(std::string msg, bool isWaring, std::string fileName, int line);
	void saveLog();

private:
	bool _isError;

	//���������Ϣ
	std::string _log;
	std::string _fileName;
};
#endif // MCLOG_H_
