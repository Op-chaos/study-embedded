#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	pid_t child;		
	int num = 0;
	int status;
	if((child = fork()) == -1) {	//创建进程失败 
		perror("fork");
		exit(EXIT_FAILURE);
	} else if(child == 0) {	 //子进程中的child值为0
		puts("in child");
		num = num + 10;
		printf("num = %d ------", num);
		printf("------");
		char *argv[] = {"ls -l", NULL};  
		if(execve("/bin/ls", argv, NULL) == -1) {
			perror("execve");
			exit(EXIT_FAILURE);
		}	
		exit(EXIT_SUCCESS);
	} else {   //父进程中的child值为产生的子进程的id
		waitpid(child, &status, 0); 
		puts("\nin parent");
		num = num + 20;
		printf("num = %d\n", num);
		printf("\tparent pid = %d\n", getpid());
		printf("\tparent ppid = %d\n", getppid());
	}
	exit(EXIT_SUCCESS);
}
