#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
/*输入集合a：集合元素只能是A-Z,a-z,0-9,其他字符被当作分隔符去掉：
2312fadskfakfAFAB
输入集合b：集合元素只能是A-Z,a-z,0-9,其他字符被当作分隔符去掉：
121314AFASFAaabed
A:1,2,3,A,B,F,a,d,f,k,s
B:1,2,3,4,A,F,S,a,b,d,e
集合的交:1,2,3,A,F,a,d
集合的并:1,2,3,4,A,B,F,S,a,b,d,e,f,k,s
集合的差:B,f,k,s
集合的对称差:B,f,k,s,4,S,b,e
<1,1>,<1,2>,<1,3>,<1,4>,<1,A>,<1,F>,<1,S>,<1,a>,<1,b>,<1,d>,<1,e>,<2,1>,<2,2>,<2,3>,<2,4>,<2,A>,<2,F>,<2,S>,<2,a>,
<2,b>,<2,d>,<2,e>,<3,1>,<3,2>,<3,3>,<3,4>,<3,A>,<3,F>,<3,S>,<3,a>,<3,b>,<3,d>,<3,e>,<A,1>,<A,2>,<A,3>,<A,4>,<A,A>,
<A,F>,<A,S>,<A,a>,<A,b>,<A,d>,<A,e>,<B,1>,<B,2>,<B,3>,<B,4>,<B,A>,<B,F>,<B,S>,<B,a>,<B,b>,<B,d>,<B,e>,<F,1>,<F,2>,
<F,3>,<F,4>,<F,A>,<F,F>,<F,S>,<F,a>,<F,b>,<F,d>,<F,e>,<a,1>,<a,2>,<a,3>,<a,4>,<a,A>,<a,F>,<a,S>,<a,a>,<a,b>,<a,d>,
<a,e>,<d,1>,<d,2>,<d,3>,<d,4>,<d,A>,<d,F>,<d,S>,<d,a>,<d,b>,<d,d>,<d,e>,<f,1>,<f,2>,<f,3>,<f,4>,<f,A>,<f,F>,<f,S>,
<f,a>,<f,b>,<f,d>,<f,e>,<k,1>,<k,2>,<k,3>,<k,4>,<k,A>,<k,F>,<k,S>,<k,a>,<k,b>,<k,d>,<k,e>,<s,1>,<s,2>,<s,3>,<s,4>,
<s,A>,<s,F>,<s,S>,<s,a>,<s,b>,<s,d>,<s,e>*/
/*修改点1：改进print函数，优化了代码质量*/
int print(char a[])
{
	//集合保存在一个字符串，显示时在各元素之间加入逗号，及返回长度
	/*int nLen=0;
	int i=0;
	nLen=strlen(a);
	if(nLen>0) printf("%c",a[0]);
	for(i=1;i<nLen;i++) printf(",%c",a[i]);
	printf("\n");*/
	int nlen=strlen(a);
    if(nlen==0)
        printf("空集");
    else
        for(int i=0;i<nlen;++i)
        {
            if(i>0) printf(",");
            printf("%c",a[i]);
        }
    printf("\n");
	return nlen; 
}
int input(char a[])
{
	//由于集合保存在一个字符串内，但是输入时个字符用逗号隔开
	//形参a是一个数组 输入的是一个地址值 在函数对该数组的修改会反映在主函数
	char nLen=0,i=0,j=0,k=0;
	char stmp[1024];
	printf("集合元素只能是A-Z,a-z,0-9,其他字符被当作分隔符去掉：\n");
	gets(stmp); fflush(stdin);
	nLen =strlen(stmp);
	for(i=0;i<nLen;i++)
	{
		if((stmp[i]>='A'&&stmp[i]<='Z')||(stmp[i]>='a'&&stmp[i]<='z')||(stmp[i]>='0'&&stmp[i]<='9'))
		{
			//判断该字符是否已经出现
			/*for(k=0;k<j;k++)
			{
				if(a[k]==stmp[i]) break;// 如果出现则比较结束 
			} 
			if (k>j) 
			{
				a[j]=stmp[i];
				j++; //没有出现则写入到a中 
			}*/
			/* 修改点2：使用strchr函数代替循环搜索，优化了运行速度 */
            if(strchr(a,stmp[i])==NULL)
            {
                a[j]=stmp[i];
                j++;
            }
		}
	 } 
	 /* 修改点3：使用sort函数将集合排序，方便了使用 */
    sort(a,a+j);
	 a[j]='\0';
	 return j;
}

