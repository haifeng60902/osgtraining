#ifndef _QT_HLP_H_
#define _QT_HLP_H_

#include <vector>
#include <string>
#include <QTcpSocket>

namespace QtHlp
{
	bool GetStr(QTcpSocket* sock, std::string* str, std::string* loc);
	void WriteStr(QTcpSocket* sock, const std::string& s);

	bool GetStrs(int bytesReceived, char* data, std::vector<std::string>* vs);
	void WriteStrs(const std::vector<std::string>& vs, std::vector<char>& data);

	//generate random string
	void rndStr(std::string* str, int len_from, int len_to);
}

#endif	//_QT_HLP_H_