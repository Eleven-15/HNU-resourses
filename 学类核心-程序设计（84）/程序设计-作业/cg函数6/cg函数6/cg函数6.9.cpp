#include<stdio.h>
int main(void)
{
	int i,j,k=0;
	scanf("%d",&i);
	j=i;
	while(j)
	{
		k=k*10+j%10;
		j/=10;
	}
	if(k==i)
	printf("true",i);
	else
	printf("false",i);
	return 0;
}

