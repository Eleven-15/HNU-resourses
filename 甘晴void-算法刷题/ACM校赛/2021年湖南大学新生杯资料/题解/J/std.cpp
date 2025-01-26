#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define fi first
#define se second
using namespace std;
const int M=50009;
const int B=160;
int n,m,q,id,num;
vector<pair<int,int>>g[M];
vector<int>s[M];
int b[M];
ll ans[B<<1][M];
ll d[M];
int a[M],tid[M],dep[M],f[M<<1][23],p[M][2];
void dfs(int u,int fa){
	f[tid[u]=++id][0]=u;dep[u]=dep[fa]+1;
	for(auto o:g[u]){
		int v=o.fi,w=o.se;
		if(v!=fa){d[v]=d[u]+w;dfs(v,u);f[++id][0]=u;}
	}
}
int Min(int l,int r){return dep[l]<dep[r]?l:r;}
int lca(int x,int y){
	if(tid[x]>tid[y])swap(x,y);
	int k=log2(tid[y]-tid[x]+1);
	return Min(f[tid[x]][k],f[tid[y]-(1<<k)+1][k]);
}
ll dis(int x,int y){
	int w=lca(x,y);
	return d[x]+d[y]-d[w]-d[w];
}
void sol(int x){
	int y=b[x];
	for(int i=1;i<=m;++i){
		ans[y][i]=1ll<<60;
		if(s[i].size()>s[x].size()||(s[i].size()==s[x].size()&&i>x))continue;
		for(auto o:s[i]){
			ans[y][i]=min(ans[y][i],max({dis(o,p[i][0]),dis(o,p[i][1]),dis(o,p[x][0]),dis(o,p[x][1])}));
		}
	}
}
unordered_map<int,ll>mp[M];
int main(){
//	freopen("20.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%d%d",&n,&m);
	assert(n>=1&&n<=5e4&&m>=1&&m<=n);
	for(int i=1,u,v,w;i<n;++i){
		scanf("%d%d%d",&u,&v,&w);
		assert(u>=1&&u<=n&&v>=1&&v<=n);
		assert(w>=1&&w<=1e5);
		g[u].eb(v,w);
		g[v].eb(u,w);
	}
	dfs(1,0);
	for(int j=1;j<=23;++j){
		for(int i=1;i<=id-(1<<j)+1;++i){
			f[i][j]=Min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		assert(a[i]>=1&&a[i]<=m);
		s[a[i]].eb(i);
		p[a[i]][0]=p[a[i]][1]=i;
	}
	for(int i=1;i<=n;++i){
		if(dis(1,i)>dis(1,p[a[i]][0]))p[a[i]][0]=i;
	}
	for(int i=1;i<=n;++i){
		if(dis(p[a[i]][0],i)>dis(p[a[i]][0],p[a[i]][1]))p[a[i]][1]=i;
	}
//	for(int i=1;i<=m;++i){
//		assert(s[i].size()>0);
//		if(s[i].size()>B){
//			b[i]=++num;
//			sol(i);
//		}
//	}
	scanf("%d",&q);
	//assert(q>=1&&q<=5e4);
	for(int i=1,x,y;i<=q;++i){
		scanf("%d%d",&x,&y);
		assert(x>=1&&x<=n&&y>=1&&y<=n&&x!=y);
		if(s[x].size()<s[y].size()||(s[x].size()==s[y].size()&&x<y))swap(x,y);
		if(mp[x].count(y))printf("%lld\n",mp[x][y]);
		else {
			ll w=1ll<<60;
			for(auto o:s[y]){
				w=min(w,max({dis(o,p[y][0]),dis(o,p[y][1]),dis(o,p[x][0]),dis(o,p[x][1])}));
			}
			mp[x][y]=w;
			printf("%lld\n",w);
		}
	}
	return 0;
}
