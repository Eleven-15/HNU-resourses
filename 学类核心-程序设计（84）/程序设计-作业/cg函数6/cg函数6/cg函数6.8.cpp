#include <stdio.h>
void fun(char str[],int n)
{
	//使用两个数组分别存放大小写字符
	char min[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char max[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int i,k,m; 
	for(i=0;str[i]!='\0';i++)//判空条件也可以使用strlen(str)来获取str长度实现 
	{
		if('a'<=str[i] && str[i]<='z')
		{
			k=str[i]-'a';//使用k来获得当前字符对于字符a的偏离程度。若当前字符为a，则k=0，刚好符合字符数组min的下标
			m=(k+n)%26;//使用m来保存移动后的字符，对26取余数保证m始终位于0至25之间。
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

