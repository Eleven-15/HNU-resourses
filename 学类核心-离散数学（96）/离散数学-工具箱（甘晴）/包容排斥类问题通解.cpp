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
   cout<<"���մ�Ϊ"<<count;
}

int number(int m)//from a to b ����m
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
	        		if (count!=total) cout<<"��";
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
  cout<<"��������Ϊ"<<endl;
  cin>>n;
  cout<<"�����������"<<endl;
  for (int i=0;i<n;i++)
  {
  	cin>>m[i]; 
  } 
  cout<<"���������±߽�"<<endl; 
  cin>>a>>b;
//n=4;
//m[0]=3;m[1]=5;m[2]=7;m[3]=11;
//a=100;b=1000;
  for (int i=0;i<n;i++)
  {
  	mark[i]=0;//0Ϊδѡ�� 
  }
  for (int i=1;i<=n;i++)//ȡi���� 
  {
  	for (int j=0;j<n;j++)//��ÿ��Ϊ��� 
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

