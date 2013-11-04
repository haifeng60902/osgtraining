#include "Tcp/TCPStream.h"

TCPStream::TCPStream(SOCKET msock, struct sockaddr_in* address):msgsock(msock)
{
	m_peerIP=std::string(inet_ntoa(address->sin_addr));
	m_peerPort=ntohs(address->sin_port);
}

TCPStream::~TCPStream()
{
	closesocket(msgsock);
}

std::string TCPStream::getPeerIP()
{
	return m_peerIP;
}

int TCPStream::getPeerPort()
{
	return m_peerPort;
}

int TCPStream::receive(char* buffer, int len) 
{
	return recv(msgsock, buffer, len, 0);
}

int TCPStream::send(const char* buffer, int len) 
{
	return ::send(msgsock, buffer, len, 0);
}