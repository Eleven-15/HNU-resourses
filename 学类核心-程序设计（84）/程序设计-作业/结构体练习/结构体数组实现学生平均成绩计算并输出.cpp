#include  <iostream>
#include  <iomanip>
using  namespace  std;
struct  Student{
        string  name;    //  学生姓名
        float  mid_score;    //    期中成绩
        float  end_score;    //  期末成绩
        float  avg_score;    //  期中与期末的平均成绩
};
int  main(){
        int  n;
        cin  >>  n;      
		Student ss[n];						    //  定义长度为n的结构体数组
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
