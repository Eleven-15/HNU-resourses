#include<iostream>
#include<cstring>

using  namespace  std;

class  Employee
{
public:
    void display()
{
		cout<<"name:"<<n<<endl;
		cout<<"address:"<<add<<endl;
		cout<<"city:"<<city<<endl;
		cout<<"state:"<<sta<<endl;
		cout<<"postcode:"<<post<<endl;
}
Employee(string n1,string n2)
{
	n=n2+n1;
}
private:
string n,add="Lunan",city="Changsha",sta="Hunan",post="430000";

};
int    main()
{
string m,n;
	cin>>m>>n;
	Employee p(m,n);
	p.display();

return  0;
}
