#ifndef __tcpacceptor_h__
#define __tcpacceptor_h__

#include <string>
#include <winsock2.h>

#include "TCP/TCPStream.h"

class TCPAcceptor
{    
  public:
    TCPAcceptor(int port, const char* address="");
    ~TCPAcceptor();

    int start();
    TCPStream* accept();

  private:
    TCPAcceptor(){};

	int m_port;
	std::string m_address;
	bool m_listening;

	WSADATA wsaData;
	struct sockaddr_in local;
	SOCKET listen_socket, msgsock;
};

#endif
