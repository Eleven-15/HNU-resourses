#include<iostream>
#include"gragh.h"
#include"OLgragh.h"
using namespace std;

//dfs:打印顶点标号和所有出，入边的权之和
void DFS(int v1,OLGragh<char> &G)
{
    if(G.getMark(v1))
        return ;
    G.setMark(v1,1);
    int s1,s2;
    s1=s2=0;
    int p=G.firstOut(v1);
    while(p!=-1)
    {
        s1+=G.weight(v1,p);
        p=G.nextOut(v1);
    }
    p=G.firstIn(v1);
    while(p!=-1)
    {
        s2+=G.weight(p,v1);
        p=G.nextIn(v1);
    }
    cout << G.getVex(v1)<<"的出边权之和(无权图的出度):"<<s1
    <<"  入边权之和(无权图的入度):"<<s2<<endl;
    p=G.firstOut(v1);
    while(p!=-1)
    {
        DFS(p,G);
        p=G.nextOut(v1);
    }
}

bool flag1;      //保存图是否带权
void INIT(OLGragh<char>& G)  //建图
{
    cout<<"此图是否为带权图(是请输入1，不是请输入0):";
    cin >> flag1;
    int n=G.n();
    char a,b;
    cout <<"请输入初始状态时，图中各顶点的标号(以空格分隔)\n";
    for(int i=0;i<n;i++)
    {
        cin >> a;
        G.putVex(i,a);
    }
    cout <<"请输入初始状态时，图中边的数量:";
    cin >> n;
    cout <<"请输入初始状态时，图中边连接的顶点的标号\n"
    <<"每行输入两个字母，以空格分隔\n"
    <<"弧尾在前，弧头在后(带权图后加空格和权值)\n"
    <<"例如:A B (带权:A B 3)为A指向B的边\n";
    for(int i=0;i<n;i++)
    {
        int c=1;
        cin >> a >> b;
        int x=G.locateVex(a);
        int y=G.locateVex(b);
        if(flag1)
            cin >>c;
        G.setEdge(x,y,c);
    }
}

void menu(OLGragh<char>& G)  //菜单
{
    int x,y,c;
    char a,b;
    int flag = 1;
    while(flag)
    {
        cout <<"----------------------------------\n";
        int t;
        cout<<"0.退出程序\n"
            <<"1.插入边\n"
            <<"2.删除边\n"
            <<"3.DFS输出顶点和出、入边的权之和(无权图则为出、入度)\n"
            <<"请输入所需操作的序号:";
        cin >> t;
        switch(t)
        {
        case 0:
            flag=0;
            break;
        case 1:
            cout <<"请输入插入边的端点标号(和权)格式参照建图时边的输入的格式:";
            c=1;
            cin >> a >> b;
            x=G.locateVex(a);
            y=G.locateVex(b);
            if(flag1)
                cin >>c;
            G.setEdge(x,y,c);
            break;
        case 2:
            cout <<"请输入删除边的端点标号:";
            cin >> a >> b;
            x=G.locateVex(a);
            y=G.locateVex(b);
            G.delEdge(x,y);
            break;
        case 3:
            cout <<"dfs输出结果为:\n";
            for(int i=0;i<G.n();i++)  //初始化标记数组
                G.setMark(i,0);
            for(int i=0;i<G.n();i++)  //对非连通图的遍历
            {
                if(!G.getMark(i))
                    DFS(i,G);
            }
            break;
        default:
            cout <<"请输入正确的指令!!";
            break;
        }
        cout <<"----------------------------------\n\n";
    }
}

int main()
{
    int n;
    cout <<"本程序只支持有向图的储存,图的标号类型为字符\n";
    cout <<"请输入本次建立图的顶点数量:";
    cin >> n;
    OLGragh<char> G(n);
    INIT(G);
    menu(G);
    return 0;
}
