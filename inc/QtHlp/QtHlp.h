#ifndef _QT_HLP_H_
#define _QT_HLP_H_

#include <string>
#include <QTcpSocket>

namespace QtHlp
{
	bool GetStr(QTcpSocket* sock, std::string* s);
	void WriteStr(QTcpSocket* sock, const std::string& s);
}

#endif	//_QT_HLP_H_