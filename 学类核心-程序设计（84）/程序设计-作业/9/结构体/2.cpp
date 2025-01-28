#include <iostream>
using namespace std;
struct City{
	int *vote;
	int result;
};
int main()
{
	int n,m;
	cin>>n>>m;
	City p[m+1];
	for(int i=1;i<=m;i++){
		p[i].vote=new int[n+1];
		int l=0;
		for(int j=1;j<=n;j++){
			cin>>p[i].vote[j];
			if(p[i].vote[j]>l){
				l=p[i].vote[j];
				p[i].result=j;
			}
		}
	}
	int a[n+1];
	for(int i=1;i<=n;i++)
	{
		a[i]=0;
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(p[i].result==j)
			{
				a[j]++;
			}
		}	
	}
	int max=0;
	int t=0;
	for(int i=1;i<=n;i++){
		if(a[i]>max){
			max=a[i];
			t=i;
		}
	}
	cout<<t;
	return 0;
}

