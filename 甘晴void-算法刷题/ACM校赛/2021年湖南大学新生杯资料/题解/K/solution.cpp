#include<bits/stdc++.h>
using namespace std;
const int M=2e6+9;
int n,x,y;
int a[M],b[M],f[M],s1[M],s2[M];
bool vis[M];
int main(){
//	char pt[50];
//	for(int i=30;i<=37;i++){
//		sprintf(pt,"%d.in",i);
//		freopen(pt,"r",stdin);
//		sprintf(pt,"%d.out",i);
//		freopen(pt,"w",stdout);
		scanf("%d",&n);
		for(int i=0;i<n;++i)scanf("%d",&a[i]),b[a[i]]=i,vis[i]=0;
		
		for(int i=0;i<n;++i){
			vis[a[i]]=1;
			s1[i+1]=(a[i]+n-a[i?i-1:n-1])%n;
			s2[i+1]=(b[i]+n-b[i?i-1:n-1])%n;
			s1[n+i+1]=s1[i+1];
			s2[n+i+1]=s2[i+1];
		}
		for(int i=0;i<n;++i)assert(vis[i]==1);
		for(int i=1,j=0;i<=n*2;f[++i]=++j)while(j&&s1[i]!=s1[j])j=f[j];
		x=n*2+1-f[n*2+1];
		for(int i=1,j=0;i<=n*2;f[++i]=++j)while(j&&s2[i]!=s2[j])j=f[j];
		y=n*2+1-f[n*2+1];
		bool bol=0;
		if(x==y){
			for(int i=1,j=1;i<=n*2;++i,++j){
				while(j&&s1[i]!=s2[j])j=f[j];
				if(j==x){bol=1;break;}
			}
		}
		printf("%lld\n",1ll*(x+(bol?0:y))*n);
//	}
	return 0;
}
