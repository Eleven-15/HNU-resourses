#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#define N 100
#define MAX 1000000
/*
4
6
0 0 6 0 5 3
0 0 4 5 5 0
6 4 0 0 2 0
0 5 0 0 1 0
5 5 2 1 0 4
3 0 0 0 4 0

6
9
0 0 6 0 5 3
0 0 4 5 5 0
6 4 0 0 2 0
0 5 0 0 1 0
5 5 2 1 0 4
3 0 0 0 4 0
1 0 0 0 0 1 1 0 0
0 1 1 0 0 0 0 0 1
1 1 0 0 0 0 0 1 0
0 0 1 1 0 0 0 0 0
0 0 0 1 1 0 1 1 1
0 0 0 0 1 1 0 0 0
*/
struct stree
{
	int pointa,pointb,weight;
};
int inputadjaceedge(int A[][N],int B[][N],int *n,int *m)
{
	int i=0,j=0;
    printf("点数：");scanf("%d",n);fflush(stdin);
    printf("边数：");scanf("%d",m);fflush(stdin);
    printf("n=%d m=%d\n",*n,*m);
    printf("\n输入邻接矩阵的值：");
    for(i=0;i<*n;++i)
        for(j=0;j<*n;++j)
            scanf("%d",&A[i][j]);
    fflush(stdin);
    printf("\n输入关联矩阵的值：");
    for(i=0;i<*n;++i)
        for(j=0;j<*m;++j)
            scanf("%d",&B[i][j]);
    return 1;
}
//int inputadjace(int a[][N],int *n)
//{
//    int i=0,j=0;
//    printf("点数：");scanf("%d",n);fflush(stdin);
//    printf("\n输入邻接矩阵的值：");
//    for(i=0;i<*n;++i)
//        for(j=0;j<*n;++j)
//            scanf("%d",&a[i][j]);
//    fflush(stdin);
//    return 1;
//}
//
//int inputedge(int b[][N],int n,int *m)
//{
//    int i=0,j=0;
//    printf("边数：");scanf("%d",m);fflush(stdin);
//    printf("\n输入关联矩阵的值：");
//    for(i=0;i<n;++i)
//        for(j=0;j<*m;++j)
//            scanf("%d",&b[i][j]);
//    return 1;
//}
int print(int t[][N],int n,int m,char msg[])
{
    int i=0,j=0;
    printf("\n%s: \n",msg);
    for(i=0;i<n;++i)
    {
        for(j=0;j<m;++j)
            printf("%4d",t[i][j]);
        printf("\n");
    }
    return 1;
}
int getedge(int a[][N],int n,stree t[])
{
    int i=0,j=0,nstree=0;
    for(i=0;i<n;++i)
        for(j=i;j<n;++j)
            if(a[i][j]>0)
            {
                t[nstree].pointa=i;
                t[nstree].pointb=j;
                t[nstree].weight=a[i][j];
                nstree++;
            }
    return nstree;
}

void printtree(stree t[],int nt)
{
    int i=0;
    for(i=0;i<nt;++i)
        printf("%d--%d(%d)",t[i].pointa,t[i].pointb,t[i].weight);
}

void sortedge(stree t[],int nt)
{
    stree t0;
    int i=0,j=0;
    for(i=0;i<nt-1;++i)
        for(j=0;j<nt-1-i;++j)
            if(t[j].weight>t[j+1].weight)
            {
            	t0=t[j];
            	t[j]=t[j+1];
            	t[j+1]=t0;
			}
}

