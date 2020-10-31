#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_alarm(int sig)
{
	printf("---the signal received is %d. \n", sig);
	signal(SIGINT, SIG_DFL);
}

int main()
{
	signal(SIGINT, sig_alarm);
	while(1) 
	{
		printf("waiting here!\n");
		sleep(1);
	}
	return 0;
}
