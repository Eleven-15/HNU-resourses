#include<bits/stdc++.h>
using namespace std;

bool judge(int i,int m)
{
	return i%m==0 ? 1 : 0;
}

void ans()
{
  int a,b,count=0;
  cout<<"from"<<endl;
  cin>>a;
  cout<<"to"<<endl;
  cin>>b;
  for (int i=a;i<=b;i++)
  {
  	if (judge(i,3) || judge(i,5) || judge(i,7) || judge(i,11)) 
  	{
//  	cout<<i<<endl;
  		count++;
	  }
   } 
   cout<<count;
}

void number()
{
	int a,b,m,count=0;
	a=100; b=1000;
	cout<<"³ıÊı"<<endl;
	cin>>m;
	for (int i=a;i<=b;i++)
	{
		if (i%m==0) count++;
	}
	cout<<count<<endl;
}

int main()
{
  int n=1;
  switch(n)
  {
  	case 0:
  		{
  			ans();
		  }
	case 1:
		{
			while(1)
			{
				number();
			}
		}
  }

  return 0;
}

