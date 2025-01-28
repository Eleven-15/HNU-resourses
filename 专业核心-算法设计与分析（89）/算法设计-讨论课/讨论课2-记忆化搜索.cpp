#include<bits/stdc++.h>
using namespace std;
int n,a[1005][1005],f[1005][1005];
inline int dfs(int x,int y)
{
	if(x==n) return a[x][y];
	if(f[x][y]) return f[x][y];
	return f[x][y]=max(dfs(x+1,y),dfs(x+1,y+1))+a[x][y];
}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	 for(register int j=1;j<=i;j++) scanf("%d",&a[i][j]);
	printf("%d",dfs(1,1));
	return 0;
}
