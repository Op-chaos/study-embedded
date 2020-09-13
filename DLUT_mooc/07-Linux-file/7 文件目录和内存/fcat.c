#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{ 
	int temp;
	FILE *fpr;
	if(argc==1)
	{ 
		printf("Parameter missing!\n");
		exit(0);
	}
	if((fpr=fopen(argv[1],"r"))==NULL)
	{ 
		printf("Can not open the source file!\n");
		exit(0);
	}
	fseek(fpr,0L,0);
	while(!feof(fpr))
	{ 
		temp=fgetc(fpr);
		putchar(temp);
	}
	fclose(fpr);
	return 0;
}
