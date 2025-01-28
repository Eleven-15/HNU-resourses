#include<iostream>
using namespace std;
int exponent(int num,int k);
int exponent(int num,int k)
{
	int sum=0;
	while (num>=k && num%k==0)
	{
		num/=k;
		sum++;
		//cout<<num<<" "<<k<<" "<<sum<<endl;
	}
	if (num==1) return sum;
	else return 0;
}
int main()
{
    int num,k;
    cin>>num>>k;
    cout<<exponent(num,k);
    





  return 0;
}

