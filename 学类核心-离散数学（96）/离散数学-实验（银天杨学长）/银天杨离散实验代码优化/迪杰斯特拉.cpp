#include <iostream>
 
using namespace std;
#define MAXNODE 500//��󶥵����
#define Inf 65535//�����
typedef int vertype;
struct VerNode
{
    vertype vertex;//// ������Ϣ����������ĸ��ʾ��Ҳ���������ֱ�ʾ
    //.....;//// �Ͷ�����ص�������Ϣ���綥��Ķ�
};
struct Arc
{
    int adj;// ������֮���Ƿ���ڹ�ϵ����1��0��ʾ���ڷ�����Ǵ�Ȩͼ����ΪȨֵ����
    //....;// �ͻ�����ߣ���ص���Ϣ���绡ͷ����β
};
struct MGraph//ͼ���ڽӾ����ʾ����
{
    VerNode vex[MAXNODE];//��������
    Arc arcs[MAXNODE][MAXNODE];//�ڽӾ���
    int vexnum,arcnum;//ͼ�ĵ�ǰ�������ͻ���
};
int sum=0;//��������·���Ļ���
MGraph CreatMGraph(MGraph g)//�����ڽӾ���
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
            g.arcs[i][j].adj=Inf;//��ʼ���ڽӾ��󣬸��������·
        }
    }
    int i,j,quan,e=0;
    cin>>i>>j;//����һ����������������
    cin>>quan;
    while(i||j)//������ȫΪ0��ʾ����
    {
        e++;
        g.arcs[i][j].adj=quan;
        g.arcs[i][i].adj=0;//�����㵽�Լ��ľ���Ϊ0
        g.arcs[j][j].adj=0;//�����㵽�Լ��ľ���Ϊ0
        cin>>i>>j;cin>>quan;
    }
    g.vexnum=n;
    g.arcnum=e;
    return g;
}
void ShortestPath(MGraph g,int v)//Dijkstra�㷨
{
    int dist[MAXNODE],path[MAXNODE];//dist�����V��ʼ������������·��
                                    //path����·������ʾi�����ǰ������
    int s[MAXNODE];//s����
    int mindis,i,j,u;
    for(i=0;i<g.vexnum;i++)
    {
        dist[i]=g.arcs[v][i].adj;//�����ʼ��
        s[i]=0;//s[]�ÿ�
        if(g.arcs[v][i].adj<Inf)//·����ʼ��
            path[i]=v;//����v��i�б�ʱ���ö���i��ǰ��Ϊv
        else path[i]=-1;//����v��iû��ʱ���ö���i��ǰ��Ϊ-1
    }
    s[v]=1;path[v]=0;//Դ����v����s��
    for(i=0;i<g.vexnum;i++)//ѭ��ֱ�����ж�������·�������
    {
        mindis=Inf;//mindis����С���ȳ�ֵ
        for(j=0;j<g.vexnum;j++)//ѡȡ����s���Ҿ�����С����Ķ���u
        {
            if(s[j]==0&&dist[j]<mindis)
            {
                u=j;
                mindis=dist[j];
            }
        }
        s[u]=1;//����u����s��
 
        for(j=0;j<g.vexnum;j++)//�޸Ĳ���s�еĶ���ľ���
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
