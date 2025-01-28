#include<stdio.h>
using namespace std;
int main()
{
   long long int a,b,k,t;
   scanf("%lld",&t);
   long long int x[t+1];
   for (int i=1;i<=t;i++)
   {
   	  scanf("%lld %lld %lld",&a,&b,&k);
   	  if (k%2==0) x[i]=(a-b)*k/2;
   	  else x[i]=(a-b)*(k-1)/2+a;
   }
   for (int i=1;i<=t;i++)
   {
   	printf("%lld \n",x[i]);
   }





  return 0;
}

