#include<iostream>
using namespace std;
int main()
{
 int n,i,j,t=0;
 cin>>n;
 int a[n+1][3];
 for(i=1;i<=n;i++)
 {
  cin>>a[i][1]>>a[i][2];
 }
 t=a[1][1];
 for(i=2;i<=n;i++)
 {
   for(j=a[i][1];;j=j+a[i][2])
   {
    if(j>t)
    {
     t=j;
     break;
    }
   }
 }
 cout<<t;
 return 0;
}
