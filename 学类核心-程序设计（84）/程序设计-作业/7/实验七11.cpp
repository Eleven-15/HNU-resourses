#include<iostream>
#include<string> 
using namespace std;
bool yuanyin(char x)
{
	if(x=='a'||x=='e'||x=='i'||x=='o'||x=='u')
		 return true;
	else return false;
}
int main()
{
	string s;cin>>s; 
	int book=1;
	int l=s.length();
	for(int i=0;i<l-1;i++)
	{
		if(yuanyin(s[i])||s[i]=='n')
			continue;
		if(!yuanyin(s[i+1]))
		{
			book=0;
			break;
		}
	}
	if(s[l-1]!='n'&&!yuanyin(s[l-1])) 
		book=0;
	if(book==1) cout<<"YES";
	else cout<<"NO";
	return 0; 
}
