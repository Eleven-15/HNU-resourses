#include<iostream>
using namespace std;

int main()
{
    struct warrior
    {
    	string name;
    	int x[4];
	};
	warrior *m= new warrior[100000];
	int i=1;
    while (cin>>m[i].name && m[i].name != "#")
    {
    	cin>>m[i].x[1]>>m[i].x[2]>>m[i].x[3];
    	m[i].x[0]=i; 
		i++;
	}
	int n=i-1; //cout<<n;
	int std;
	cin>>std;
    for (int i=1;i<=n;i++)
    {
    	for (int j=n;j>i;j--)
    	{
    		if (m[i].x[std]<m[j].x[std]  || (m[i].x[std]==m[j].x[std] && m[i].x[0]>m[j].x[0])) 
    		{
    			warrior tmp;
    			tmp=m[i];
    			m[i]=m[j];
    			m[j]=tmp;
			}
		}
	}
	for (int i=1;i<=n;i++)
	{
		cout<<m[i].name<<" "<<m[i].x[1]<<" "<<m[i].x[2]<<" "<<m[i].x[3]<<endl;
	}

    return 0;
}

