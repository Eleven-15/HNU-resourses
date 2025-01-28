#include<iostream>
using namespace std;
int main()
{
    int n,count=0;
    int m=0,u=0;
    int x[602][602];
	cin>>n; 
    for (int i=1;i<=n;i++)
 {
 	count=0;
 	   for (int j=1;j<=n;j++)
    {
    	cin>>x[i][j];
    	if (x[i][j]==0) count++;
	}
	if (count>2) m=count;
	if (count>0) u++;
 }
 /*for (int i=1;i<=n;i++)
 {
 	for (int j=1;j<=n;j++)
 	{
 		cout<<x[i][j]<<" ";
	 }
 }*/
   cout<<(m-2)*(u-2)<<endl;



  return 0;
}

