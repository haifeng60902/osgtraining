#include "tcp/tcpacceptor.h"

#include <iostream>

#pragma comment(lib, "ws2_32.lib")

TCPAcceptor::TCPAcceptor(int port, const char* address) 
    : m_port(port), m_address(address), m_listening(false)
{
	int retval=0;
	
	// Request Winsock version 2.2
	if ((retval = WSAStartup(0x202, &wsaData)) != 0)
	{
		std::cout<<"Server: WSAStartup() failed with error "<<retval<<std::endl;
		WSACleanup();
	}
	else
		std::cout<<"Server: WSAStartup() is OK."<<std::endl;
} 

TCPAcceptor::~TCPAcceptor()
{
  
}

int TCPAcceptor::start()
{
    if (m_listening == true)
	{
        return 0;
    }

	local.sin_family = AF_INET;
	local.sin_addr.s_addr = (m_address.empty()) ? INADDR_ANY:inet_addr(m_address.c_str());

	/* Port MUST be in Network Byte Order */
	local.sin_port = htons(m_port);

	// TCP socket
	listen_socket = socket(AF_INET, SOCK_STREAM,0);
	if (listen_socket == INVALID_SOCKET)
	{
		std::cout<<"Server: socket() failed with error "<<WSAGetLastError()<<std::endl;
		WSACleanup();
		return -1;
	}
	else
		std::cout<<"Server: socket() is OK."<<std::endl;

	// bind() associates a local address and port combination with the socket just created.
	// This is most useful when the application is a 
	// server that has a well-known port that clients know about in advance.
	if (bind(listen_socket, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR)
	{
		std::cout<<"Server: bind() failed with error "<<WSAGetLastError()<<std::endl;
		WSACleanup();
		return -1;
	}
	else
		std::cout<<"Server: bind() is OK."<<std::endl;

	// So far, everything we did was applicable to TCP as well as UDP.
	// However, there are certain steps that do not work when the server is
	// using UDP. We cannot listen() on a UDP socket.
	if (listen(listen_socket,5) == SOCKET_ERROR)
	{
		std::cout<<"Server: listen() failed with error "<<WSAGetLastError()<<std::endl;
		WSACleanup();
		return -1;
	}
	else
		std::cout<<"Server: listen() is OK."<<std::endl;

	m_listening = true;
	return 0;
}

TCPStream* TCPAcceptor::accept() 
{
    if (m_listening == false) {
        return NULL;
    }

    struct sockaddr_in from;
    int len = sizeof(from);
    memset(&from, 0, len);
    SOCKET msgsock = ::accept(listen_socket, (struct sockaddr*)&from, &len);
   
	if (msgsock == INVALID_SOCKET)
	{
		std::cout<<"Server: accept() error "<<WSAGetLastError()<<std::endl;
		WSACleanup();
		return NULL;
	}
	else
		std::cout<<"Server: accept() is OK."<<std::endl;

	std::cout<<"Server: accepted connection from "<<inet_ntoa(from.sin_addr)<<", port "<<htons(from.sin_port)<<std::endl;

    return new TCPStream(msgsock, &from);
}