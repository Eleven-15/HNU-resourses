#include <iostream>
using namespace std;
struct Value{
	int K;
	int I;
	int E;
};
int main()
{
	int n;
	cin>>n;
	Value p[n];
	for(int i=0;i<n;i++)
	{
		cin>>p[i].K;
	}
	for(int i=0;i<n;i++)
	{
		cin>>p[i].I;
	}
	for(int i=0;i<n;i++)
	{
		cin>>p[i].E;
	}
	int sum=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(p[i].K<p[j].K&&p[i].I<p[j].I&&p[i].E<p[j].E){
				sum++;
				break;
			}
		}
	}
	cout<<sum;
	return 0;
}