int setjiao(char a[],char b[],char c[])
{
	//集合的交 结果保存在 c中
	int i=0,j=0,k=0,nLen1=0,nLen2=0;
	nLen1 =strlen(a);
	nLen2 = strlen(b);
	for(i=0;i<nLen1;i++)
	{
		for(j=0;j<nLen2;j++)
		{
			if(a[i]==b[j]) break;//找到则结束 
		}
		if(j<nLen2) //找到了则输入到交集中 
		{
			c[k]=a[i];
			k++;
		}
	 } 
	 c[k]='\0';
	 return k; 
}
int setbin(char a[],char b[],char c[])
{
	int i=0,j=0,k=0,nLen1=0,nLen2=0;
	nLen1 =strlen(a);
	nLen2 = strlen(b);
	//将首个集合a的值输入到c中
	/* for(i=0;i<nLen1;i++)
	 {
	 	c[i]=a[i];
	 }*/
	/* 修改点4：使用strcpy函数复制数组 */
    strcpy(c,a);
	 k=nLen1;
	 for(i=0;i<nLen2;i++)
	 {
	 	for(j=0;j<nLen1;j++)
	 	{
	 		if(b[i]==a[j]) break; //找到则结束 
		 }
		 if(j>=nLen1)
		 {
		 	c[k]=b[i]; k++;
		 }
	 }
	 /*修改点5sort排序*/ 
	 sort(c,c+k);
	 c[k]='\0';
	 return k;
}
int setsub(char a[],char b[],char c[])
{
	int i=0,j=0,k=0,nLen1=0,nLen2=0;
	nLen1 =strlen(a);
	nLen2 = strlen(b);
	for(i=0;i<nLen1;i++)
	{
		for(j=0;j<nLen2;j++)
		{
			if(a[i]==b[j]) break;
		}
		if(j>=nLen1)
		{
			c[k]=a[i];
			k++;
		}
	}
	c[k]='\0';
	return k;
}
int setdc(char a[],char b[],char c[])
{
	int i=0,j=0,k=0,nLen1=0,nLen2=0;
	nLen1 =strlen(a);
	nLen2 = strlen(b);
	//将a-b送入到c中
	for(i=0;i<nLen1;i++)
	{
		for(j=0;j<nLen2;j++)
		{
			if(a[i]==b[j]) break;
		}
		if(j>=nLen1) {
			c[k]=a[i];
			k++;
		}
	 } 
	 //将 b-a送入到c中 
	 for(i=0;i<nLen2;i++)
	 {
	 	for(j=0;j<nLen1;j++)
	 	if(a[j]==b[i]) break;
	 	if (j>=nLen1) 
		 {
	 		c[k]=b[i];
	 		k++;
		 }
	 }
	 c[k]='\0';
	 return k;
}
int setdicarl(char a[],char b[],char c[][3])
{
    int i=0,j=0,k=0,nlen1=0,nlen2=0;
    nlen1=strlen(a);
    nlen2=strlen(b);
    for(i=0;i<nlen1;++i)
    {
        for(j=0;j<nlen2;++j)
        {
            c[k][0]=a[i];
            c[k][1]=b[j];
            c[k][2]='\0';
            k++;
        }
    }
    return k;
}
int main()
{
	char a[1024],b[1024],c[1024],dcar[1024][3];
	int nlen=0;
	int i=0;
	printf("输入集合a：");
	input(a);
	printf("输入集合b：");
	input(b);
	printf("A:");
	print(a);
	printf("B:");
	print(b);
	printf("集合的交:");
	setjiao(a,b,c);
	print(c);
	printf("集合的并:");
	setbin(a,b,c);
	print(c);
	printf("集合的差:");
	setsub(a,b,c);
	print(c);
	printf("集合的对称差:");
	setdc(a,b,c);
	print(c);
	nlen=setdicarl(a,b,dcar);
	if(nlen>0)
        printf("<%c,%c>",dcar[0][0],dcar[0][1]);
    for(i=1;i<nlen;++i)
        printf(",<%c,%c>",dcar[i][0],dcar[i][1]);
	return 0;
}
