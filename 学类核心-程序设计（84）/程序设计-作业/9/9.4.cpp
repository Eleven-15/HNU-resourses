#include<iostream>
using namespace std;

struct team
{
	string name;
	int m[100];
	int time[100];
}list[100]={};
int main()
{
	team host,a;
	int n;
    cin>>host.name;
    cin>>a.name;
    cin>>n;
    int flag=0;
    for (int i=1;i<=n;i++)
    {
    	int time,membernum;
    	char name1,type;
    	cin>>time>>name1>>membernum>>type;
    	if (name1=='h')
    	{
    		if (type='r' || (host.m[membernum]==1)) 
    		{
    			host.m[membernum]=2;
    			host.time[membernum]=time;
    			cout<<host.name<<" "<<membernum<<" "<<host.time[membernum]<<endl;
    			flag=1;
			}
			else 
			{
				host.m[membernum]=1;
    			host.time[membernum]=time;
			}
		}
		else if (name1=='a')
    	{
    		if (type='r' || (a.m[membernum]==1)) 
    		{
    			a.m[membernum]=2;
    			a.time[membernum]=time;
    			cout<<a.name<<" "<<membernum<<" "<<a.time[membernum]<<endl;
    			flag=1;
			}
			else 
			{
				a.m[membernum]=1;
    			a.time[membernum]=time;
			}
		}
    	
	}
	if (flag==0) cout<<"No Red Card";


    return 0;
}

