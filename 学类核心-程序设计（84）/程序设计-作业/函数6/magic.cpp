#include<iostream>
using namespace std;
int breakit(long long int n,int *x)
{
	int i;
	for (i=1;n!=0;i++)
	{
		*(x+i)=n%10;
		n/=10;
	}
	return i-1;
}

int main()
{
	int *x=new int;
    long long int n;
    cin>>n;
    int length=breakit(n,x);
    if (length==0) 
    {
    	cout<<"NO";
    	return 0;
	}
    for (int i=length;i>=1;)
    {
    	if (*(x+i)!=1 && *(x+i)!=4)
    	{
    		cout<<"NO";
    		return 0;
		}
    	if (*(x+i)==1)
		{
			if (i-1==0)
			{
				cout<<"YES";
				return 0;
			}
			if (*(x+i-1)==1) 
			{
				i--;
				continue;
			}
			else if (*(x+i-1)==4)
			{
				if (i-2==0)
				{
					cout<<"YES";
					return 0;
				}
				if (*(x+i-2)==4)
				{
					if (i-3==0)
					{
						cout<<"YES";
						return 0;
					 } 
					i-=3;
					continue;
				}
				else if (*(x+i-2)==1)
				{
					i-=2;
					continue;
				}
				else 
				{
					cout<<"NO";
					return 0;
				}
			}
				else 
				{
					cout<<"NO";
					return 0;
				}
		 } 
		 else 
				{
					cout<<"NO";
					return 0;
				}
	}
    cout<<"YES"; 
  return 0;
}

