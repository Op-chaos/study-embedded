#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{ 
	int res;
	if(argc==1)
	{ 
		printf("Parameter missing!\n");
		exit(0);
	}
	res = remove( argv[1] );
	if(res == 0)
	{ 
		printf("deleted!\n");
		exit(0);
	}
	else if(res == -1)
	{ 
		printf("error happend!\n");
		exit(0);
	}
	return 0;
}
