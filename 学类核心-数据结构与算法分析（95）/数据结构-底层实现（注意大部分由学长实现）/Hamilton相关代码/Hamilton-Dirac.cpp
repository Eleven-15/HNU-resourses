#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define N 1001
#define E 1e-6
#define LL long long
using namespace std;
bool G[N][N];
bool vis[N];
int ans[N];
void Reverse(int arv[N],int s,int t){//将数组anv从下标s到t的部分的顺序反向
    int temp;
    while(s<t){
        swap(arv[s],arv[t]);
        s++;
        t--;
    }
}
void Hamilton(int n){
    int t;
    int s=1;//初始化取s为1号点
    for(int i=1;i<=n;i++)
        if(G[s][i]){
            t=i;//取任意邻接与s的点为t
            break;
        }
    memset(vis,false,sizeof(vis));
    vis[s]=true;
    vis[t]=true;
    ans[0]=s;
    ans[1]=t;
    int ansi=2;
    while(true){
        //从t向外扩展
        while(true){
            int i;
            for(i=1;i<=n;i++){
                if(G[t][i] && !vis[i]){
                    ans[ansi++]=i;
                    vis[i]=true;
                    t=i;
                    break;
                }
            }
            if(i>n)
                break;
        }
        //将当前得到的序列倒置
        Reverse(ans,0,ansi-1);
        //s和t互换
        swap(s,t);
        while(true){//从t继续扩展,相当于在原来的序列上从s向外扩展
            int i;
            for(i=1;i<=n;i++){
                if(G[t][i] && !vis[i]){
                    ans[ansi++]=i;
                    vis[i]=true;
                    t=i;
                    break;
                }
            }
            if(i>n)
                break;
        }
        //如果s和t不相邻,进行调整
        if(!G[s][t]){
            //取序列中的一点i,使得ans[i]与t相连,并且ans[i+1]与s相连
            int i;
            for(i=1;i<ansi-2;i++)
                if(G[ans[i]][t]&&G[s][ans[i+1]])
                    break;
            i++;
            t=ans[i];
            Reverse(ans,i,ansi-1);//将从ans[i+1]到ｔ部分的ans[]倒置
        }//此时s和t相连 
        //如果当前序列包含n个元素,算法结束
        if(ansi==n)
            return;
        //当前序列中元素的个数小于n,寻找点ans[i],使得ans[i]与ans[]外的一个点相连
        int i,j;
        for(j=1;j<=n;j++){
            if(vis[j])
                continue;
            for(i=1;i<ansi-2;i++)
                if(G[ans[i]][j])
                    break;
            if(G[ans[i]][j])
                break;
        }
        s=ans[i-1];
        t=j;//将新找到的点j赋给t
        Reverse(ans,0,i-1);//将ans[]中s到ans[i-1]的部分倒置
        Reverse(ans,i,ansi-1);//将ans[]中ans[i]到t的部分倒置
        ans[ansi++]=j;//将点j加入到ans[]尾部
        vis[j]=true;
    }
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    n*=2;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(i==j){
                G[i][j]=false;
                G[j][i]=false;
            }
            else{
                G[i][j]=true;
                G[j][i]=true;
            }
        }
    }
    int ansi=0;
    memset(ans, 0, sizeof(ans));
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        G[y][x]=false;
        G[x][y]=false;
    }
    Hamilton(n);
    for(int i=0;i<n;i++)
        printf("%d ", ans[i]);
    printf("\n");
    return 0;
}
