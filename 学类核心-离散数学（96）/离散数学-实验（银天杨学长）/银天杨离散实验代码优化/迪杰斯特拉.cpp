#include <iostream>
 
using namespace std;
#define MAXNODE 500//最大顶点个数
#define Inf 65535//无穷大
typedef int vertype;
struct VerNode
{
    vertype vertex;//// 顶点信息，可以是字母表示，也可以是数字表示
    //.....;//// 和顶点相关的其它信息，如顶点的度
};
struct Arc
{
    int adj;// 两顶点之间是否存在关系，用1或0表示相邻否；如果是带权图，则为权值类型
    //....;// 和弧（或边）相关的信息，如弧头、弧尾
};
struct MGraph//图的邻接矩阵表示类型
{
    VerNode vex[MAXNODE];//顶点向量
    Arc arcs[MAXNODE][MAXNODE];//邻接矩阵
    int vexnum,arcnum;//图的当前顶点数和弧数
};
int sum=0;//保存所走路径的花费
MGraph CreatMGraph(MGraph g)//创建邻接矩阵
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>g.vex[i].vertex;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            g.arcs[i][j].adj=Inf;//初始化邻接矩阵，各顶点间无路
        }
    }
    int i,j,quan,e=0;
    cin>>i>>j;//输入一条边依附顶点的序号
    cin>>quan;
    while(i||j)//两顶点全为0表示结束
    {
        e++;
        g.arcs[i][j].adj=quan;
        g.arcs[i][i].adj=0;//各顶点到自己的距离为0
        g.arcs[j][j].adj=0;//各顶点到自己的距离为0
        cin>>i>>j;cin>>quan;
    }
    g.vexnum=n;
    g.arcnum=e;
    return g;
}
void ShortestPath(MGraph g,int v)//Dijkstra算法
{
    int dist[MAXNODE],path[MAXNODE];//dist保存从V开始到各顶点的最短路径
                                    //path保存路径，表示i顶点的前驱顶点
    int s[MAXNODE];//s集合
    int mindis,i,j,u;
    for(i=0;i<g.vexnum;i++)
    {
        dist[i]=g.arcs[v][i].adj;//距离初始化
        s[i]=0;//s[]置空
        if(g.arcs[v][i].adj<Inf)//路径初始化
            path[i]=v;//顶点v到i有边时，置顶点i的前驱为v
        else path[i]=-1;//顶点v到i没边时，置顶点i的前驱为-1
    }
    s[v]=1;path[v]=0;//源点编号v放入s中
    for(i=0;i<g.vexnum;i++)//循环直到所有顶点的最短路径都求从
    {
        mindis=Inf;//mindis置最小长度初值
        for(j=0;j<g.vexnum;j++)//选取不在s中且具有最小距离的顶点u
        {
            if(s[j]==0&&dist[j]<mindis)
            {
                u=j;
                mindis=dist[j];
            }
        }
        s[u]=1;//顶点u加入s中
 
        for(j=0;j<g.vexnum;j++)//修改不在s中的顶点的距离
        {
            if(s[j]==0)
            {
                if(g.arcs[u][j].adj<Inf&&dist[u]+g.arcs[u][j].adj<dist[j])//dist[j]=min{dist[j],dist[u]+g.arcs[u][j].adj};
                {
                    dist[j]=dist[u]+g.arcs[u][j].adj;
                    path[j]=u;
                }
            }
        }
    }
//    for(i=0;i<g.vexnum;i++)
//        cout<<dist[i]<<" ";
//    cout<<endl;
}
int main()
{
    MGraph g= CreatMGraph(g);
    vertype v;
    cin>>v;
    //cout<<g.vexnum<<"  "<<g.arcnum<<endl;
    ShortestPath(g,v);
    return 0;
}
