#include <iostream>
using namespace std;
struct Player
{
	string name;
	int a[7];
	int sum;
};
int main()
{
	int n;
	cin>>n;
	Player mount[n];
	for(int i=0;i<n;i++)
	{
		cin>>mount[i].name;
		int max=60;
		int min=100;
		for(int j=0;j<7;j++)
		{
			mount[i].sum=0;
			cin>>mount[i].a[j];
			if(mount[i].a[j]>max)
				max=mount[i].a[j];
			if(mount[i].a[j]<min)
				min=mount[i].a[j];
		}
		for(int j=0;j<7;j++)
		{
			mount[i].sum+=mount[i].a[j];
		}
		mount[i].sum=mount[i].sum-max-min;
	}
	for(int i=1;i<n;i++){
		for(int j=0;j<n-i;j++){
			if(mount[j].sum<mount[j+1].sum){
				Player temp;
				temp=mount[j];
				mount[j]=mount[j+1];
				mount[j+1]=temp;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		cout<<mount[i].name<<" "<<mount[i].sum<<endl;
	}
	return 0;
}

