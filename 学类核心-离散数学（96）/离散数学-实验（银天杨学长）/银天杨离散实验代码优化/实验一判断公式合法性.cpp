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

	//�����ǰλ������ ��1 ��λ 1
	if ( (i+1<n) && (a[i]=='!') && (a[i+1] == '1'))
	{
		a[i] = '1';
		i++;
		while (a[i+1]!='\0')
		{
			a[i] = a[i+1]; //������ַ�ǰ��һ�� 
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	/*�޸ĵ�1���޸�����˳������⣬�Ż���������߼��������˳���ĸ���*/ 
	//��ǰλ�� ��1�� �򻻳� 1 
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
	/* �޸ĵ�2�����������ո�ʱ���жϣ����������ʽ���� */
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
{//�˷� ��ȡ1*1to 1 
	// 1+1 1*1 1-1 1=1 ����Ϊ 1
	int n = strlen(a);
	if ( (i+2<n) && (a[i]=='1') && (a[i+1]=='*') && (a[i+2]=='1'))
	{
		a[i]='1'; //ǰ��2 
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
	// 1+1 1*1 1-1 1=1 ����Ϊ 1
	int n = strlen(a); 
	if ( (i+2<n) && (a[i]=='1') && (a[i+1]=='=') && (a[i+2]=='1'))
	{
		a[i]='1'; //ǰ��2 
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
	// 1+1 1*1 1-1 1=1 ����Ϊ 1
	int n = strlen(a);
	if ( (i+2<n) && (a[i]=='1') && (a[i+1]=='-') && (a[i+2]=='1'))
	{
		a[i]='1'; //ǰ��2 
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
	// 1+1 1*1 1-1 1=1 ����Ϊ 1
	int n = strlen(a);
	if ( (i+2<n) && (a[i]=='1') && (a[i+1]=='+') && (a[i+2]=='1'))
	{
		a[i]='1'; //ǰ��2 
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
	/* �޸ĵ�3�������ж϶����ʽ��������ʹ�� */
	while(1)
	{
	char pstate[120],pstate0[120];
	int i=0,nold=0,nnew=0;
	cout << "�����빫ʽ(��+ ,��*����-��˫������!,01):\n";
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
	cout << "����1��:" <<pstate <<endl;
	
	nold = strlen (pstate0)+1;
	nnew = strlen (pstate); 
	while ( nnew<nold)
	{
		nold = strlen(pstate);
		//ʹ�ù���2���ַ������д��� ��ı䳤�� 
		i=0;
		while( i<strlen(pstate))
		{
			rule2(pstate,i);
			i++;
		 } 
		cout << "����2��:" <<pstate <<endl;
		i=0;
		while( i<strlen(pstate))
		{
			rule3Con(pstate,i); //��ȡ 
			i++;
		 } 
		 i=0;
		 while( i<strlen(pstate))
		{
			rule3BiCond(pstate,i); //˫���������������ĺ�ȡ 
			i++;
		 }  
		 i=0;
		 while( i<strlen(pstate))
		{
			rule3Cond(pstate,i);  //�������� ǰ�У� 
			i++;
		 } 
		 i=0;
		 while( i<strlen(pstate))
		{
			rule3DisConj(pstate,i); //��ȡ 
			i++;
		 } 
		 cout <<  "����3��:" <<pstate <<endl;
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
