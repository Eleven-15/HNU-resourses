#include<iostream>
#include<cstring> 
using namespace std;
class Employee
{
	public:
		Employee()
		{
			name="Zhangsan";
			address="Lunan";
			city="Changsha";
			state="Hunan";
			postcode="430000";
		}
void display()
{
	cout<<"address:"<<address<<endl;
	cout<<"city:"<<city<<endl;
	cout<<"state:"<<state<<endl;
	cout<<"postcode:"<<postcode<<endl;
}

void start()
{
	getline(cin,name);
	s=&name;
	Name t(s);
	t.display();
	display();
}
		class Name
		{
			public:
			Name(string*t){
				total=*t;
			}
			void display()
			{
				for (int i=0;i<=total.length()-1;i++)
				{
					if (total[i]==' ') temp=i;
				}
				cout<<"name:";
				for (int i=temp+1;i<=total.length()-1;i++)
				{
					cout<<total[i];
				}
				for (int i=0;i<=temp-1;i++)
				{
					cout<<total[i];
				}
				cout<<endl;
			
			}
			private:
			string total; 
			int temp;
		 };
	protected:
		string name,address,city,state,postcode;
		string* s;
	
};
int main()
{
	Employee test;
	test.start();
  return 0;
}

