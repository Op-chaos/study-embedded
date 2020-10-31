#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char ch = 'A';
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");   //根据服务器情况设置连接地址
	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *)&address, len);  //连接到服务器
	if(result == -1) 
	{
		perror("oops: client1");
		exit(1);
	}
	write(sockfd, &ch, 1);  // 通过套接字文件描述符读写信息
	read(sockfd, &ch, 1);
	printf("char from server = %c\n", ch);
	close(sockfd);
	exit(0);
}
