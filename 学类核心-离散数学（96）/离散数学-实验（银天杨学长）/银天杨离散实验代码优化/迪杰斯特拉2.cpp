#include <iostream>
#include <cstdio>
#define MAX 1000000
#define INF  0x7fffffff
/*
6
0 0 6 0 5 3
0 0 4 5 5 0
6 4 0 0 2 0
0 5 0 0 1 0
5 5 2 1 0 4
3 0 0 0 4 0
*/
using namespace std;
int arcs[100][100];//邻接矩阵
int D[100];//保存最短路径长度
int p[100][100];//路径
int final[100];//若final[i] = 1则说明 顶点vi已在集合S中
int top = 0;//顶点个数
int v0 = 4;//源点
int v,w;
void ShortestPath_DIJ()
{
     for (v = 0; v < top; v++) //循环 初始化
     {
          final[v] = 0; D[v] = arcs[v0][v];
          for (w = 0; w < top; w++) p[v][w] = 0;//设空路径
          if (D[v] < MAX) {p[v][v0] = 1; p[v][v] = 1;}
     }
     D[v0] = 0; final[v0]=1; //初始化 v0顶点属于集合S
     //开始主循环 每次求得v0到某个顶点v的最短路径 并加v到集合S中
     for (int i = 1; i < top; i++)
     {
          int min = MAX;
          for (w = 0; w < top; w++)
          {
               //我认为的核心过程--选点
               if (!final[w]) //如果w顶点在V-S中
               {
                    //这个过程最终选出的点 应该是选出当前V-S中与S有关联边
                    //且权值最小的顶点 书上描述为 当前离V0最近的点
                    if (D[w] < min) {v = w; min = D[w];}
               }
          }
          final[v] = 1; //选出该点后加入到合集S中
          for (w = 0; w < top; w++)//更新当前最短路径和距离
          {
               /*在此循环中 v为当前刚选入集合S中的点
               则以点V为中间点 考察 d0v+dvw 是否小于 D[w] 如果小于 则更新
               比如加进点 3 则若要考察 D[5] 是否要更新 就 判断 d(v0-v3) + d(v3-v5) 的和是否小于D[5]
               */
               if (!final[w] && (min+arcs[v][w]<D[w]))
               {
                    D[w] = min + arcs[v][w];
                   // p[w] = p[v];
                    p[w][w] = 1; //p[w] = p[v] +　[w]
               }
          }
     }
}
void translate()//权矩阵转换为路径 0-无穷 
{
	for (int i = 0; i < top; i++)
    {
         for (int j = 0; j < top; j++)
         {
         	if(arcs[i][j]==0) arcs[i][j]=MAX;
         }
    }
}
//int n=0;
//int a[100][100];
//void Dijkstra(int (a[n][n]),int n ,int s)
//{
//	int d[N];
//	bool vis[N]={false};
//	fill(d,d+N,MAX);
//	d[s]=0;
//	for(int i=0;i<n;i++)
//	{
//		int u=-1,min=MAX;
//		for(int j=0;j<n;j++)
//		{
//			if(vis[j]==false&&d[j]<min)
//			{
//				u=j;
//				min=d[j];
//			}
//		}
//		if(u==-1) return ;
//		vis[u]=true;
//		for(int v=0;v<n;v++)
//		{
//			if(vis[v]==false&&a[u][v]!=MAX&&d[u]+a[u][v]<d[v])
//			{
//				d[v]=d[u]=a[u][v];
//			}
//		}
//	}
//	for(int i=0;i<n;i++)
//	{
//		if(i==s) continue;
//		printf("%d",&d[i]);
//	}
// } 

int main()
{
    cin >> top;
    for (int i = 0; i < top; i++)
    {
         for (int j = 0; j < top; j++)
         {
              cin >> arcs[i][j];
         }
    }
//    int s=0;
//    scanf("%d",s);
    translate();
//    Dijkstra(arcs[][],top,s)
    ShortestPath_DIJ();
    for (int i = 0; i < top; i++) printf("D[%d] = %d\n",i,D[i]);
    return 0;
}
