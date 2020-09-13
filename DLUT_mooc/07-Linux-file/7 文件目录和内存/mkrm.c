#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	mkdir(argv[1],0);
	getchar();
	rmdir(argv[1]);
	return 0;
}

