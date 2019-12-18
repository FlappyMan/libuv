#include "Socket.h"

Socket::Socket() 
{
	// TODO Auto-generated constructor stub

}

Socket::~Socket() 
{
	// TODO Auto-generated destructor stub
}

// 
/**************************************************
* 类名		: Socket
* 函数名	: set_notblocking
* 返回类型	: bool
* 函数功能	: 设置socket为非阻塞模式
* 参数描述	: sock	: socket句柄
*			: ret	: 操作是否成功
**************************************************/
bool Socket::SetNonBlocking()
{
	int ret;
	if ( 0 >= m_sock ) 
		return false;

	ret = ::fcntl(m_sock, F_GETFL, 0);
	if ( 0 > ret )
		return false;

	ret = (ret | O_NONBLOCK);
	ret = ::fcntl(m_sock, F_SETFL, ret);

	if ( 0 > ret )
		return false;
	return true;
}

bool Socket::Create()
{
	m_sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

	if ( 0 > m_sock )
		return false;	// 套接字创建失败

	int opt = 1;		//SO_REUSEADDR

	if( -1 == setsockopt( m_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) ) )
		return false;
	return true;
}



bool CSocketOper::Bind(int sock)
{
	if ( 0 >= sock ) 
		return false;

	struct sockaddr_in m_addr;
	m_addr.sin_family		= AF_INET;
	m_addr.sin_addr.s_addr	= inet_addr(SERVER_IP);	//INADDR_ANY
	m_addr.sin_port			= htons(SERVER_PORT);

	int ret = bind ( sock, ( struct sockaddr * ) &m_addr, sizeof ( m_addr ) );

	if ( 0 > ret )
		return false;
	return true;
}



bool CSocketOper::Listen(int sock)
{
	if ( 0 >= sock ) 
		return false;
	int ret = listen ( sock, SOCK_MAX_LISTEN );
	if ( 0 > ret )
		return false;
	return true;
}


/**************************************************
* 类名		: 接受socket连接请求
* 函数名	: accept
* 返回类型	: bool
* 函数功能	: 接受socket的连接请求并将接受的值保存在newsocket中
* 参数描述	: sock		: 触发的sock句柄
*			: newsock	: 用于保存接收以后的返回值进行连接判断
*			: clientaddr; 客户端连接地址
*			: addrlen	: 地址长
**************************************************/
bool CSocketOper::Accept(int sock, int & newsock, sockaddr_in *clientaddr, int *addrlen)
{
	newsock = accept ( sock, ( sockaddr * ) clientaddr, ( socklen_t * ) addrlen );
	if( 0 > newsock ) 
		return false;
	return true;
}



bool Socket::Send( const char *buf, int len, int & ret)//
{
	ret = ::send ( m_sock , buf , len , MSG_NOSIGNAL );
	if ( 0 < ret || EAGAIN == errno || EINTR == errno || EWOULDBLOCK == errno ) 
		return true;
	return false;
}


/**************************************************
* 类名		: Scoket
* 函数名	: recv
* 返回类型	: bool
* 函数功能	: 获取socket句柄代表的缓冲区数据
* 参数描述	: sock	: 缓冲区句柄
*			: buf	: 存放数据的缓冲区
*			: len	: 缓冲区最大长度
*			: ret	: 在linux中recv函数的返回值为拷贝的字节个数（数据流长度）
**************************************************/
bool Socket::Recv(char *buf, int len, int & ret)
{
	// ret值代表buf变量中实际拷贝的数据长度
	ret = recv( m_sock , buf , len , MSG_NOSIGNAL );

	if ( 0 < ret || EAGAIN == errno || EINTR == errno || EWOULDBLOCK == errno ) 
		return true;
	return false;
}


bool Socket::Close()
{
	return ( 0 == ::close( m_sock ) );
}

