#ifndef _TCP_CONNECTOR_H_
#define _TCP_CONNECTOR_H_

#include <winsock2.h>

#include "TCP/TCPStream.h"

class TCPConnector
{
public:

	TCPConnector(bool bWSA=true);
	~TCPConnector();

	TCPStream* connect(int port, const char* server_name);

private:
	int resolveHost(const char* host, struct in_addr* addr);

	WSADATA wsaData;

	bool m_bWSA;
};

#endif	//_TCP_CONNECTOR_H_