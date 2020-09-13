#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
void err_quit(char *msg);

int main(int argc, char *argv[])
{
	int fdin;			//�ļ�������
	char *src;			//�ڴ��׵�ַָ��
	struct stat statbuf;		//�ļ�״̬�ṹ
	off_t len;			//����
	/* ���һ���Ƿ����������� */
	if(argc != 2) 
	{
		fprintf(stderr, "usage: mmcat {file}\n");
		exit(EXIT_FAILURE);
	}
	/* �򿪴����ļ� */
	if((fdin = open(argv[1], O_RDONLY)) < 0) 
	{
		err_quit("open");
	}

	/* Ҫ����mmap��������֪�������ļ��Ĵ�С��ͨ������fstat���õ� */
	if((fstat(fdin, &statbuf)) < 0) 
	{
		err_quit("fstat");
	}
	len = statbuf.st_size;

	/* ���ļ�ӳ���ڴ��� */
	if((src = mmap(0, len, PROT_READ, MAP_SHARED, fdin, 0)) == (void *)-1) 
	{ 
		err_quit("mmap");
	}

	/* ���ӳ�䵽�ڴ��е��ļ������� */
	printf("%s", src);

	/* ������ */
	close(fdin);
	munmap(src, len);

	exit(EXIT_SUCCESS);
}

void err_quit(char *msg) 
{
	perror(msg);
	exit(EXIT_FAILURE);
}
