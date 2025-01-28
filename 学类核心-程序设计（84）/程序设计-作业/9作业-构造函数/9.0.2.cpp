//【样例输入】
//
//3
//A12 3.34
//15
//B1 11.34
//15
//C 4352.45
//60
//【样例输出】
//
//Shelf_ID: A12 3.34          Price: 15
//Shelf_ID: B1 11.34          Price: 15
//Shelf_ID: C 4352.45         Price: 60
//【样例说明】
//注意输出前导符的大小写，前导符“:”后面有一个半角的空格。书架号可能包含空格。
#include  <iostream>
#include  <iomanip>
#include  <string>
using  namespace  std;

class  Book{
        public:
                Book();
                void setInfo();
                void show();
        private:
                float  price;
                string  shelf_id;
};
  Book::Book()
  {
          price  =  0;
          shelf_id  =  "";
  }
  void Book::setInfo()
  {
  	  getline(cin,shelf_id);
  	  cin>>price;
  	  cin.get();
  }
  void Book::show()
  {
  	cout<<"Shelf_ID: "<<setiosflags(ios::left)<<setw(18)<<shelf_id<<"Price: "<<price<<endl;
  }
  
  
  int  main()
  {
          int  n;
          cin  >>  n;      //从键盘输入整数n
          cin.get();    //吸收整数输入后的回车
        Book  library[n];      //声明对象数组
          for(int  i=0;i<n;i++)
          {
                  library[i].setInfo();    //从键盘输入对象数组的每个元素
        }
          for(int  i=0;i<n;i++)
          {
                  library[i].show();    //输出对象数组
        }
          return  0;
  }
