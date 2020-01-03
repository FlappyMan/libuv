#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "BackTrade_Marco.h"


using namespace std;

class CSocketOper
{
public:
	CSocketOper();
	virtual ~CSocketOper();

public:
	bool Bind(int sock);
	bool Listen(int sock);
	bool Accept(int sock, int &newsock, sockaddr_in *clientaddr, int *addrlen);
};

class Socket 
{
public:
	Socket();
	virtual ~Socket();

public:
	bool Create();
	bool Send(const char *buf, int len, int &ret);
	bool Recv(char *buf, int len, int &ret);
	bool Close();

protected:
	bool SetNonBlocking();

private:
	int m_sock;
};

#endif /* SOCKET_H_ */
