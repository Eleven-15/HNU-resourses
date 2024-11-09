#include<bits/stdc++.h>
using namespace std;

int ans[105];
int mapm[105][105];

void Insert(int arv[], int &len, int index, int key){
    if(index>len)
        index=len;
    len++;
    for(int i=len-1; i>=0; i--){
        if(i!=index && i)
            arv[i]=arv[i-1];
        else{
            arv[i]=key;
            return;
        }
    }
}

void Hamilton(int n){
    int ansi = 1;
    ans[ansi++] = 1;
    for(int i=2; i<=n; i++){//第一种情况,直接把当前点添加到序列末尾
        if(mapm[i][ans[ansi-1]]==1)
            ans[ansi++]=i;
        else{
            int flag=0;
            //当前序列从后往前找到第一个满足条件的点j,使得存在<Vj,Vi>且<Vi,Vj+1>.
            for(int j=ansi-2; j>0; j--){
                if(mapm[i][ans[j]]==1){//找到后把该点插入到序列的第j+1个点前.
                    flag=1;
                    Insert(ans,ansi,j+1,i);
                    break;
                }
            }
            if(!flag)//否则说明所有点都邻接自点i,则把该点直接插入到序列首端.
                Insert(ans,ansi,1,i);
        }
    }
}

int main(){
    int n,m;
    scanf("%d", &n);
    m=n*(n-1)/2;
    for(int i=0;i<m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        if(u<v)
            mapm[v][u]=1;
    }
    Hamilton(n);
    for(int i=1;i<=n;i++)
        printf(i==1? "%d":" %d",ans[i]);
    printf("\n");
    return 0;
}
