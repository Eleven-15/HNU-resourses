#include  <iostream>
#include  <iomanip>
using  namespace  std;
struct  Student{
        string  name;    //  ѧ������
        float  mid_score;    //    ���гɼ�
        float  end_score;    //  ��ĩ�ɼ�
        float  avg_score;    //  ��������ĩ��ƽ���ɼ�
};
int  main(){
        int  n;
        cin  >>  n;      
		Student ss[n];						    //  ���峤��Ϊn�Ľṹ������
        for  (int  i  =  0;  i  <  n;  i++)  {
                cin  >>  ss[i].name;
                cin  >>	 ss[i].mid_score;
                cin  >>  ss[i].end_score;
                ss[i].avg_score=(float)((ss[i].mid_score+ss[i].end_score)/2);
        }
        for  (int  i  =  0;  i  <  n;  i++)  {
                cout  <<  ss[i].name  <<  "  "  <<  fixed  <<  setprecision(2)  <<  ss[i].avg_score  <<  endl;
        }
}
