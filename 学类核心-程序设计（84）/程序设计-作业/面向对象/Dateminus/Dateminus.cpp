#include "Dateminus.h"
#include<iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
bool isLeap(int year);

void Dateminus::get()
{
	cin>>x>>y>>z;
}

bool isLeap(int year) {
	return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
}

int Dateminus::operator-(Dateminus &c)
{
    int monthDays[13][2] = {
		{0,0},{31,31},{28,29},{31,31},{30,30},{31,31},
		{30,30},{31,31},{31,31},{30,30},{31,31},{30,30},
		{31,31}
	};
	int time1, year1, month1, days1;
	int time2, year2, month2, days2;
	int numbers =0;
	time1=10000*(this->x)+100*(this->y)+(this->z);
	time2=10000*c.x+100*c.y+c.z;
	if (time1>time2){
		int temp = time1;
		time1 = time2;
		time2 = temp;
	}
	//������ڣ���Ϊ�꣬�£���
	year1 = time1 / 10000; month1 = time1 / 100 % 100; days1 = time1 % 100;
	year2 = time2 / 10000; month2 = time2 / 100 % 100; days2 = time2 % 100;
	//��һ������ �ۼӵ� �ڶ�������
	while (year1 < year2 || month1 < month2 || days1 < days2) {
		days1++;// �ڵ�һ�����ڻ�����  ��һ��
		//��һ�����Ӧ���£������ҲҪ��һ���ı仯
		if (days1 == monthDays[month1][isLeap(year1)]+1) {//��ǰ�ų�����ǰ������������·ݼ�1���ű�����µ�1��
			month1++;
			days1 = 1;
		}
		if (month1 == 13) {//�·ݳ���12���� ����ݼ�1,�·ݱ�������1��
			year1++;
			month1 = 1;
		}
		numbers++;
	}
	return numbers;


}
/* 
struct Date{
 int y;//year
 int m;//month
 int d;//day in month
};
int daysOfDate(Date d);
int daysOfMonth(Date d);
int isLeap(int y);

int Dateminus::operator-(Dateminus &c)
{
	Date d1,d2;
	d1.y=this->x; d1.m=this->y; d1.d=this->z;
	d2.y=c.x;     d2.m=c.y;     d2.d=c.z;
	int days1=daysOfDate(d1);
	int days2=daysOfDate(d2);
	int day=abs(days1-days2);
	return day;
}

int isLeap(int y)
{
 return y%4==0 && y%100==0 || y%400==0;
}

int daysOfMonth(Date d)
{
 int days[12]={31,0,31,30,31,30,31,31,30,31,30,31};
 if(d.m!=2)
  return days[d.m-1];
 else
  return 28+isLeap(d.y);
}

int daysOfDate(Date d)
{
 int days=0;
 for(int y=1;y<=d.y;y++)
  days+=365+isLeap(y);
 for(int m=1;m<d.m;m++)
  days+=daysOfMonth(d);
 days+=d.d;
 return days;
}
*/


