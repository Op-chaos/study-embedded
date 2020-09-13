#include <unistd.h>
#include <stdio.h>
int main()
{
	char buf[80];
	getcwd(buf,sizeof(buf));
	printf("current working directory : %s\n",buf);
	return 0;
}
