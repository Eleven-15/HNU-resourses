//���������롿
//
//3
//A12 3.34
//15
//B1 11.34
//15
//C 4352.45
//60
//�����������
//
//Shelf_ID: A12 3.34          Price: 15
//Shelf_ID: B1 11.34          Price: 15
//Shelf_ID: C 4352.45         Price: 60
//������˵����
//ע�����ǰ�����Ĵ�Сд��ǰ������:��������һ����ǵĿո���ܺſ��ܰ����ո�
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
          cin  >>  n;      //�Ӽ�����������n
          cin.get();    //�������������Ļس�
        Book  library[n];      //������������
          for(int  i=0;i<n;i++)
          {
                  library[i].setInfo();    //�Ӽ���������������ÿ��Ԫ��
        }
          for(int  i=0;i<n;i++)
          {
                  library[i].show();    //�����������
        }
          return  0;
  }
