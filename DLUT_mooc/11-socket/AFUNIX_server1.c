#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
	int server_sockfd, client_sockfd;   // 套接字标识符
	int server_len, client_len;         // 套接字地址长度
	struct sockaddr_un server_address;  // 套接字地址 监听套接字
	struct sockaddr_un client_address;  // 套接字地址 客户套接字
    unlink("server_socket");            // 如果当前系统中之前存在该套接字文件，则删除
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);   // 返回套接字文件描述符
	server_address.sun_family = AF_UNIX;               // 设置套接字类型
	strcpy(server_address.sun_path, "server_socket");  // 设置文件名
	server_len = sizeof(server_address);               // 地址长度
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	listen(server_sockfd, 5);    // 创建监听队列
	while(1) 
	{
		char ch;
		printf("server waiting\n");
		client_len = sizeof(client_address);     // 获得客户端套接字长度
		// accept 会造成系统阻塞，直至客户端到来
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
		read(client_sockfd, &ch, 1);
		ch++;
		write(client_sockfd, &ch, 1);
		close(client_sockfd);
	}
}