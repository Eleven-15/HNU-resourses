#include<bits/stdc++.h>
using namespace std;

int main()
{
   int x[3][4];
   char y[4]={'0','A','B','C'};
   int t;
   char ty;
   for (int i=1;i<=3;i++)
   {
   	for (int j=1;j<=3;j++)
   	{
   		cin>>x[i][j];
	   }
   }
for (int i=1;i<=3;i++)
   {
      for (int j=3;j>i;j--)
      {
      	if (x[j-1][1]>x[j][1]) 
      	{
      		for (int k=1;k<=3;k++)
      		{
      			t=x[j-1][k];
      			x[j-1][k]=x[j][k];
      			x[j][k]=t;
      			ty=y[j-1];
      			y[j-1]=y[j];
      			y[j]=ty;
			  }
		  }
		  else if (x[j-1][1]==x[j][1]) 
		  {
		  	       if (x[j-1][2]<x[j][2]) 
      	         {
      	         	for (int k=1;k<=3;k++)
      	         	{
      	    		t=x[j-1][k];
      		     	x[j-1][k]=x[j][k];
      	   	    	x[j][k]=t;
      			    ty=y[j-1];
      		    	y[j-1]=y[j];
      		    	y[j]=ty;
			        }
		          }
		          else if (x[j-1][2]==x[j][2]) 
		          {
		          	             if (x[j-1][3]<x[j][3]) 
      	         {
      	         	for (int k=1;k<=3;k++)
      	         	{
      	    		t=x[j-1][k];
      		     	x[j-1][k]=x[j][k];
      	   	    	x[j][k]=t;
      			    ty=y[j-1];
      		    	y[j-1]=y[j];
      		    	y[j]=ty;
			        }
		          }
				  }
		  }
	  }
   }
   for (int i=1;i<=3;i++)
   {
   	cout<<y[i];
   }



  return 0;
}

