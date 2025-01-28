#include "Date.h"
#include<iostream>
using namespace std;
		void Date::get()
		{
			cin>>day>>month>>year;
		}
		void Date::show(int day,int month,int year)
		{
			cout<<day<<"/"<<month<<"/"<<year<<endl;
		}
		void Date::error()
		{
	        cout<<"error date!";
		}
		void Date::start()
		{
			get();
			if (judge(day,month,year)==0) error();
			else 
			{
				show(day,month,year);
				change(day,month,year);
				show(day,month,year);
			}
			
		}
		bool Date::judge(int day,int month,int year)
		{
			if (year<0) return 0;
            switch (month)
            {
            	case 1: return (day>=1 && day<=31) ? 1 : 0;
            	case 3: return (day>=1 && day<=31) ? 1 : 0;
            	case 4: return (day>=1 && day<=30) ? 1 : 0;
            	case 5: return (day>=1 && day<=31) ? 1 : 0;
            	case 6: return (day>=1 && day<=30) ? 1 : 0;
				case 7: return (day>=1 && day<=31) ? 1 : 0;
            	case 8: return (day>=1 && day<=31) ? 1 : 0;
            	case 9: return (day>=1 && day<=30) ? 1 : 0;
				case 10: return (day>=1 && day<=31) ? 1 : 0;
            	case 11: return (day>=1 && day<=30) ? 1 : 0;
            	case 12: return (day>=1 && day<=31) ? 1 : 0;
            	case 2:
            		{
            			if (runnian(year)==1) return (day>=1 && day<=29) ? 1 : 0;
            			else return (day>=1 && day<=28) ? 1 : 0;
					}
            	default: return 0;
			}
		}
		bool Date::runnian(int year)
		{
			return (((year%100!=0) && (year%4==0)) || (year%400==0)) ? 1 : 0;
		}
		void Date::change(int &day,int &month,int &year)
		{
			if (judge(day+1,month,year)==1)
			{
				day++;
				return;
			}
			else if (judge(1,month+1,year)==1)
			{
				day=1,month++;
				return;
			}
			else if (judge(1,1,year+1)==1)
			{
				day=1,month=1,year++;
			}
		}
