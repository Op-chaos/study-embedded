#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
void err_quit(char *msg);

int main(int argc, char *argv[])
{
	int fdin;			//文件描述符
	char *src;			//内存首地址指针
	struct stat statbuf;		//文件状态结构
	off_t len;			//长度
	/* 检测一个是否共有两个参数 */
	if(argc != 2) 
	{
		fprintf(stderr, "usage: mmcat {file}\n");
		exit(EXIT_FAILURE);
	}
	/* 打开磁盘文件 */
	if((fdin = open(argv[1], O_RDONLY)) < 0) 
	{
		err_quit("open");
	}

	/* 要调用mmap，必须先知道磁盘文件的大小，通过调用fstat来得到 */
	if((fstat(fdin, &statbuf)) < 0) 
	{
		err_quit("fstat");
	}
	len = statbuf.st_size;

	/* 把文件映象到内存中 */
	if((src = mmap(0, len, PROT_READ, MAP_SHARED, fdin, 0)) == (void *)-1) 
	{ 
		err_quit("mmap");
	}

	/* 输出映射到内存中的文件的内容 */
	printf("%s", src);

	/* 清理工作 */
	close(fdin);
	munmap(src, len);

	exit(EXIT_SUCCESS);
}

void err_quit(char *msg) 
{
	perror(msg);
	exit(EXIT_FAILURE);
}
