#include<iostream>
#include<string>
using namespace std;

void func(string &s);
void func(string &s)
{
	for (unsigned int i=0;i<=s.length()-1;i++)
	{
		if ((s[i]>='A' && s[i]<='V') || (s[i]>='a' && s[i]<='v'))
		{
			s[i]+=4;
		}
		else 
		{
			s[i]+=-22;
		}
		
	}
}
int main()
{
    string s;
    int n;
    cin>>n;
    cin>>s;
    func(s);
    cout<<s;
  return 0;
}

