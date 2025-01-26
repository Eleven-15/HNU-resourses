#include<iostream>

#define maxn 5003
#define inf 998244353

using namespace std;

bool now;
int n,a[maxn],dp[2][maxn];

signed main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	dp[0][0]=dp[1][0]=0;
	for(int i=1;i<n;i++) dp[0][i]=dp[1][i]=-inf;
	for(int i=0;i<n;i++){
		now=!now;
		for(int j=0;j<n;j++) dp[now][j]=dp[!now][j];
		
		for(int j=0;j<n;j++){
			dp[now][j]=max(dp[now][j],dp[!now][(j-a[i]+n)%n]+1);
		}
	}
	
//	for(int i=0;i<n;i++){
//		cout<<dp[now][i]<<' ';
//	}
//	cout<<endl;
	
	for(int t=1;t<=n;t++){
		int ans=0;
		for(int i=0;i<n;i++){
			if(t*i%n==0) ans=max(ans,dp[now][i]);
		}
		cout<<ans<<' ';
	}
	cout<<endl;
	return EOF+1;
}