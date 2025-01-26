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
    printf("������");scanf("%d",n);fflush(stdin);
    printf("������");scanf("%d",m);fflush(stdin);
    printf("n=%d m=%d\n",*n,*m);
    printf("\n�����ڽӾ����ֵ��");
    for(i=0;i<*n;++i)
        for(j=0;j<*n;++j)
            scanf("%d",&A[i][j]);
    fflush(stdin);
    printf("\n������������ֵ��");
    for(i=0;i<*n;++i)
        for(j=0;j<*m;++j)
            scanf("%d",&B[i][j]);
    return 1;
}
//int inputadjace(int a[][N],int *n)
//{
//    int i=0,j=0;
//    printf("������");scanf("%d",n);fflush(stdin);
//    printf("\n�����ڽӾ����ֵ��");
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
//    printf("������");scanf("%d",m);fflush(stdin);
//    printf("\n������������ֵ��");
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

        printf("�����±ߺ�Ĺ�������\n");
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
        printf("�����������Ժ�\n");
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
int arcs[100][100];//�ڽӾ���
int D[100];//�������·������
int p[100][100];//·��
int final[100];//��final[i] = 1��˵�� ����vi���ڼ���S��
int top = 0;//�������
int v0 = 0;//Դ��
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
    for(int i=0;i<top;i++) printf("D[%d] = %d\n",i,D[i]);

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


int main()
{
	stree st0[N],st1[N];
	int A[N][N],B[N][N],D[N],color[N];
	int i=0,j=0,n=0,m=0;
	int nchoice,nt0=0,nt=0;
	while(1)
	{
		printf("\n===========================\n");
        printf("1.�����ڽӾ��󼰹�������\n");
		printf("2.��kruskal����С������\n3.��prim����С������\n");
		printf("4.��Dij�����·\n");
        printf("����ѡ��(����0����)��\n");
        scanf("%d",&nchoice);
        fflush(stdin);
        if(nchoice==0) break;
        switch(nchoice)
        {
        	case 1:
                {
                    inputadjaceedge(A,B,&n,&m);
                    print(A,n,n,"�ڽӾ���");
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
            	printf("�����������\n");
            	scanf("%d",&top);
            	printf("������Դ��\n");
            	scanf("%d",&v0);
            	printf("�������ڽӾ���:\n");
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


