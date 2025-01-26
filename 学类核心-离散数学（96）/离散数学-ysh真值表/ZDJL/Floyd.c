#include <stdio.h>
#include <windows.h>
#define SIZE 100
#define INF  2000000000
#define FINITE(x) x<INF
#define ENDL j==n-1?10:32
#define FOR(x) for(x=0;x<n;++x)
//#define DEBUG
#define TIME
int dis[SIZE][SIZE];

void Floyd(int n){
     int i,j,k,t;
     FOR(k)
       FOR(i)
          FOR(j)
             if(FINITE(dis[i][k])&&FINITE(dis[k][j])&&(t=dis[i][k]+dis[k][j])<dis[i][j])
                dis[i][j]=t;
                }
   
int main(int argc,char **argv){
    
#ifdef TIME
     DWORD dwTimeStart;
     DWORD dwTimeEnd;     
#endif 
    int i,j,a,b,d,n,m;
    freopen(argv[1],"r",stdin);
    freopen(argv[2],"w",stdout);
    while(1){
#ifdef DEBUG
    printf("请输入图的节点数与边数\n");
#endif
    if(scanf("%d%d",&n,&m)!=2)break;
          FOR(i)
             FOR(j)
                 dis[i][j]=(i==j?0:INF);
#ifdef DEBUG
          printf("输入边的信息，起点 终点 距离，每行一边\n"); 
#endif
          for(i=0;i<m;++i){
              scanf("%d%d%d",&a,&b,&d);
              dis[a-1][b-1]=d;}
#ifdef DEBUG
          printf("距离矩阵：\n"); 
          FOR(i)FOR(j)
                if(FINITE(dis[i][j]))
                   printf("%d%c",dis[i][j],ENDL);
                else 
                   printf("INF%c",ENDL);
#endif
#ifdef TIME
           dwTimeStart = GetTickCount();
#endif           
          Floyd(n);
#ifdef TIME
          dwTimeEnd = GetTickCount();
          printf( "Time %ums\n", dwTimeEnd - dwTimeStart );
#endif    
          printf("最小距离矩阵：\n"); 
          FOR(i)FOR(j)
                if(FINITE(dis[i][j]))
                   printf("%5d%c",dis[i][j],ENDL);
                else 
                   printf(" INF %c",ENDL);
}  
          return 0;} 
          
