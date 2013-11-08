#include "Tcp/TCPConnector.h"

#include <iostream>

#pragma comment(lib, "ws2_32.lib")

TCPConnector::TCPConnector(bool bWSA):m_bWSA(bWSA)
{
	int retval=0;
	if (!bWSA)
		return;

	// Request Winsock version 2.2
	if ((retval = WSAStartup(0x202, &wsaData)) != 0)
	{
		std::cout<<"Server: WSAStartup() failed with error "<<retval<<std::endl;
		WSACleanup();
	}
	else
		std::cout<<"Server: WSAStartup() is OK."<<std::endl;
}

TCPConnector::~TCPConnector()
{
	if (m_bWSA)
		WSACleanup();
}

TCPStream* TCPConnector::connect(int port, const char* server_name)
{
	// Attempt to detect if we should call gethostbyname() or gethostbyaddr()
	
	static bool bLog=true;
	struct hostent *hp=NULL;
	if (isalpha(server_name[0]))
	{   // server address is a name
		hp = gethostbyname(server_name);
	}
	else
	{ // Convert nnn.nnn address to a usable one
		unsigned int addr = inet_addr(server_name);
		hp = gethostbyaddr((char *)&addr, 4, AF_INET);
	}

	if (hp == NULL )
	{
		std::cout<<"Client: Cannot resolve address "<<server_name<<": Error "<<WSAGetLastError()<<std::endl;
		//WSACleanup();
		return NULL;
	}
	else
		if (bLog)
			std::cout<<"Client: gethostbyaddr() is OK."<<std::endl;

	// Copy the resolved information into the sockaddr_in structure
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	memcpy(&(server.sin_addr), hp->h_addr, hp->h_length);
	server.sin_family = hp->h_addrtype;
	server.sin_port = htons(port);

	SOCKET conn_socket = socket(AF_INET, SOCK_STREAM, 0); /* Open a socket */

	if (conn_socket <0 )
	{
		std::cout<<"Client: Error Opening socket: Error "<<WSAGetLastError()<<std::endl;
		//WSACleanup();
		return NULL;
	}
	else
		if (bLog)
			std::cout<<"Client: socket() is OK."<<std::endl;

	if (bLog)
		std::cout<<"Client: Client connecting to: "<<hp->h_name<<std::endl;
	if (::connect(conn_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		std::cout<<"Client: connect() failed: "<<WSAGetLastError()<<std::endl;
		closesocket(conn_socket);
		//WSACleanup();
		return NULL;
	}
	else
		if (bLog)
			std::cout<<"Client: connect() is OK."<<std::endl;

	bLog=false;
	return new TCPStream(conn_socket, &server);
}