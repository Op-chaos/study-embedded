int t=14,s=100;
int main()
{
	int arr[]={1,2,4,6,8};
	int i;
	int s=5;
	int *p;
	p=(int*)malloc(s*sizeof(int));
	for(i=0;i<5;i++)
	{
		arr[i]++;
		p[i]=10*i;
	}
	free(p);
	return 0;
}	
