#include <stdio.h>
void fun(char str[],int n)
{
	//ʹ����������ֱ��Ŵ�Сд�ַ�
	char min[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char max[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int i,k,m; 
	for(i=0;str[i]!='\0';i++)//�п�����Ҳ����ʹ��strlen(str)����ȡstr����ʵ�� 
	{
		if('a'<=str[i] && str[i]<='z')
		{
			k=str[i]-'a';//ʹ��k����õ�ǰ�ַ������ַ�a��ƫ��̶ȡ�����ǰ�ַ�Ϊa����k=0���պ÷����ַ�����min���±�
			m=(k+n)%26;//ʹ��m�������ƶ�����ַ�����26ȡ������֤mʼ��λ��0��25֮�䡣
			str[i]=min[m];
		}	
		else if('A'<=str[i] && str[i]<='Z')
		{
			k=str[i]-'A';
			m=(k+n)%26;
			str[i]=max[m];
		}		
	}		
}
int main()
{
	char a[10],ch;
	int n;
	scanf("%d",&n);
	ch=getchar();
	gets(a);
	fun(a,n);
	puts(a);
	return 0;
}

