#include<bits/stdc++.h>
using namespace std;
int main()
{
	cout<<"��ģΪn="<<endl; 
	int n;
	cin>>n;
	int m[n+1][n+1];
	cout<<"input matrix"<<endl;
	for (int i=1;i<=n;i++)
  	{
  	    for (int j=1;j<=n;j++)
  		{
  			cin>>m[i][j];
	 	 }
   	} //initialization
   	
   	cout<<endl<<"��Ϊ��"<<endl; 
  	for (int j=1;j<=n;j++)
  	{
  		cout<<"j="<<j<<",����"<<j<<"��"<<endl; 
  		for (int i=1;i<=n;i++)
  		{
  			if (m[i][j]==1)
  			{
  				bool flag=false;
  				for (int k=1;k<=n;k++)
  				{
  					int temp=m[i][k];
  					m[i][k]=m[i][k]+m[j][k];
  					if (m[i][k]>1) m[i][k]=1;
  					if (temp!=m[i][k]) flag=true;
				  }
			    if (flag==true)
			    {
			    	cout<<"M("<<i<<","<<j<<")="<<endl;
					for (int i2=1;i2<=n;i2++)
  					{
  	  					  for (int j2=1;j2<=n;j2++)
  							{
  								cout<<m[i2][j2]<<" ";
	 						 }
	 						 cout<<endl;
   					}
   					cout<<endl;
				}
				else cout<<"M("<<i<<","<<j<<")="<<endl<<"����"<<endl<<endl;
			  }
	 	 }
	 	 cout<<endl;
   	} 
	system("pause") ;


  return 0;
}

