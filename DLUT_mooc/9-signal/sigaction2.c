#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_alarm(int sig)
{
	printf("---the signal received is %d. \n", sig);
}

int main()
{
	struct sigaction act;
	act.sa_handler = sig_alarm;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, 0);
	while(1) 
	{
		printf("waiting here!\n");
		sleep(1);
	}
}
