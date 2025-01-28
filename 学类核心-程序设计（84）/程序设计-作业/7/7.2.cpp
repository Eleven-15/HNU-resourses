#include<iostream>
using namespace std;

int min(int x,int y) {return (x<y) ? x : y; }
int max(int x,int y) {return (x>y) ? x : y; }
int main()
{
   int x1,y1,x2,y2;
   cin>>x1>>y1>>x2>>y2;
   int n;
   cin>>n;
   int x,y,ans=0;
   for (int i=1;i<=n;i++)
   {
   	cin>>x>>y;
   	ans+=(x>=min(x1,x2) && x<=max(x1,x2) && y>=min(y1,y2) && y<=max(y1,y2)) ? 1 : 0;
	} 
	cout<<ans;


    return 0;
}

