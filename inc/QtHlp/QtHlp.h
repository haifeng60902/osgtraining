#ifndef _QT_HLP_H_
#define _QT_HLP_H_

#include <string>
#include <QTcpSocket>

namespace QtHlp
{
	bool ChkStr(QTcpSocket* sock, std::string* s);
}

#endif	//_QT_HLP_H_