#include<iostream>
using namespace std;
int main()
{
	char a,b;
    cin.get(a);
    cin.get(b);
    bool flag=0;
    for (int i=1;i<=10;i++)
    {
    	char n;
    	cin.get(n);
    	if (n==a || n==b) flag=1;
	}
    if (flag==0) cout<<"NO";
    else cout<<"YES";



  return 0;
}

