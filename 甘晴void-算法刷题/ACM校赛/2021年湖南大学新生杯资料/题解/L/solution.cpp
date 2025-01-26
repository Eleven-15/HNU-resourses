#include<bits/stdc++.h>
using namespace std;
const int maxn=105;
char mp[maxn][maxn];
struct nod {
	int r,c;
};
int dir_r[]={1,0,-1,0};
int dir_c[]={0,1,0,-1};
int n,m;
bool check(int r,int c) {return (r>=1&&r<=n&&c>=1&&c<=m)&&mp[r][c]!='o';}
bool vis[maxn][maxn];
bool bfs(int r,int c) {
	queue<nod>q;
	q.push(nod{r,c});
	while(!q.empty()) {
		nod u=q.front();
		q.pop();
		if(vis[u.r][u.c]) continue;
		if(mp[u.r][u.c]=='X') return 1;
		vis[u.r][u.c]=1;
		for(int i=0;i<4;i++) {
			int tor=dir_r[i]+u.r;
			int toc=dir_c[i]+u.c;
			if(check(tor,toc)&&!vis[tor][toc]) {
				q.push(nod{tor,toc});
			}
		}
	}
	return 0;
}
void sol() {
	cin>>n>>m;
    assert(1<=n&&n<=100&&1<=m&&m<=100);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>mp[i][j];
    int cntp=0,cntx=0;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            if(mp[i][j]=='X') cntx++;
            else if(mp[i][j]=='P') cntp++;
            else assert(mp[i][j]=='.'||mp[i][j]=='o');
        }
    }
    assert(cntp==1&&cntx==1);
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(mp[i][j]=='P') {
				bool ok=bfs(i,j);
				if(ok) cout<<"Playftql";
				else cout<<"Playftcl";
                return;
			}
		}
	}
}
int main() {
	sol();
	return 0;
}