#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	char c[80];
	chdir(argv[1]);
	printf("%s\n",getcwd(c,80));
	return 0;
}
