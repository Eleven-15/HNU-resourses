#include<iostream>
using  namespace  std;
struct  Person{
        char  name[20];
        unsigned  long  id;
        float  salary;
};
Person  pr1;
int  main(){
    cin>>pr1.name>>pr1.id>>pr1.salary;    
	cout<<pr1.name<<" "<<pr1.id<<" "<<pr1.salary;
}
