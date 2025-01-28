#include<iostream>
using namespace std;

struct person
{
	int k,l,e;
	int survive;
};
int main()
{
	
   int n;
   cin>>n;
/*   int x[3+1][n+1];
   for (int i=1;i<=3;i++)
   for (int j=1;j<=n;j++)
   {
   	cin>>x[i][j];
   }
    for (int i=1;i<=3;i++)
   {
   	for (int j=1;j<=n;j++)
   {
   	cout<<x[i][j]<<" "; 
   }
   cout<<endl;
   }*/
   int ans=0;
   struct person *p= new person[n+1];
   for (int i=1;i<=n;i++) p[i].survive=1;
   for (int i=1;i<=n;i++) cin>>p[i].k;
   for (int i=1;i<=n;i++) cin>>p[i].l;
   for (int i=1;i<=n;i++) cin>>p[i].e;
   //for (int i=1;i<=n;i++) cout<<p[i].k<<p[i].l<<p[i].e<<endl;
   for (int i=1;i<=n;i++) 
   {
   	   for (int j=i+1;j<=n  && p[i].survive==1;j++)
		  {
		  	  if (p[i].e<p[j].e && p[i].k<p[j].k && p[i].l<p[j].l && p[j].survive==1)
		  	  {
		  	  	p[i].survive=0;
		  	    ans++;
		    	}
		      else if (p[i].e>p[j].e && p[i].k>p[j].k && p[i].l>p[j].l && p[j].survive==1)
		      {
		      	p[j].survive=0;
		      	ans++;
			  }
		   } 
   }
   cout<<ans;
    return 0;
}

