#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
void k(double r,double s){
	if(r*r>=s*s){
		cout<<fixed<<setprecision(5)<<0.5*sin(r*s);
	}
	else cout<<fixed<<setprecision(5)<<sqrt(sin(r)*sin(r)+sin(s)*sin(s));
}
int main(){
double r,s;
cin>>r>>s;
k(r,s);
return 0;
}

