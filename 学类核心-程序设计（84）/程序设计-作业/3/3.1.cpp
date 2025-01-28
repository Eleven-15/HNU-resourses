#include<iostream>
using namespace std;
int main()
{
   int n,a,b,c;
   cin>>n;
   a=0,b=0,c=0;
   if (n%3==0) a++;
   if (n%5==0) b++;
   if (n%7==0) c++;
   if (a==1 && b==1 && c==1) cout<<"It's divisible by 3,5,7";
   if (a==1 && b==0 && c==1) cout<<"It's divisible by 3,7";
   if (a==1 && b==1 && c==0) cout<<"It's divisible by 3,5";
   if (a==1 && b==0 && c==0) cout<<"It's divisible by 3";
   if (a==0 && b==1 && c==1) cout<<"It's divisible by 5,7";
   if (a==0 && b==0 && c==1) cout<<"It's divisible by 7";
   if (a==0 && b==1 && c==0) cout<<"It's divisible by 5";
   if (a==0 && b==0 && c==0) cout<<"null";
   

  return 0;
}

