#include<bits/stdc++.h>
using namespace std;
int judge(int a);
int judge(int a)
{
	int count=1,sum=0;
	for (int i=1;i<=a;i++)
	{
		if (a%i==0) sum+=i;
	}
	return (sum-a);
}

int main()
{
   int s;
   cin>>s;
   for (int i=s;1;i++)
   {
   	if (i==judge(judge(i)) && judge(i)>s)
   	{
   		cout<<i<<" "<<judge(i);
   		break;
	   }
   }





  return 0;
}

