#include<iostream>
#include <string.h>
using namespace std;
void rule1 (char a[],int i)
{
	if( (a[i] >= 'a') && ( a[i] <= 'z'))
	{
		a[i]='1';
	}
	else if (a[i]=='0')
	{
		a[i]='1';
	}
} 
int rule2(char a[],int i)
{
	int n=strlen(a);
	int _result=0;

	//如果当前位置形如 ！1 换位 1
	if ( (i+1<n) && (a[i]=='!') && (a[i+1] == '1'))
	{
		a[i] = '1';
		i++;
		while (a[i+1]!='\0')
		{
			a[i] = a[i+1]; //后面的字符前移一格 
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	/*修改点1：修改运算顺序的问题，优化了运算的逻辑，减少了出错的概率*/ 
	//当前位如 （1） 则换成 1 
	else if(i+3<n && a[i]=='!' && a[i+1]=='(' && a[i+2]=='1' && a[i+3]==')')
	{
		a[i]='1';
		i++;
		while(a[i+3]!='\0')
		{
			a[i]=a[i+3];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	else if ( (i+2<n) && (a[i]=='(') && (a[i+1]=='1') && (a[i+2]==')')) 
	{
		a[i] = '1';
		i++;
		while (a[i+2] != '\0' )
		{
			a[i] = a[i+2];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	/* 修改点2：增加遇到空格时的判断，避免输入格式问题 */
	else if(i<n && a[i]==' ')
	{
		while(a[i+1]!='\0')
		{
			a[i]=a[i+1];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	return _result;
}
void rule3Con(char a[],int i)
{//乘法 合取1*1to 1 
	// 1+1 1*1 1-1 1=1 均化为 1
	int n = strlen(a);
	if ( (i+2<n) && (a[i]=='1') && (a[i+1]=='*') && (a[i+2]=='1'))
	{
		a[i]='1'; //前移2 
		i++;
		while( a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		 } 
		 a[i]='\0';
	}
}
void rule3BiCond(char a[],int i)
{
	// 1+1 1*1 1-1 1=1 均化为 1
	int n = strlen(a); 
	if ( (i+2<n) && (a[i]=='1') && (a[i+1]=='=') && (a[i+2]=='1'))
	{
		a[i]='1'; //前移2 
		i++;
		while( a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		 } 
		 a[i]='\0';
	}
}
void rule3Cond(char a[],int i)
{
	// 1+1 1*1 1-1 1=1 均化为 1
	int n = strlen(a);
	if ( (i+2<n) && (a[i]=='1') && (a[i+1]=='-') && (a[i+2]=='1'))
	{
		a[i]='1'; //前移2 
		i++;
		while( a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		 } 
		 a[i]='\0';
	}
}
void rule3DisConj(char a[],int i)
{
	// 1+1 1*1 1-1 1=1 均化为 1
	int n = strlen(a);
	if ( (i+2<n) && (a[i]=='1') && (a[i+1]=='+') && (a[i+2]=='1'))
	{
		a[i]='1'; //前移2 
		i++;
		while( a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		 } 
		 a[i]='\0';
	}
}
int main()
{
	/* 修改点3：连续判断多个公式，方便了使用 */
	while(1)
	{
	char pstate[120],pstate0[120];
	int i=0,nold=0,nnew=0;
	cout << "请输入公式(析+ ,合*，条-，双二，否定!,01):\n";
	gets(pstate0);
	fflush(stdin);
	
	nold = strlen (pstate0)+1;
	nnew = strlen (pstate0);
	for( i=0;i<nnew;i++)
	{
		pstate[i]=pstate0[i];
	}
	pstate[i] = '\0';
	i=0;
	while(i<strlen(pstate))
	{
		rule1(pstate,i);
		i++;
	}
	cout << "规则1后:" <<pstate <<endl;
	
	nold = strlen (pstate0)+1;
	nnew = strlen (pstate); 
	while ( nnew<nold)
	{
		nold = strlen(pstate);
		//使用规则2对字符串进行处理 会改变长度 
		i=0;
		while( i<strlen(pstate))
		{
			rule2(pstate,i);
			i++;
		 } 
		cout << "规则2后:" <<pstate <<endl;
		i=0;
		while( i<strlen(pstate))
		{
			rule3Con(pstate,i); //合取 
			i++;
		 } 
		 i=0;
		 while( i<strlen(pstate))
		{
			rule3BiCond(pstate,i); //双条件，两个条件的合取 
			i++;
		 }  
		 i=0;
		 while( i<strlen(pstate))
		{
			rule3Cond(pstate,i);  //单个条件 前有！ 
			i++;
		 } 
		 i=0;
		 while( i<strlen(pstate))
		{
			rule3DisConj(pstate,i); //析取 
			i++;
		 } 
		 cout <<  "规则3后:" <<pstate <<endl;
		 nnew = strlen (pstate);
	}
	if( (pstate[0]=='1') && (strlen(pstate)==1))
	{
		cout << pstate0 <<"is valid\n";
	}
	else {
		cout << pstate << "is invalid\n"; 
	}
	}
	return 0;
}
