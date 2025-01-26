//在一个n*m的网格中，每个格点都有个权值，q个询问，形式为（x，y，d）表示距离点（x，y）d以内的所有点的权值和是多少（曼哈顿距离）
//n，m<=2000,q<=1e6
#include<bits/stdc++.h>
using namespace std;
int n,m,q,d;
int val[4005][4005];
long long f[4005][4005];
inline int read()
{
	int X=0,Y=1;char C=getchar();
	while (C<'0'||C>'9') {if (C=='-') Y=-1;C=getchar();}
	while (C>='0'&&C<='9') X=X*10+C-'0',C=getchar();
	return X*Y;
}
int main()
{
    memset(val,0,sizeof(val));
    memset(f,0,sizeof(f));
    n=read();m=read();q=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            val[i+j-1][n+j-i]=read();
    for(int i=1;i<=n+m-1;i++)
        for(int j=1;j<=n+m-1;j++)
            f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]+1ll*val[i][j];
    for(int i=1;i<=q;i++)
    {
        int r,c,d;
        r=read();c=read();d=read();
		int lr=max(0,r+c-d-2),lc=max(0,n+c-r-d-1),rr=min(n+m-1,r+c+d-1),rc=min(n+m-1,n+c-r+d);
		printf("%lld\n",f[rr][rc]-f[lr][rc]-f[rr][lc]+f[lr][lc]);
    }
    return 0;
}
