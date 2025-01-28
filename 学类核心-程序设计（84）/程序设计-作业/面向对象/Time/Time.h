#ifndef TIME_H
#define TIME_H

class Time
{
	public:
       void get();
       void show(int hour,int minute,int second);
       void start();
       void error(int n);
	protected:
		int hour,minute,second; 
};

#endif
