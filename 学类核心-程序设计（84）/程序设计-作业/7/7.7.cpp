#include<iostream>
using namespace std;

class s
{
	public:
		bool judge(int i,string &s)
		{
			return (s[i]=='W' && s[i+1]=='U' && s[i+2]=='B')? 1:0;
		}
		void start()
		{
			flag=0;
			cin>>s;
			for (unsigned int i=0;i<=s.length();)
			{
				if (judge(i,s)==1)
				{
					i+=3;
					if (flag==1)
					{
						cout<<" ";
						flag=0;
					}
				}
				else 
				{
					cout<<s[i];
					flag=1;
					i++;
				}
			}
		}
	private:
		string s;
		bool flag;
};
int main()
{
	s n;
	n.start();
  return 0;
}

