#include<iostream>
using namespace std;
bool flag=0;

int MakeNumber(){int number=35; return number;}

void GuessNumber(int n)
{
	int temp;
	cin>>temp;
	if (temp==n) 
	{
		cout<<"Right!"<<endl;
		flag=1;
	}
	else if (temp>n) cout<<"Wrong! Too high!"<<endl;
	else if (temp<n) cout<<"Wrong! Too low!"<<endl;
}

int main()
{
   for (int i=1;i<=5;i++)
   {
   	GuessNumber(MakeNumber());
   	if (flag==1) break;
   	
   }





  return 0;
}

