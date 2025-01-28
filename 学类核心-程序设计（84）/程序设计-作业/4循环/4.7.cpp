#include<stdio.h>
using namespace std;

bool perfect(int x);
bool perfect(int x)
{
	int sum=0;
	for (int i=1;i<x;i++)
	{
		if (x%i==0) sum+=i;
	}
	if (sum==x) return 1;
	else return 0;
}
int main()
{
   int n; 
   scanf("%d",&n);
   if (perfect(n)==1) printf("true");
   else printf("false");
   
  return 0;
}

