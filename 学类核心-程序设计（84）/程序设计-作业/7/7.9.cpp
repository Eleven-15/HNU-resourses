#include<iostream>
using namespace std;

class m
{
    public:
	m(){
	};
		int max(int a,int b)
		{
			return a>b ? a:b;
		}
		int min(int a,int b)
		{
			return a<b ? a:b;
		}
		bool circle()
		{
			string str;
		    cin>>str;
			int *map=new int[10000];
			for (unsigned int i=0;i<=str.length()-1;i++)
			{
				map[i]=0;
			}
			for (unsigned int i=0;i<=str.length()-1;i++)
			{
				if (str[i]>='0' && str[i]<='9')
				{
					int m=str[i]-'0';
					//cout<<m<<endl;
					for (int j=max(0,i-m);j<=min(str.length()-1,i+m);j++)
					{
						map[j]++;
					}
				}
			}
			//for (unsigned int i=0;i<=str.length()-1;i++) cout<<map[i]<<" ";
			for (unsigned int i=0;i<=str.length()-1;i++)
			{
				if (map[i]>1) return 0;
			}
			return 1;
		}
		void start()
		{
			cin>>T;
			for (int i=1;i<=T;i++)
			{
				cout<<((circle()==1)? "safe" : "unsafe");
				cout<<endl;
			}
		}
	~m(){
	};
	private:
		int T;
};
int main()
{
  m n;
  n.start(); 
;  return 0;
}

