#include<bits/stdc++.h>
using namespace std;
int main()
{
  int n;
  cin>>n;
  for (int i=1;i<=n;i++)
  {
     for (int j=n-i+1;j>=1;j--)
     {
     	cout<<" ";
	 }
	 cout<<"*";
	 if (i==1) cout<<endl;
	 if (i>1)
	 {
	 	for (int k=1;k<=2*i-3;k++) cout<<" ";
	 	cout<<"*"<<endl;
	 }

  }
   cout<<"*";
   for (int i=1;i<=2*n-1;i++) cout<<" ";
   cout<<"*"<<endl;
   for (int i=1;i<=n;i++)
  {
     for (int j=1;j<=i;j++)
     {
     	cout<<" ";
	 }
	 cout<<"*";
	 if (i<n)
	 {
	 	for (int k=1;k<=2*(n-i)-1;k++) cout<<" ";
	 	cout<<"*"<<endl;
	 }

  }
   



  return 0;
}
/*
   *
  * *
 *   *
*     *
 *   *
  * *
   *
*/
