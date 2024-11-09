//给定一张 n 个点的带权无向图，点从 0～n?1 标号，求起点 0 到终点 n?1 的最短 Hamilton 路径。
//
//Hamilton 路径的定义是从 0 到 n?1 不重不漏地经过每个点恰好一次。
//
//输入格式
//第一行输入整数 n。
//
//接下来 n 行每行 n 个整数，其中第 i 行第 j 个整数表示点 i 到 j 的距离（记为 a[i,j]）。
//
//对于任意的 x,y,z，数据保证 a[x,x]=0，a[x,y]=a[y,x] 并且 a[x,y]+a[y,z]≥a[x,z]。
//
//输出格式
//输出一个整数，表示最短 Hamilton 路径的长度。
//
//数据范围
//1≤n≤20
//0≤a[i,j]≤107
//输入样例：
//5
//0 2 4 5 1
//2 0 6 5 3
//4 6 0 8 3
//5 5 8 0 5
//1 3 3 5 0
//输出样例：
//18

#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=20,M=1<<N;

int f[M][N],w[N][N];//w表示的是无权图

int main()
{
    int n;
    cin>>n;

    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      cin>>w[i][j];

    memset(f,0x3f,sizeof(f));//因为要求最小值，所以初始化为无穷大
    f[1][0]=0;//因为零是起点,所以f[1][0]=0;

    for(int i=0;i<1<<n;i++)//i表示所有的情况
     for(int j=0;j<n;j++)//j表示走到哪一个点
      if(i>>j&1)
       for(int k=0;k<n;k++)//k表示走到j这个点之前,以k为终点的最短距离
        if(i>>k&1)
         f[i][j]=min(f[i][j],f[i-(1<<j)][k]+w[k][j]);//更新最短距离

    cout<<f[(1<<n)-1][n-1]<<endl;//表示所有点都走过了,且终点是n-1的最短距离
    //位运算的优先级低于'+'-'所以有必要的情况下要打括号
    return 0;
}
