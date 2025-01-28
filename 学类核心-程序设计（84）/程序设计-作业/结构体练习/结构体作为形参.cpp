#include  <iostream>
using  namespace  std;
struct  Person{
        char  name[20];
        unsigned  long  id;
        float  salary;
};
//  编写以结构体值作为形参的函数，按指定格式打印结构体数组
void  print(Person a)
{
	cout<<a.name<<" "<<a.id<<" "<<a.salary<<endl;
}
Person  allone[6]={
        {"jone",12345,339.0},
        {"david",13916,449.0},
        {"marit",27519,311.0},
        {"jasen",42876,623.0},
        {"peter",23987,400.0},
        {"yoke",12335,511.0}
        };
int  main()
{
//  循环调用print函数打印allone数组
	for(int i=0;i<6;i++)
		print(allone[i]);
}

