#include<iostream>
using namespace std;

class m
{
	public:
	m(){
	};
	bool judge(char c)
	{
		return (c=='q' || c=='w' || c=='e' || c=='r' || c=='t' || 
		        c=='a' || c=='s' || c=='d' || c=='f' || c=='g' || 
				c=='z' || c=='x' || c=='c' || c=='v' || c=='b' ||
				c=='Q' || c=='W' || c=='E' || c=='R' || c=='T' || 
				c=='A' || c=='S' || c=='D' || c=='F' || c=='G' || 
				c=='Z' || c=='X' || c=='C' || c=='V' || c=='B')? 1:0;
	}
	void start()
	{
		cin>>n;
		string str[n];
		double sum[n];
		ans=0; 
		for (int i=0;i<=n-1;i++) sum[i]=0;
		for (int i=0;i<=n-1;i++)
		{
			cin>>str[i];
			//cout<<str[i]<<endl;
			for (int j=0;j<i;j++)
			{
				if (str[i]==str[j]) 
				{
					sum[i]=sum[j]/2.0;
					//cout<<sum[i]<<"tt"<<endl;
					break;
				}
			}
			if (sum[i]==0)
			{
				sum[i]+=0.2;
				for (int j=1;j<=str[i].length()-1;j++)
				{
					if (judge(str[i][j])==judge(str[i][j-1])) sum[i]+=0.4;
					else sum[i]+=0.2;
				}
				//cout<<sum[i]<<"tt"<<endl;
			}
			ans+=sum[i];
		}
		cout<<ans*10;
	}
	~m(){
	};
	private:
		int n;
		double ans;
		
};
int main()
{
  m n;
  n.start();
  return 0;
}

