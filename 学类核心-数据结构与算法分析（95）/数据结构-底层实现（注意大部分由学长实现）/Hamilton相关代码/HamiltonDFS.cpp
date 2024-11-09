#include <iostream>  
#include <cstring>  
#define N 101
using namespace std;  
int n,m;
int u,v;
int g[N][N];
int vis[N],appear[N];
int ans[N],num[N];
int length;
int x;

void dfs(int last,int i)//last表示上次访问的点 
{  
    vis[i]=1;//标记为已经访问过  
    appear[i]=1;//标记为已在一张图中出现过  
    ans[length++]=i;//记录答案  
    for(int j=1;j<=num[i];j++)  
    {  
        if(g[i][j]==x&&g[i][j]!=last)//回到起点构成哈密顿环  
        {   
            ans[++length]=g[i][j];//存储答案  
            for(int i=1;i<=length-1;i++) //找到了一个环，输出ans
                cout<<ans[i]<<' ';  
            cout<<ans[length]<<endl;
            length--;//长度-1
            break;
        }  
        if(!vis[g[i][j]])//遍历与i相关联的所有未访问的点。  
            dfs(i,g[i][j]); 
    }  
    length--;  
    vis[i]=0;//回溯
}  

int main(){  
    memset(vis,0,sizeof(vis));  
    memset(appear,0,sizeof(appear));  
    cin>>n>>m; //读入点数与边数
    for(int i=1;i<=m;i++){   
        cin>>u>>v; //读入两点
        g[u][++num[v]]=v;//记录u-v的边
        g[v][++num[v]]=u;//记录v-u的边
    }  
    for(x=1;x<=n;x++) //枚举每一个点，将其作为起点来尝试访问
    {  
        if(!appear[x])//如果点x不在之前曾经被访问过的图里  
        {  
            length=0;//记录答案的长度  
            dfs(0,x);  
        }  
    }  
    return 0;  
} 
