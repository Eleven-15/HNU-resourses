#include<iostream>
using namespace std;

class a
{
    public:
      void start()
      {
      	cin>>T;
      	for (int i=1;i<=T;i++)
      	{
      		circle();
		  }
	  }
	  void circle()
	  {
	  	cin>>s;
	  	mid=0,leftsum=0,rightsum=0;
	  	for (unsigned int i=0;i<=s.length();i++)
	  	{
	  		if (s[i]=='^') 
	  		{
	  			mid=i;
	  			break;
			  }
		  }
		for (int i=0;i<mid;i++)
		{
			if (s[i]>='0' && s[i]<='9')
			{
				leftsum+=((mid-i)*(s[i]-'0'));
			}
		}
		for (unsigned int i=mid+1;i<=s.length();i++)
		{
			if (s[i]>='0' && s[i]<='9')
			{
				rightsum+=((i-mid)*(s[i]-'0'));
			}
		}
		if (leftsum>rightsum) cout<<"left"<<endl;
		else if (leftsum<rightsum) cout<<"right"<<endl;
		else cout<<"balance"<<endl;
	  }
	private:
		string s;
		int T;
		int mid,leftsum,rightsum;
};
int main()
{
	a m;
	m.start();
  return 0;
}

