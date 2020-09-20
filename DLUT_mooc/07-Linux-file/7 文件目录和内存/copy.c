#include <stdio.h>
#include <stdlib.h>
// cope.out oldfile newfile
int main(int argc,char *argv[])
{ 
	char c;
	FILE *fp1, *fp2;
	if(argc<=2)
	{ 
		printf("Parameter missing!\n");
		exit(0);
	}
	if((fp1=fopen(argv[1],"rb"))==NULL)
	{ 
		printf("Can not open the source file!\n");
		exit(0);
	}
	if((fp2=fopen(argv[2],"a+"))==NULL)
	{ 
		printf("Can not establish the output file!\n");
		exit(0);
	}
	fseek(fp1,0L,0);
	fseek(fp2,0L,0);
	while(!feof(fp1))
	{ 
		fread(&c, 1, 1, fp1);
		fwrite(&c, 1, 1, fp2);
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}
