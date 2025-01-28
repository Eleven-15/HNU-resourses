#include  <string>
#include  <iostream>
using  namespace  std;
class  Pet
{
public:
        std::string  color;
        int  weight;
        int  age;
public:
		virtual void speak()=0; 
};
    
class  Cat  :public  Pet
{
	public:
	Cat(){}; 
	virtual void speak()
	{
		cout<<"Cat: miao miao miao..."<<endl;
	}
};
    
class  Dog  :public  Pet
{
	public:
	Dog(){}; 
	virtual void speak()
	{
		cout<<"Dog: wang wang wang..."<<endl;
	}
};
    
int  main(int  argc,  char**  args)
{
//        Pet  *pet;
//        Cat  cat;
//      Dog  dog;
//      pet=&cat;
//      pet->speak();
//      pet=&dog;
//      pet->speak();
		Cat cat;
		Pet &pet=cat;
		pet.speak();
}
