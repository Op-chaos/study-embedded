#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc,char *argv[])
{
	DIR* dir;
	struct dirent* p;
	char* path;
	
	if(argc==1)
		path = "./";
	else
		path = argv[1];

	dir=opendir(path);
	p=readdir(dir);
	while(p!=NULL)
	{
		printf("%s\n",p->d_name);
		p=readdir(dir);
	}
	closedir(dir);
	return 0;
}
