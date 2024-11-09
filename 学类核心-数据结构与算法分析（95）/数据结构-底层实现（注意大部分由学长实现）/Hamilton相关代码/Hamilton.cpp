#include<bits/stdc++.h>
using namespace std;

void Hamilton(int ans[maxN + 7], bool map[maxN + 7][maxN + 7], int n){
    Init();
    bool visit[maxN + 7] = {false};
    for(i = 1; i <= n; i++) if(map[s][i]) break;
    t = i;//取任意邻接与s的点为t
    visit[s] = visit[t] = true;
    ans[0] = s;
    ans[1] = t;
    while(true){
        while(true){//从t向外扩展
            for(i = 1; i <= n; i++){
                if(map[t][i] && !visit[i]){
                    ans[ansi++] = i;
                    visit[i] = true;
                    t = i;
                    break;
                }
            }
            if(i > n) break;
        }
        //将当前得到的序列倒置,s和t互换,从t继续扩展,相当于在原来的序列上从s向外扩展
        Hreverse(ansi, ans, i, w)
        temp = s;
        s = t;
        t = temp;
        while(true){//从新的t继续向外扩展,相当于在原来的序列上从s向外扩展
            for(i = 1; i <= n; i++){
                if(map[t][i] && !visit[i]){
                    ans[ansi++] = i;
                    visit[i] = true;
                    t = i;
                    break;
                }
            }
            if(i > n) break;    
        }
        if(!map[s][t]){//如果s和t不相邻,进行调整
            for(i = 1; i < ansi - 2; i++)//取序列中的一点i,使得ans[i]与t相连,并且ans[i+1]与s相连
                if(map[ans[i]][t] && map[s][ans[i + 1]])break;
            w = ansi - 1;
            i++;
            t = ans[i];
            reverse(ans, i, w);//将从ans[i +１]到ｔ部分的ans[]倒置
        }//此时s和t相连
        if(ansi == n) return;//如果当前序列包含n个元素,算法结束
        for(j = 1; j <= n; j++){//当前序列中元素的个数小于n,寻找点ans[i],使得ans[i]与ans[]外的一个点相连
            if(visit[j]) continue;
            for(i = 1; i < ansi - 2; i++)if(map[ans[i]][j])break;
                if(map[ans[i]][j]) break;
        }
        s = ans[i - 1];
        t = j;//将新找到的点j赋给t
        reverse(ans, 0, i - 1);//将ans[]中s到ans[i-1]的部分倒置
        reverse(ans, i, ansi - 1);//将ans[]中ans[i]到t的部分倒置
        ans[ansi++] = j;//将点j加入到ans[]尾部
        visit[j] = true;
    }


int main()
{

  return 0;
}

