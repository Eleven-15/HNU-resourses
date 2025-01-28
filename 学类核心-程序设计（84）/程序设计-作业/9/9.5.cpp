#include<iostream>
using namespace std;

int main()
{
   long long int n;
   cin>>n;
   long long int *a=new long long int[n+1];
   for (long long int i=1;i<=n;i++)
   {
   	    cin>>a[i];
   }
   long long int m;
   cin>>m;
   long long int *b=new long long int[m+1];
   long long int *c=new long long int[m+1];
   long long int *very=new long long int[m+1];
   long long int *basic=new long long int[m+1];
   for (long long int i=1;i<=m;i++)
   {
   	    cin>>b[i];
   }
   for (long long int i=1;i<=m;i++)
   {
   	    cin>>c[i];
   }
   
   long long int maxm=0,tempnum=0;
   long long int *temp=new long long int[m+1];
   for (long long int i=1;i<=m;i++){basic[i]=0;very[i]=0;}
   for (long long int i=1;i<=m;i++)
   {
   	    for (long long int j=1;j<=n;j++)
   	    {
   	    	if (a[j]==b[i]) very[i]++;
   	    	else if (a[j]==c[i]) basic[i]++;
		   }
		//cout<<" "<<"very:"<<very[i]<<" "<<"basic:"<<basic[i]<<endl;
		if (very[i]>maxm) 
		{
			tempnum=1;
			maxm=very[i];
			temp[1]=i;
		}
		else if (very[i]==maxm)
		{
			tempnum++;
			temp[tempnum]=i;
		}
   }
   //for (long long int i=1;i<=tempnum;i++)
   //{
   //	cout<<temp[i]<<" "<<"very:"<<very[temp[i]]<<" "<<"basic:"<<basic[temp[i]]<<endl;
   //}
   cout<<endl;
   
   long long int maxm2=0,temp2num=0;
   long long int *temp2=new long long int[tempnum+1];
   for (long long int i=1;i<=tempnum;i++)
   {
   	   if (basic[temp[i]]>maxm2)
   	   {    
		    temp2num=1;
   	   	    maxm2=basic[temp[i]];
			temp2[temp2num]=temp[i];
	   }
	   else if (basic[temp[i]]==maxm2)
	   {
	   	   temp2num++;
	   	   temp2[temp2num]=temp[i];
	   }
   }
   if (temp2num==0) cout<<"unsatisfied";
   else
   for (long long int i=1;i<=temp2num;i++)
   {
   	cout<<temp2[i]<<" ";
   }
    return 0;
}

