#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512

 
int main()
{
	
	printf("%d",IPC_NOWAIT);
	exit(EXIT_SUCCESS);
}
