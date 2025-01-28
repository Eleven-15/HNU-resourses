#include<bits/stdc++.h>
using namespace std;

int test(int n,int u,int d);
int test(int n,int u,int d)
{
	int now=0,count=0;
	if (u>n) return 1;
	else{
		do
		{
			now+=u; count++;
			if (now>=n) break;
			now-=d; count++;
		 } while(1);
	}
	return count;
}
int main()
{
	int n,u,d;
	int x[1000]={0};
	int num=1;
   do
   {
   	cin>>n>>u>>d;
   	if (n==0  && u==0 && d==0) break;
   	x[num]=test(n,u,d);
   	num++;
   }while (1);
   for (int i=1;i<=num-1;i++)
   {
   	cout<<x[i]<<endl;
   }

  return 0;
}
