#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
/*���뼯��a������Ԫ��ֻ����A-Z,a-z,0-9,�����ַ��������ָ���ȥ����
2312fadskfakfAFAB
���뼯��b������Ԫ��ֻ����A-Z,a-z,0-9,�����ַ��������ָ���ȥ����
121314AFASFAaabed
A:1,2,3,A,B,F,a,d,f,k,s
B:1,2,3,4,A,F,S,a,b,d,e
���ϵĽ�:1,2,3,A,F,a,d
���ϵĲ�:1,2,3,4,A,B,F,S,a,b,d,e,f,k,s
���ϵĲ�:B,f,k,s
���ϵĶԳƲ�:B,f,k,s,4,S,b,e
<1,1>,<1,2>,<1,3>,<1,4>,<1,A>,<1,F>,<1,S>,<1,a>,<1,b>,<1,d>,<1,e>,<2,1>,<2,2>,<2,3>,<2,4>,<2,A>,<2,F>,<2,S>,<2,a>,
<2,b>,<2,d>,<2,e>,<3,1>,<3,2>,<3,3>,<3,4>,<3,A>,<3,F>,<3,S>,<3,a>,<3,b>,<3,d>,<3,e>,<A,1>,<A,2>,<A,3>,<A,4>,<A,A>,
<A,F>,<A,S>,<A,a>,<A,b>,<A,d>,<A,e>,<B,1>,<B,2>,<B,3>,<B,4>,<B,A>,<B,F>,<B,S>,<B,a>,<B,b>,<B,d>,<B,e>,<F,1>,<F,2>,
<F,3>,<F,4>,<F,A>,<F,F>,<F,S>,<F,a>,<F,b>,<F,d>,<F,e>,<a,1>,<a,2>,<a,3>,<a,4>,<a,A>,<a,F>,<a,S>,<a,a>,<a,b>,<a,d>,
<a,e>,<d,1>,<d,2>,<d,3>,<d,4>,<d,A>,<d,F>,<d,S>,<d,a>,<d,b>,<d,d>,<d,e>,<f,1>,<f,2>,<f,3>,<f,4>,<f,A>,<f,F>,<f,S>,
<f,a>,<f,b>,<f,d>,<f,e>,<k,1>,<k,2>,<k,3>,<k,4>,<k,A>,<k,F>,<k,S>,<k,a>,<k,b>,<k,d>,<k,e>,<s,1>,<s,2>,<s,3>,<s,4>,
<s,A>,<s,F>,<s,S>,<s,a>,<s,b>,<s,d>,<s,e>*/
/*�޸ĵ�1���Ľ�print�������Ż��˴�������*/
int print(char a[])
{
	//���ϱ�����һ���ַ�������ʾʱ�ڸ�Ԫ��֮����붺�ţ������س���
	/*int nLen=0;
	int i=0;
	nLen=strlen(a);
	if(nLen>0) printf("%c",a[0]);
	for(i=1;i<nLen;i++) printf(",%c",a[i]);
	printf("\n");*/
	int nlen=strlen(a);
    if(nlen==0)
        printf("�ռ�");
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
	//���ڼ��ϱ�����һ���ַ����ڣ���������ʱ���ַ��ö��Ÿ���
	//�β�a��һ������ �������һ����ֵַ �ں����Ը�������޸Ļᷴӳ��������
	char nLen=0,i=0,j=0,k=0;
	char stmp[1024];
	printf("����Ԫ��ֻ����A-Z,a-z,0-9,�����ַ��������ָ���ȥ����\n");
	gets(stmp); fflush(stdin);
	nLen =strlen(stmp);
	for(i=0;i<nLen;i++)
	{
		if((stmp[i]>='A'&&stmp[i]<='Z')||(stmp[i]>='a'&&stmp[i]<='z')||(stmp[i]>='0'&&stmp[i]<='9'))
		{
			//�жϸ��ַ��Ƿ��Ѿ�����
			/*for(k=0;k<j;k++)
			{
				if(a[k]==stmp[i]) break;// ���������ȽϽ��� 
			} 
			if (k>j) 
			{
				a[j]=stmp[i];
				j++; //û�г�����д�뵽a�� 
			}*/
			/* �޸ĵ�2��ʹ��strchr��������ѭ���������Ż��������ٶ� */
            if(strchr(a,stmp[i])==NULL)
            {
                a[j]=stmp[i];
                j++;
            }
		}
	 } 
	 /* �޸ĵ�3��ʹ��sort�������������򣬷�����ʹ�� */
    sort(a,a+j);
	 a[j]='\0';
	 return j;
}

int setjiao(char a[],char b[],char c[])
{
	//���ϵĽ� ��������� c��
	int i=0,j=0,k=0,nLen1=0,nLen2=0;
	nLen1 =strlen(a);
	nLen2 = strlen(b);
	for(i=0;i<nLen1;i++)
	{
		for(j=0;j<nLen2;j++)
		{
			if(a[i]==b[j]) break;//�ҵ������ 
		}
		if(j<nLen2) //�ҵ��������뵽������ 
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
	//���׸�����a��ֵ���뵽c��
	/* for(i=0;i<nLen1;i++)
	 {
	 	c[i]=a[i];
	 }*/
	/* �޸ĵ�4��ʹ��strcpy������������ */
    strcpy(c,a);
	 k=nLen1;
	 for(i=0;i<nLen2;i++)
	 {
	 	for(j=0;j<nLen1;j++)
	 	{
	 		if(b[i]==a[j]) break; //�ҵ������ 
		 }
		 if(j>=nLen1)
		 {
		 	c[k]=b[i]; k++;
		 }
	 }
	 /*�޸ĵ�5sort����*/ 
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
	//��a-b���뵽c��
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
	 //�� b-a���뵽c�� 
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
	printf("���뼯��a��");
	input(a);
	printf("���뼯��b��");
	input(b);
	printf("A:");
	print(a);
	printf("B:");
	print(b);
	printf("���ϵĽ�:");
	setjiao(a,b,c);
	print(c);
	printf("���ϵĲ�:");
	setbin(a,b,c);
	print(c);
	printf("���ϵĲ�:");
	setsub(a,b,c);
	print(c);
	printf("���ϵĶԳƲ�:");
	setdc(a,b,c);
	print(c);
	nlen=setdicarl(a,b,dcar);
	if(nlen>0)
        printf("<%c,%c>",dcar[0][0],dcar[0][1]);
    for(i=1;i<nlen;++i)
        printf(",<%c,%c>",dcar[i][0],dcar[i][1]);
	return 0;
}
