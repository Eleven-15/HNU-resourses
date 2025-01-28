#include "Time.h"
#include<iostream>
using namespace std;
		void Time::get()
		{
			cin>>hour>>minute>>second;
		}
		void Time::show(int hour,int minute,int second)
		{
			cout<<hour<<":"<<minute<<":"<<second;
		}
		void Time::error(int n)
		{
			switch(n)
			{
				case 1:cout<<"hour error!"<<endl;break;
				case 2:cout<<"minute error!"<<endl;break;
				case 3:cout<<"secondes error!"<<endl;break;
			}
		}
		void Time::start()
		{
			get();
			if (hour>=24 || hour<0) {error(1);}
			if (minute>=60 || minute<0) {error(2);}
			if (second>=60 || second<0) {error(3);}
			show(hour,minute,second);
		}
