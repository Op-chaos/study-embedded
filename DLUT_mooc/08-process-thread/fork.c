#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int num = 0;
    pid_t child;
    if((child = fork()) == -1) { //创建进程失败执行以下代码
		perror("fork");
		exit(EXIT_FAILURE);
    } else if(child == 0) {  //子进程执行以下代码
		puts("in child");
		num = num + 10;
		printf("num = %d ------", num);
		printf("------");
		printf("\tchild pid = %d\n", getpid());
		printf("\tchild ppid = %d\n", getppid());
		exit(EXIT_SUCCESS);
    } else {   // 父进程执行以下代码
		puts("in parent");
		num = num + 20;
		printf("num = %d\n", num);
		printf("\tparent pid = %d\n", getpid());
		printf("\tparent ppid = %d\n", getppid());
    }
    exit(EXIT_SUCCESS);
}
