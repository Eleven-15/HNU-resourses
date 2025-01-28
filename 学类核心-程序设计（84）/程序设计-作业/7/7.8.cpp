#include<iostream>
#include<string>
using namespace std;

class m
{
	public:
	m(){
	};
	int start()
	{

		getline(cin,s1);
		getline(cin,s2);
		l1=s1.length()-1; p1=l1;
		l2=s2.length()-1; p2=l2;
		if (s1==""||s2=="") return s1=="" ? l2+1 :l1+1;
		for (;;)
		{
			if (p1>0 && p2>0 &&s1[p1]==s2[p2])
			{
				p1--;
				p2--;
			 }
			 else if (p1>0 && p2>0)
			 {
			 	return p1+p2+2;
			 }
			 else if (p1==0 && p2==0)
			 {
			 	return 0;
			 }
			 else if (p1==0 || p2==0) 
			 {
			 	if (s1[p1]==s2[p2]) return p1==0 ? p2 : p1;
			 	else return p1==0 ? p2+2 : p1+2;
			 }
		}
		
	}
	~m(){
	};
	private:
		string s1,s2;
		int l1,l2,p1,p2;
		
};

int main()
{
  m n;
  cout<<n.start();

  return 0;
}

