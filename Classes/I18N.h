#ifndef __I18N_H__
#define __I18N_H__

#include <unordered_map>

class I18N{
public:
	~I18N();

	static I18N* getInstance();
	
	//�����ַ��ļ�
	void loadStringFile(std::string fileName);

	//ͨ����ֵ��ȡ�����ַ���---ע�⣺���ñ�����ǰ����ȷ���Ѿ����ù�loadStringFile
	const std::string* getStringByKey(std::string key);

	void dstoryInstance();

private:
	I18N();

private:
	std::unordered_map<std::string, std::string>* _map;

	static I18N* _instance;
};

#endif // I18N_H_
