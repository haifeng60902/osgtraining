#ifndef _QT_HLP_H_
#define _QT_HLP_H_

#include <vector>
#include <string>
#include <QTcpSocket>

namespace QtHlp
{
	bool GetStr(QTcpSocket* sock, std::string* str, std::string* loc);
	void WriteStr(QTcpSocket* sock, const std::string& s);

	bool GetStrs(QTcpSocket* sock, std::vector<std::string>* vs);
	void WriteStrs(QTcpSocket* sock, const std::vector<std::string>& vs);
}

#endif	//_QT_HLP_H_