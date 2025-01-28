#include<bits/stdc++.h>
using namespace std;

int sum=0;
int judge(char c);
int judge(char c)
{
	switch(c)
	{
		case 'y':sum+=2;break;
		case 'g':sum+=3;break;
		case 'c':sum+=4;break;
		case 'b':sum+=5;break;
		case 'p':sum+=6;break;
		case 'B':sum+=7;break;
		default:;
	}
}
int main()
{
   int n,t;
   char c;
   cin>>n;
   for (int i=1;i<=n;i++)
   {
   	cin>>c;
   	if (c=='r')
   	{
   		cin>>t;
   		sum+=t;
	   }
	else judge(c);
   }
   cout<<sum;



  return 0;
}

