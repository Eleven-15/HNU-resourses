#include<bits/stdc++.h>
using namespace std;

  int *m=new int[10];
  int *mark=new int[10];
  int n;
  int a,b;

bool judge(int i,int m)
{
	return i%m==0 ? 1 : 0;
}

void ans()
{
  int count=0;
  for (int i=a;i<=b;i++)
  {
  	bool flag=false;
  	for (int j=0;j<n;j++)
  	{
  		if (judge(i,m[j])==1) flag=true;
	  }
	if (flag==true) count++;
   } 
   cout<<"最终答案为"<<count;
}

int number(int m)//from a to b 除数m
{
	int count=0;
	for (int i=a;i<=b;i++)
	{
		if (i%m==0) count++;
	}
	return count;
}


void choose(int now,int rest,int *mark,int total)
{
	    if (now==n) return;
	    if (rest==0)
	    {
	    	int sum=1,count=0;
	        for (int i=0;i<n;i++)
	        {
	        	if (mark[i]==1) 
	        	{
	        		cout<<"A"<<m[i]; 
	        		count++;
	        		if (count!=total) cout<<"∩";
	        		sum*=m[i];
				}
			}
			cout<<"="<<number(sum)<<endl;
		}
		else
		{
			for (int i=now+1;i<n;i++)
			{
				mark[i]=1;
				choose(i,rest-1,mark,total);
				mark[i]=0;
			}
		}
}

int main()
{
  cout<<"除数个数为"<<endl;
  cin>>n;
  cout<<"输入各个除数"<<endl;
  for (int i=0;i<n;i++)
  {
  	cin>>m[i]; 
  } 
  cout<<"请输入上下边界"<<endl; 
  cin>>a>>b;
//n=4;
//m[0]=3;m[1]=5;m[2]=7;m[3]=11;
//a=100;b=1000;
  for (int i=0;i<n;i++)
  {
  	mark[i]=0;//0为未选中 
  }
  for (int i=1;i<=n;i++)//取i个数 
  {
  	for (int j=0;j<n;j++)//以每个为起点 
  	{
  		mark[j]=1;
  		choose(j,i-1,mark,i); 
  		mark[j]=0;
	  }
	cout<<endl;
  }
  ans();
  system("pause"); 

  return 0;
}

