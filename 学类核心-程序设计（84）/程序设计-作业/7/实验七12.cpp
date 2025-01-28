#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;
//最大公约数 
int answer(int m,int n) {
	if(m%n==0)
		return n;
	else
		return answer(n,m%n);
}
int main() {
	int n,length,left,right;
	float num;
	string str;
	char number[100];
	cin>>n;
	int on[n],under[n];
	for(int i=0; i<n; i++) {
		cin>>str;
		if(str.find('(')>str.length()||str.find('(')<0) {
			length=str.length()-2;
			str.copy(number,length+2);
			number[str.length()]='\0';
			num=atof(number)*pow(10,length);
			on[i]=num/answer(num,pow(10,length));
			under[i]=pow(10,length)/answer(num,pow(10,length));
		} else if(str.find('(')==2) {
			left=str.find('(');
			right=str.find(')');
			length=right-left-1;
			str.copy(number,length,left+1);
			number[length]='\0';
			num=atoi(number);
			on[i]=num/answer(num,(pow(10,length)-1));
			under[i]=(pow(10,length)-1)/answer(num,(pow(10,length)-1));
		} else {
			int numA,numB;
			left=str.find('(');
			right=str.find(')');
			length=right-left-1;
			str.copy(number,length,left+1);
			number[length]='\0';
			numA=atoi(number);
			str.copy(number,left-2,2);
			number[left-2]='\0';
			numB=atoi(number)*pow(10,length)+numA-atoi(number);
			on[i]=numB/answer(numB,(pow(10,length)-1)*pow(10,left-2));
			under[i]=((pow(10,length)-1)*pow(10,left-2))/answer(numB,(pow(10,length)-1)*pow(10,left-2));
		}
	}
	for(int i=0; i<n; i++)
		cout<<on[i]<<"/"<<under[i]<<endl;
	return 0;
}

