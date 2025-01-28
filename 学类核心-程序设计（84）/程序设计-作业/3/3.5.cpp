#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,big,small,number,other,sum;
	char c[1000];
   cin>>n;
   sum=0;
   big=0;small=0;other=0;number=0;
   for (int i=1;i<=n;i++)
   {
   	cin>>c[i];
   	if ('A'<=c[i] && c[i]<='Z') big++;
   	else if ('a'<=c[i] && c[i]<='z') small++;
	else if ('0'<=c[i] && c[i]<='9') 
	{
		number++;   
		sum+=(c[i]-'0');
	}
   	else other++;	
   }
   cout<<big<<" "<<small<<" "<<number<<" "<<other<<endl;
   if (sum!=0) cout<<sum;




  return 0;
}

