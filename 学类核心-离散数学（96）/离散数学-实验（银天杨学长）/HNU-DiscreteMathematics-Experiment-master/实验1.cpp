/*
 * ʵ��һ
 * �����ַ���������жϺ�ʽ��ʽ�ĺϷ��ԡ� 
 * by ljkjk
 */

/* �޸ĵ�1��ʹ������ͷ�ļ���������ͷ�ļ������� */
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
void rule1(char a[],int i)
{
	if(a[i]>='a' && a[i]<='z') a[i]='1';
	else if(a[i]=='0') a[i]='1';
}
int rule2(char a[],int i)
{
	int n=strlen(a);
	int _result=0;

	if(i+1<n && a[i]=='!' && a[i+1]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+1]!='\0')
		{
			a[i]=a[i+1];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	/* �޸ĵ�2���޸�����˳������⣬�Ż���������߼��������˳���ĸ��� */
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
	else if(i+2<n && a[i]=='(' && a[i+1]=='1' && a[i+2]==')')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	/* �޸ĵ�3�����������ո�ʱ���жϣ����������ʽ���� */
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
int rule3Con(char a[],int i)
{
	int _result=0;
	int n=strlen(a);
	if(i+2<n && a[i]=='1' && a[i+1]=='*' && a[i+2]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	return _result;
}
int rule3BiCond(char a[],int i)
{
	int _result=0;
	int n=strlen(a);
	if(i+2<n && a[i]=='1' && a[i+1]=='=' && a[i+2]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	return _result;
}
int rule3Cond(char a[],int i)
{
	int _result=0;
	int n=strlen(a);
	if(i+2<n && a[i]=='1' && a[i+1]=='-' && a[i+2]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	return _result;
}
int rule3DisConj(char a[],int i)
{
	int _result=0;
	int n=strlen(a);
	if(i+2<n && a[i]=='1' && a[i+1]=='+' && a[i+2]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	return _result;
}
void rule3(char a[],int i)
{
	int n=strlen(a);
	if(i+2<n && a[i]=='1' && (a[i+1]=='*' || a[i+1]=='-' || a[i+1]=='=' || a[i+1]=='+') && a[i+2]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
	}
}

int main()
{
	/* �޸ĵ�4�������ж϶����ʽ��������ʹ�� */
	while(true)
	{
		char pstate[120],pstate0[120];
		int i=0,nold=0,nnew=0;
		printf("�����빫ʽ(��+,��*,��-,˫=,��!,01):\n");
		gets(pstate0);
		fflush(stdin);

		nold=strlen(pstate0)+1;
		nnew=strlen(pstate0);
		for(i=0;i<nnew;i++)
			pstate[i]=pstate0[i];
		pstate[i]='\0';
		i=0;
		while(i<strlen(pstate))
		{
			rule1(pstate,i);
			i++;
		}
		printf("����1��%s\n",pstate);

		nold=strlen(pstate0)+1;
		nnew=strlen(pstate);
		/* �޸ĵ�5���Ż�����ʾ�߼���ֻ�����Ҫ���еĲ��裬������� */
		while(nnew<nold)
		{
			nold=strlen(pstate);
			i=0;
			bool flag=false;
			while(i<strlen(pstate))
				if(rule2(pstate,i)==0)
					i++;
				else flag=true;
			if(flag) printf("����2��%s\n",pstate);

			i=0;
			flag=false;
			while(i<strlen(pstate))
				if(rule3Con(pstate,i)==0)
					i++;
				else flag=true;
			if(flag) printf("����3��ȡ��%s\n",pstate);

			i=0;
			flag=false;
			while(i<strlen(pstate))
				if(rule3BiCond(pstate,i)==0)
					i++;
				else flag=true;
			if(flag) printf("����3˫������%s\n",pstate);

			i=0;
			flag=false;
			while(i<strlen(pstate))
				if(rule3Cond(pstate,i)==0)
					i++;
				else flag=true;
			if(flag) printf("����3��������%s\n",pstate);

			i=0;
			flag=false;
			while(i<strlen(pstate))
				if(rule3DisConj(pstate,i)==0)
					i++;
				else flag=true;
			if(flag) printf("����3��ȡ��%s\n",pstate);

			nnew=strlen(pstate);
		}
		if(pstate[0]=='1' && strlen(pstate)==1)
			printf("%s is valid\n\n",pstate0);
		else
			printf("%s is invalid\n\n",pstate0);
	}
	return 0;
}

