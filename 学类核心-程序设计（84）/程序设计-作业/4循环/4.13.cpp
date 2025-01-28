#include<stdio.h>
#include<cmath>

using namespace std;
int main()
{
  int a,b,n;
  scanf("%d %d %d",&a,&b,&n);
  if (a/b!=0) 
  {
  printf("%d.",a/b);
  a=a%b;
  }
  else   printf("0."); 
  for (int i=1;i<=n;i++)
  {
      a*=10;
      printf("%d",a/b);
      a=a%b;
  	
  }

  return 0;
}
  
