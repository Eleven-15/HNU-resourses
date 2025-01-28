#include  <iostream>
#include  <cstring>
using  namespace  std;
class  X
{
        int  elem;
        char  name[40];
public:
        X(int);
        X(const  X&);
        ~X();
};
X  f(X);
X::X(int  e){
        elem  =  e;
        strcpy(name,  "X");
        cout  <<  "Constructing  new  X"<<  elem  <<  endl;
}
X::X(const  X&  a){
	    elem = a.elem;
        cout  <<  "Constructing  copy  of  "  <<  a.name  <<  elem    <<  endl;
        strcpy(name  ,  "copy  of  ");
        strcat(name,  a.name);
}
X::~X(){
        cout  <<  "Destructing  "<<  name  <<  elem  <<  endl 
}
X  f(X  a){
        cout  <<  "In  function  f()"  <<  endl; 
        return X(a);
}

int  main()
{
X  a(1);
X  b=f(X(2));
a=f(a);
        return  0;
} 
