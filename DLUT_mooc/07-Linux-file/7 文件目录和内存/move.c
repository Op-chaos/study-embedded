#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{ 
	int res;
	if(argc!=3)
	{ 
		printf("Parameter error!\n");
		exit(0);
	}
	res = rename( argv[1], argv[2]);
	if (res == 0)
	{
		printf("success!\n");
	}
	else
	{
		printf("error!\n");
	}
	return 0;
}
