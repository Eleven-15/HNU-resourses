//利用函数计算素数个数并求和
 
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;
int prime(int m);
int main(int argc,char const *argv[])
{
	int m,n,i;
	int sum=0,count=0;
	
	while(1) 
	{
		scanf("%d%d",&m,&n);
		if(m>=1&&m<=500&&n>=1&&n<=500&&m<=n)
			break;
	
	}
	
	for(i=m;i<=n;i++)
	{
		if(prime(i))
		{
			count++;
			sum+=i;
		}
	}
	
	cout<<count<<endl;
	cout<<sum<<endl; 
	return 0;
} 
 
int prime(int m)
{
	int i;
	int ret=1;
	
	if(m==1)
		ret=0;
	for(i=2;i<=sqrt(m);i++)
	{
		if(m%i==0)
		{
			ret=0;
			break;
		}
		
	}
	
	return ret;
}
