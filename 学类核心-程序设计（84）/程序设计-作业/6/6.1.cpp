#include<iostream>
using namespace std;

int count(long long int number,int x);
int count(long long int number,int x)
{
	int ans=0;
	for(;;)
	{
		if ((number%10)==x) ans++;
		number/=10;
		if (number==0) return ans;
	}
}
int main()
{
     long long int number;
     int x;
     cin>>number>>x;
     cout<<count(number,x);
  return 0;
}

