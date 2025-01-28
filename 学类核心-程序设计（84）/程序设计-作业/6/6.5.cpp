#include<iostream>
using namespace std;
int fun(int num);
int mi(int x,int n);
 
int mi(int x,int n)
{
	int ans=1;
	for (int i=1;i<=n;i++)
	{
		ans*=x;
	}
	return ans;
}
int fun(int num)
{
	int sum=0;
	int numa=num;
	while (num!=0)
	{
		num/=10;
		sum++;
	}
	if (sum==1) return 0;
	sum=mi(10,sum-1);
	//cout<<sum<<endl;
	numa%=sum;
	return numa;
	
}
int main()
{
	int num;
   cin>>num;
   cout<<fun(num);
  return 0;
}

