#ifndef DATE_H
#define DATE_H

class Date
{
	public:
       void get();
       void show(int day,int month,int year);
       void start();
       void error();
       bool judge(int day,int month,int year);
       bool runnian(int year);
       void change(int &day,int &month,int &year);
	protected:
		int day,month,year;
};

#endif
