#include<iostream>
using namespace std;
void excute();
bool judge(int x,int y,int*map,int n,int m);

bool judge(int x,int y,int*map,int n,int m)
{
	int * newmap=new int [n*m];
	for (int i=0;i<=n-1;i++)
	{
		for (int j=1;j<=m-1;j++)
		{
			*(newmap+i*m+j)=*(map+i*m+j);
			if (x==i || y==j) *(newmap+i*m+j)=0;
		}
	}
	for (int i=0;i<=n-1;i++)
	{
		for (int j=1;j<=m-1;j++)
		{
			if (*(newmap+i*m+j)==1) return 0;
		}
	}
	return 1;
}

void excute()
{
	int n,m,x,y;
	cin>>n>>m;
	char temp;
	int * map=new int [n*m];
		for (int i=0;i<=n-1;i++)
		{
			for (int j=0;j<=m-1;j++)
			{
				cin>>temp;
				if (temp=='.') *(map+i*m+j)=0;//empty
				else if (temp=='*') 
				{
				   *(map+i*m+j)=1;
				   x=i,y=j;
				}//wall
			}
		}
		for (int i=1;i<=m;i++)
		{
			if (judge(x,i,map,n,m)==1)
			{
				cout<<"YES"<<endl;
				return;
			}
		}//先操作行 
			for (int i=1;i<=n;i++)
		{
			if (judge(i,y,map,n,m)==1)
			{
				cout<<"YES"<<endl;
				return;
			}
		}//先操作行 
		cout<<"NO"<<endl;
}

int main()
{
	int t;
	cin>>t;
	for (int i=1;i<=t;i++)
	{
		excute();
	} 
  return 0;
}

