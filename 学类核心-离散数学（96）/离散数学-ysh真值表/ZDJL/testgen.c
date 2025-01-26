#include <stdio.h>
#include <stdlib.h>
int used[100][100];
int RND(){
	return ((((int)rand())<<15)|rand());
}
int main(){
int t=10,n,m,i,j,a,b,d;
freopen("zdjl.in","w",stdout);
srand((int)time(NULL));

while(t--){
	n=10*(10-t);
	b=n*(n-1)/2;
	m=RND()%b;
	for(i=0;i<n;++i)for(j=0;j<n;++j)used[i][j]=0;
	printf("%d %d\n",n,m);
	for(i=0;i<m;++i){
        do {a=RND()%n;b=RND()%n;d=RND()%101;}
          while(a==b||used[a][b]);
        used[a][b]=1;
        printf("%d %d %d\n",a+1,b+1,d);
}}
return 0;}
