#include<iostream>
#include<string>
#include  <cstring>
using  namespace  std;
struct  Person{
        char  name[20];
        unsigned  long  id;
        float  salary;
};
int  main(){
        Person  pr1;
        Person *prPtr=new Person;
        cin>>pr1.name;
        strcpy(prPtr->name,pr1.name);
        cin>>prPtr->id;
        cin>>prPtr->salary;
        cout<<prPtr->name<<"  "<<prPtr->id<<"  "<<prPtr->salary<<endl;
}

