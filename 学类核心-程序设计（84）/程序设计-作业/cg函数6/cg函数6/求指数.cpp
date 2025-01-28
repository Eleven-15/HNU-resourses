#include<iostream>
#include<cmath>
using namespace std;
int exponent(int num,int k){
	int s=0;
	for(int i=1;1;i++){
		s=pow(k,i);
		if(s==num){
			return i;
			break;
		}
		if(s>num){
			return 0;
			break;
		}
	}
	
}
int main(){
int a,b;
cin>>a>>b;
cout<<exponent(a,b);
return 0;
}

