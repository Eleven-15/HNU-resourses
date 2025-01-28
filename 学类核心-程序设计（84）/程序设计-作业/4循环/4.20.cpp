#include<iostream>
using namespace std;
int main()
{
    int x[20];
    bool flag=0;
    char c;
    int count=0;
    for (int i=1;i<=11;i++)
    {
    	x[i]=0;
	}
    while (cin.get(c))
    {
    	if (c=='-') flag=1;//¸ºÊı
		else if (c>='0' && c<='9')
		{
			count++;
			x[count]=c-'0'; 
			//cout<<x[count];
		} 
		if (count!=0 && (c>'9' || c<'0')) break;
	}
   
    long long int test=0;
    for (int i=count;i>=1;i--)
    {
    	test+=x[i];
    	test*=10;
	}
	test/=10;
	//cout<<test<<endl;
	if (test>=2147483647 ) 
	{
		cout<<"0";
		return 0;
	}
	//cout<<test<<endl; 
	if (flag==1) cout<<"-";
	bool t=0;
  for (int i=count;i>=1;i--)
    {
    	if (t==0 && x[i]!=0) t=1;
		if (t==1) cout<<x[i];
	}  
  return 0;
}

