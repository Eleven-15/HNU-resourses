#include<bits/stdc++.h>
using namespace std;
int a[1010][1010],f[1010][1010];
int main(){
	int n,s=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			f[i][j]=max(f[i-1][j-1],f[i-1][j])+a[i][j];
	for(int j=1;j<=n;j++) s=max(s,f[n][j]);
	cout<<s;
	return 0;
} 
