#include <iostream>
using namespace std;
struct movie{
	int visual;
	int sound;
	int happy;
	int sat;
};
int main()
{
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int m;
	cin>>m;
	movie p[m];
	for(int i=0;i<m;i++){
		cin>>p[i].sound;
	}
	for(int i=0;i<m;i++){
		cin>>p[i].visual;
	}
	int flag=0;
	for(int i=0;i<m;i++){
		p[i].happy=0;
		p[i].sat=0;
		for(int j=1;j<=n;j++){
			if(p[i].sound==a[j]){
				p[i].happy++;
				flag++;
			}
			if(p[i].visual==a[j]){
				p[i].sat++;
				flag++;
			}
		}
	}
	if(flag==0)
		cout<<"unsatisfied";
	else{
		int maxh=0,maxs=0;
		for(int i=0;i<m;i++)
		{
			if(p[i].happy>maxh)
				maxh=p[i].happy;
		}
		for(int i=0;i<m;i++)
		{
			if(p[i].happy==maxh){
				for(int j=0;j<m;j++){
					if(p[j].happy==maxh){
						if(p[j].sat>maxs)
							maxs=p[j].sat;
						}
				}
				for(int i=0;i<m;i++)
				if(p[i].sat==maxs) cout<<i+1<<" ";
				return 0; 
			}
		}
	}
	return 0;
}

