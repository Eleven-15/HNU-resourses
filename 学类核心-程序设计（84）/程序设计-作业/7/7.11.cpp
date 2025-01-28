#include<iostream>
using namespace std;

class m
{
	public:
	int judge(char c)
	{
		if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' || c=='n') return 1; //ิชา๔
		else return 0; 
	}
    void start()
	{	
      getline(cin,str);
      for (int i=0;i<=str.length()-1;)
      {
      	if (judge(str[i])==0)
      	{
      		if (i+2<=str.length()-1) 
      		{
      			if (judge(str[i+1])==1)
                  {
                  	i+=2;
      			    continue;
				  }
				  else
				{
					cout<<"NO";
					return;
				}
			  }
			else if (i==str.length()-1-1)
			{
				if (judge(str[i+1])==0)
				{
					cout<<"NO";
					return;
				}
				else 
				{
				    cout<<"YES";
					return;	
				}
			}
			else if (i==str.length()-1)
				{
					cout<<"NO";
					return;
				}
		  }
		  else 
		  {
		  	i++;
		  	continue;
		  }
	  }
	  cout<<"YES";
	  return;
	}	
	private:
		string str;
};
int main()
{
  m n;
  n.start();
  return 0;
}

