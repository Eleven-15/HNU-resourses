#include<stdio.h>
#include<cmath>
using namespace std;
int main()
{
   long long int x,m,maxm;
   scanf("%lld %lld",&x,&m);
   x=abs(x);
   maxm=2*m-1;
   int n;
   n=x/maxm;
   if (x%maxm==0) printf("%d",n);
   else if ((x%maxm)%2==0) printf("%d",n+2);
   else printf("%d",n+1);
  return 0;
}

