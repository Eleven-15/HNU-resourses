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
int arcs[100][100];//�ڽӾ���
int D[100];//�������·������
int p[100][100];//·��
int final[100];//��final[i] = 1��˵�� ����vi���ڼ���S��
int top = 0;//�������
int v0 = 4;//Դ��
int v,w;
void ShortestPath_DIJ()
{
     for (v = 0; v < top; v++) //ѭ�� ��ʼ��
     {
          final[v] = 0; D[v] = arcs[v0][v];
          for (w = 0; w < top; w++) p[v][w] = 0;//���·��
          if (D[v] < MAX) {p[v][v0] = 1; p[v][v] = 1;}
     }
     D[v0] = 0; final[v0]=1; //��ʼ�� v0�������ڼ���S
     //��ʼ��ѭ�� ÿ�����v0��ĳ������v�����·�� ����v������S��
     for (int i = 1; i < top; i++)
     {
          int min = MAX;
          for (w = 0; w < top; w++)
          {
               //����Ϊ�ĺ��Ĺ���--ѡ��
               if (!final[w]) //���w������V-S��
               {
                    //�����������ѡ���ĵ� Ӧ����ѡ����ǰV-S����S�й�����
                    //��Ȩֵ��С�Ķ��� ��������Ϊ ��ǰ��V0����ĵ�
                    if (D[w] < min) {v = w; min = D[w];}
               }
          }
          final[v] = 1; //ѡ���õ����뵽�ϼ�S��
          for (w = 0; w < top; w++)//���µ�ǰ���·���;���
          {
               /*�ڴ�ѭ���� vΪ��ǰ��ѡ�뼯��S�еĵ�
               ���Ե�VΪ�м�� ���� d0v+dvw �Ƿ�С�� D[w] ���С�� �����
               ����ӽ��� 3 ����Ҫ���� D[5] �Ƿ�Ҫ���� �� �ж� d(v0-v3) + d(v3-v5) �ĺ��Ƿ�С��D[5]
               */
               if (!final[w] && (min+arcs[v][w]<D[w]))
               {
                    D[w] = min + arcs[v][w];
                   // p[w] = p[v];
                    p[w][w] = 1; //p[w] = p[v] +��[w]
               }
          }
     }
}
void translate()//Ȩ����ת��Ϊ·�� 0-���� 
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
