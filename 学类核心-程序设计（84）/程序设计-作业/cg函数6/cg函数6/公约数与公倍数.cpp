#include<iostream>
using namespace std;
int ys(int a,int b){
	for(int i=a ;i>1;i--){
		if(a%i==0&&b%i==0){
			return i;
			break;
		}
	}
	return 1;
}
int bs(int a,int b){
	for(int i=1;1;i++){
		if(a*i%b==0){
			return a*i;
			break;
		}
	}
}
int main(){
int a,b;
cin>>a>>b;
cout<<ys(a,b)<<" "<<bs(a,b);
return 0;
}

