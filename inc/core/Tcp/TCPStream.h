#ifndef _TCP_STREAM_H_
#define _TCP_STREAM_H_

#include <string>
#include <winsock2.h>

class TCPStream
{
public:
	friend class TCPAcceptor;

	~TCPStream();

	std::string getPeerIP();

	int getPeerPort();

	int receive(char* buffer, int len);
	int send(const char* buffer, int len);

private:
	TCPStream();

	TCPStream(SOCKET msock, struct sockaddr_in* address);

	SOCKET msgsock;

	std::string m_peerIP;
	int m_peerPort;
};

#endif	//_TCP_STREAM_H_