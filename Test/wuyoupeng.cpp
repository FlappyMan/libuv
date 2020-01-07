#include "UProtocol.h"

#define DEFAULT_PORT 8000
#define MAXLINE 4096

int main(int argc, char **argv)
{
	UPUptrade up;
	up.set_token("123");
	up.set_paypassword("456");
	up.set_marketid(1);
	up.set_price(2);
	up.set_num(3);
	up.set_type(4);
	up.set_main_coin(5);

	const int BUFFSIZE = 1024;
	char buffer[BUFFSIZE];
	int iLen = ProtoPack<UPUptrade>(buffer, BUFFSIZE, up);
	buffer[iLen] = '\0';
	// cout<<buffer<<endl;

	int sockfd, n, rec_len;
	char recvline[4096], sendline[4096];
	char buf[MAXLINE];
	struct sockaddr_in servaddr;

	if (argc != 2)
	{
		printf("usage: ./client <ipaddress>\n");
		exit(0);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9998);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s\n", argv[1]);
		exit(0);
	}

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	printf("send msg to server: \n");
	if (send(sockfd, buffer, iLen, 0) < 0)
	{
		printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}
	// while (sendline[0] != '*')
	// {
	// 	fgets(sendline, 4096, stdin);
	// 	if (send(sockfd, sendline, strlen(sendline), 0) < 0)
	// 	{
	// 		printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
	// 		exit(0);
	// 	}
	// 	memset(sendline,0,4096);
	// }

	if ((rec_len = recv(sockfd, buf, MAXLINE, 0)) == -1)
	{
		perror("recv error");
		exit(1);
	}
	buf[rec_len] = '\0';
	printf("Received : %s ", buf);
	return 0;
}