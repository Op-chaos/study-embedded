#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
static int alarm_fired = 0;

void ding(int sig)
{
	alarm_fired = 1;
}

int main()
{
	int pid;
	printf("alarm application starting\n");
	if((pid = fork()) == 0)    // 在子进程中运行部分 
	{
		sleep(5);
		kill(getppid(), SIGALRM);
		exit(0);
	}
	printf("waiting for alarm to go off\n");  // 父进程运行的部分
	signal(SIGALRM, ding);
	pause();
	if (alarm_fired)
		printf("Signal is received!\n");
	printf("done\n");
	exit(0);
}
