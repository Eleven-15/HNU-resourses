#include<iostream>
using namespace std;
int x[602][602];

int judge(int i,int j);
int judge(int i,int j)
{
	if (x[i][j]==3)
	{
		if (x[i+1][j+1]==1 || x[i+1][j-1]==1 || x[i-1][j+1]==1 || x[i-1][j-1]==1) return 1;
	}
	return 0;
}


int main()
{
   int n,temp,sum=0;
   cin>>n;
   for (int i=0;i<=n+1;i++)
     for (int j=0;j<=n+1;j++)
     {
     	x[i][j]=1;//n*n������������չһ�� ��ʼֵΪ1 
	 }
	    for (int i=1;i<=n;i++)
     for (int j=1;j<=n;j++)
     {
     	cin>>temp;
     	if (temp==0) x[i][j]=2;//�����߽磬��ʼֵΪ2 
     	else if (temp==255) x[i][j]=3;//δ����ֵ����ʼֵΪ3 
	 }
	    for (int i=1;i<=n;i++)
     for (int j=1;j<=n;j++)
     {
     	if (judge(i,j)==1) 
     	{
     		x[i][j]=1;//����ֵ����ֵΪ1 
     		sum++;
		 }
	 }
	   for (int i=1;i<=n;i++)
   {
   	  for (int j=1;j<=n;j++)
     cout<<x[i][j]<<" ";
     cout<<endl;
     
   }
	 cout<<endl; 
	 cout<<sum;
	 





  return 0;
}

