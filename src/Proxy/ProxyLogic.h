#ifndef _PROXY_LOGIC_H_
#define _PROXY_LOGIC_H_

#include <string>

class TCPAcceptor;
class TCPConnector;
class TCPStream;

class ProxyLogic
{
public:
	ProxyLogic();
	~ProxyLogic();

	void Init(const std::string& sLocalAddress, const std::string& sRemoteAddress, int iLocalPort, int iRemotePort);

	void Process();

private:

	int Accumulate(TCPStream* streamClient);

	std::string m_sLocalAddress;
	std::string m_sRemoteAddress;
	int m_iLocalPort;
	int m_iRemotePort;

	TCPAcceptor* m_pAcceptor;
	TCPConnector* m_pConnector;

	int m_iResult;
	char inBuffServer[8192];
	char inBuffClient[8192];
};

#endif	//_PROXY_LOGIC_H_