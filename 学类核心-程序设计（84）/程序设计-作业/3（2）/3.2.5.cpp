#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int i=1;
    while (n/10!=0)
    {
    	n=n/10;
    	i++;
	}
    cout<<i;


  return 0;
}

