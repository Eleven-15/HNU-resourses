#include<bits/stdc++.h>
using namespace std;
int main()
{
   int n;
   cin>>n;
   bool  bol=1;
   bool bol2=0;
   if (n==1) cout<<"2";
   else
   {
   do
   {
   	n++;
   	int i=1;
   	bol2=0;
   	do
   	{
   		i++;
   		if (n%i==0) 
   		{
   			bol2=1;
			} 
	   }while  (i<=int(sqrt(n)) && bol2==0);
	if (bol2==0) bol=0;
   }while  (bol==1);
   cout<<n;
}



  return 0;
}

