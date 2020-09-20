#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
// ./a.out ./5 0777   和  ./a.out ./5 777 不同
int main(int argc, char* argv[])
{
	int mode = 0;

	mode = atoi(argv[2]);
	printf("mode:%d",mode);
	mkdir(argv[1],0747);
	// getchar();
	// rmdir(argv[1]);
	return 0;
}

