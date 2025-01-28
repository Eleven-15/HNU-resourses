#include<iostream>
using namespace std;
int main()
{
	int n,g,r,q,now,temp;
	cin>>n>>g>>r;
	int l[n+2];
	for (int i=1;i<=n+1;i++)
	{
		cin>>l[i];
	}
    cin>>q;
    int x[q+1],ans[q+1];
    for (int i=1;i<=q;i++)
    {
    	cin>>x[i];
	}
    
    for (int i=1;i<=q;i++)
    {
    	now=x[i];
    	for (int j=1;j<=n;j++)
    	{
    		now+=l[j];
    		temp=now%(g+r);
    		if (temp>=g && temp<(g+r))
    		{
    			now+=(g+r-temp);
			}
		}
		now+=l[n+1];
    	ans[i]=now;
	}
    for (int i=1;i<=q;i++)
    {
    	cout<<ans[i]<<" ";
	}



  return 0;
}