int kruskal(struct stree t0[],int nt0,int n,struct stree t[])
{
    int i=0,j=0,k=0,nt=0,b[N][N],m=0,mtmp=0,ncount=0;
    t[nt]=t0[0];
    nt++;
    for(i=1;i<nt0;++i)
    {
        for(j=0;j<n;++j)
            for(k=0;k<nt0;++k)
                b[j][k]=0;
        for(j=0;j<nt;++j)
        {
            b[t[j].pointa][j]=1;
            b[t[j].pointb][j]=1;
        }
        b[t[i].pointa][j]=1;
        b[t[i].pointb][j]=1;

        printf("加入新边后的关联矩阵\n");
        for(j=0;j<n;++j)
        {
            for(k=0;k<=nt;++k)
                printf("%4d",b[j][k]);
            printf("\n");
        }

        for(k=0;k<=nt;++k)
        {
            for(j=k;j<n;++j)
                if(b[j][k]!=0)
                {
                    if(j>k)
                    {
				
                        for(m=0;m<=nt;++m)
                        {
                        	mtmp=b[j][m]; b[j][m]=b[k][m];b[k][m]=mtmp;
						}
                           // swap(b[j][m],b[k][m]);
						break;
                    }
                }
            for(j=k+1;j<n;++j)
                if(b[j][k]==1)
                    for(m=k;m<=nt;++m)
                        b[j][m]=b[j][m]-b[k][m]*b[j][k]/b[k][k];
        }
        printf("关联矩阵处理以后：\n");
        for(j=0;j<n;++j)
        {
            for(k=0;k<=nt;++k)
                printf("%4d",b[j][k]);
            printf("\n");
        }
        ncount=0;
        for(k=0;k<=nt;++k)
            if(b[k][k]!=0)
                ncount++;
        if(ncount==nt+1)
        {
            t[nt]=t0[i];
            nt++;
            if(nt==n-1)
                break;
        }
    }
    return nt;
}

int prim(stree t0[],int nt0,int n,stree t[])
{
    int i=0,j=0,k=0,nt=0,b[N][N],m=0,mtmp=0,ncount=0;
    int u[N],mdis=0,idis=0,jtree=0,ntree=0;

    u[nt]=0;
    printf("u[%d]=%d\n",nt,u[nt]);
    nt++;
    while(nt<n)
    {
        mdis=999999;
        idis=-1;
        for(i=0;i<nt;++i)
        {
            k=u[i];
            for(j=0;j<nt0;++j)
            {
                if(t0[j].pointa==k)
                    if(mdis>t0[j].weight)
                    {
                        mdis=t0[j].weight;
                        idis=t0[j].pointb;
                        jtree=j;
                    }
                else if(t0[j].pointb==k)
                    if(mdis>t0[j].weight)
                    {
                        mdis=t0[j].weight;
                        idis=t0[j].pointa;
                        jtree=j;
                    }
            }
        }
        u[nt]=idis;
        t[ntree]=t0[jtree];
        t0[jtree].weight=999999;
        printf("nt=%d u[%d]=%d ntree=%d jtree=%d\n",nt,nt,u[nt],ntree,jtree);
        ntree++;
        nt++;
    }
    return ntree;
}
int arcs[100][100];//邻接矩阵
int D[100];//保存最短路径长度
int p[100][100];//路径
int final[100];//若final[i] = 1则说明 顶点vi已在集合S中
int top = 0;//顶点个数
int v0 = 0;//源点
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
    for(int i=0;i<top;i++) printf("D[%d] = %d\n",i,D[i]);

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


int main()
{
	stree st0[N],st1[N];
	int A[N][N],B[N][N],D[N],color[N];
	int i=0,j=0,n=0,m=0;
	int nchoice,nt0=0,nt=0;
	while(1)
	{
		printf("\n===========================\n");
        printf("1.输入邻接矩阵及关联矩阵\n");
		printf("2.用kruskal求最小生成树\n3.用prim求最小生成树\n");
		printf("4.用Dij求最短路\n");
        printf("您的选择(输入0结束)：\n");
        scanf("%d",&nchoice);
        fflush(stdin);
        if(nchoice==0) break;
        switch(nchoice)
        {
        	case 1:
                {
                    inputadjaceedge(A,B,&n,&m);
                    print(A,n,n,"邻接矩阵");
                    break;
                }
        	case 2:
                {
                    nt0=getedge(A,n,st0);
                    printtree(st0,nt0);
                    sortedge(st0,nt0);
                    printtree(st0,nt0);
                    nt=kruskal(st0,nt0,n,st1);
                    printtree(st1,nt);
                    break;
                }
            case 3:
                {
                    nt0=getedge(A,n,st0);
                    printtree(st0,nt0);
                    sortedge(st0,nt0);
                    printtree(st0,nt0);
                    nt=prim(st0,nt0,n,st1);
                    printtree(st1,nt);
                    break;
                }
            case 4:{
            	printf("请输入点数：\n");
            	scanf("%d",&top);
            	printf("请输入源点\n");
            	scanf("%d",&v0);
            	printf("请输入邻接矩阵:\n");
            	for(int i=0;i<top;i++)
            	   for(int j=0;j<top;j++)
            	       scanf("%d",&arcs[i][j]);
            	translate();
                ShortestPath_DIJ();
                
				break;
			} 
		}
	}
	
	return 0; 
 } 


