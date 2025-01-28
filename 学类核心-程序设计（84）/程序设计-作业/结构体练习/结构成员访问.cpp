#include<iostream>
using  namespace  std;
struct  Weather{
		double temp;        
		double	wind;
};
int  main(){
    Weather  today;
    cin>>today.temp>>today.wind;
	cout<<"Temp="<<today.temp<<endl<<"Wind="<<today.wind;
	return 0;
}
