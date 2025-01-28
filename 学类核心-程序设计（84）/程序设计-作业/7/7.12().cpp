#include<iostream>
using namespace std;
int pow(int x,int y)
{
	int ans=1;
	for (int i=1;i<=y;i++)
	{
		ans*=x;
	}
	return ans;
}

void yuefen(int &n,int &m)
{
	  for(int i=2;i<=n;i++) 
      if(n%i==0 && m%i==0)
      {
         n/=i;
         m/=i;
         i--;       
      }
}
int main()
{
   int n,a,b,c;
   int 	sa=0,sb=0,sc=0;
   cin>>n;
   for (int i=1;i<=n;i++)
   {
   	 string str;
   	 cin>>str;
	a=0,b=0,c=0;
	sa=0,sb=0,sc=0;
   	 for (int j=0;j<=str.length()-1;j++)
   	 {
   	 	if ( str[j]=='.' ) 
   	 	{
   	 		for (int t=0;t<j;t++)
   	 		{
   	 			a*=10;
   	 			a+=(str[t]-'0');
   	 			sa++;
				}
			for (int k=j+1;k<=str.length()-1;k++)
			{ 
				if (str[k]=='(')
				{
					for (int m=k+1;m<=str.length()-1;m++)
					{
						if (str[m]==')') break;
						else 
						{
							c*=10;
   	 			            c+=(str[m]-'0');
   	 			            sc++;
						}
					}
					break;
				}
				else 
				{
					b*=10;
   	 			    b+=(str[k]-'0');
   	 			    sb++;
				}
			}
			break;
		}	
		}
		//cout<<a<<" "<<b<<" "<<c<<endl;
		//cout<<sa<<" "<<sb<<" "<<sc<<endl;
		if (c==0)
		{
			int temp=pow(10,sb);
			yuefen(b,temp);
			cout<<b<<"/"<<temp;
		}
		else 
		{
			int temp=pow(10,sc)-1;
			yuefen(c,temp);
			temp*=pow(10,sb);//temp为c部分的分母 ,c为分子
			int fenzi,fenmu;
			fenzi=b,fenmu=pow(10,sb);//通分前 
		    int zi,mu;
			mu=temp*fenmu; 
			zi=fenzi*temp+fenmu*c;
			yuefen(zi,mu);
			cout<<zi<<"/"<<mu;
		}
   }





  return 0;
}

