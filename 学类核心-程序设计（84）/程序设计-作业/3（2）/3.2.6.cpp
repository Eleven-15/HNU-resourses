#include<bits/stdc++.h>
using namespace std;

bool judge(int i);
bool judge(int i)
{
	if (i==3||1==4||i==5||i==9||i==10||i==11) return 0;
	else return 1;
}

int main()
{
  int y,n;
  double sum;
  cin>>y>>n;
  if (n<=180) sum=n*0.588;
  else if (judge(y)==0)
  {
  	if (n<=350)
  	{
  		sum=180*0.588+(n-180)*0.638;
	  }
	  else sum=180*0.588+(350-180)*0.638+(n-350)*0.888;
  }
  else
  {
  	if (n<=450)
  	{
  		sum=180*0.588+(n-180)*0.638;
	  }
	  else sum=180*0.588+(450-180)*0.638+(n-450)*0.888;
  }

  cout<<sum;



  return 0;
}

