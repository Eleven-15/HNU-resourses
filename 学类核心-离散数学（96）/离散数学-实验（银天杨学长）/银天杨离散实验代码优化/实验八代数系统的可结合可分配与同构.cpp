#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100

/*
 * �޸ĵ�1������ͷ�ļ�
 * �޸ĵ�2���Ż�ѡ�� 
 * �޸ĵ�3������while�ж������Ƿ�Ϸ� 
 */
 /* �޸ĵ�1������ͷ�ļ� 
#include <bits/stdc++.h>
*/
/*
��ż��ʽ�Ĺ�ϵ����ϵ���� 
a,b,c
a,b,c,b,c,a,c,a,b
a,b,c,b,b,b,c,b,c

ͬ����������
0,2,4
0 1 2 -1
0,2,4,2,4,0,4,0,2 

*/
//���ϵĻ���������ԳƲֱ��
int printYsh(char a[])
{
	int nLen=0;
	int i=0;
	nLen=strlen(a);
	if(nLen>0)printf("%c",a[0]);
	for(i=1;i<nLen;i++) printf(",%C",a[i]);
	printf("\n");
	return nLen;
 } 
int printAlgTableYsh(char a[][N],int n)
{
	int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%4c",a[i][j]);
		}
		printf("\n");
	}
	return n;
}
int inputYsh(char a[])
{
	//���ϱ�����һ���ַ����ڣ�����ʱ�ö��Ÿ���
	//�β�a��һ�����飬�������һ����ֵַ�������Ը�������޸Ļᷴӳ��������
	char nLen=0,i=0,j=0,k=0;
	char stmp[1024]; //���1024���ַ�
	printf("����Ԫ��ֻ����A-Za-z0-9,�����ַ��������ָ�����ȥ��:\n");
	gets(stmp); fflush(stdin);
	nLen=strlen(stmp);
	for(i=0;i<nLen;i++)
	{
		if (((stmp[i] >= 'A') && (stmp[i] <= 'Z')) ||
		((stmp[i] >= 'a') && (stmp[i] <= 'z')) ||
		 ((stmp[i] >= '0') && (stmp[i] <= '9')))
		 {
		 	a[j]=stmp[i];
		 	j++;
		 }
	 } 
	 a[j]='\0';
	 return j;//�ַ������� 
}
int inputInt(int fun[])
{
	int i=0,n=0;
	printf("���������������˴˼��ÿո�ָ���");
	scanf("%d",&i);
	while(i>=0)
	{
		fun[n]=i;
		n++;
		scanf("%d",&i);
	 } 
	 fflush(stdin);
	 return n;
}
int string2matrix(char a[],char b[][N],int n)
{
	//���ַ�����ÿ��ת���ɶ�ά����
	int i=0,j=0,k=0,nLen=0;
	nLen=strlen(a);
	for(k=0;k<nLen;k++)
	{
		b[i][j]=a[k];
		if((k+1)%n==0){i++;j=0;	}
		else j++;
	 } 
	 return i;
}
int getIndex(char alphaTable[],char yz)
{
	//Ѱ���ַ�yz����ĸ��alphaTable���е����
	int i=0,nLen=0;
	nLen=strlen(alphaTable);
	for(i=0;i<nLen;i++)
	if(alphaTable[i]==yz) break;
	return i;
}
int testCombine(char ysb[][N],char alphaTable[])
{
	//ysb[][]���������������ʵ����������=��ĸ���alphaTable�е�Ԫ������
	int i=0,nRow=0,nChar=0,n3=0,iyz=0,ixy=0,ix=0,iy=0,iz=0;
	char yz,xy,xyz1,xyz2;
	nChar=strlen(alphaTable);
	n3=nChar*nChar*nChar;
	ix=0;iy=0;iz=0;
	printf("%4c%4c%4c%20s%20s%10s\n",'x','y','z',"x*(y*z)","(x*y)*z","���");
	for(i=0;i<n3;i++)
	{
		yz=ysb[iy][iz];//y*z��Ӧ�������� 
		iyz=getIndex(alphaTable,yz);//Ѱ����ĸyz��Ӧ����� 
		xyz1=ysb[ix][iyz];//x*(y*z)�Ľ��
		
		xy=ysb[ix][iy];
		ixy=getIndex(alphaTable,xy);
		xyz2=ysb[ixy][iz];
		
		printf("%4c%4c%4c%20c%20c%10c\n",alphaTable[ix],alphaTable[iy],alphaTable[iz],xyz1,xyz2,(xyz1==xyz2?'=':'!='));
		iz++;
		if(iz=nChar)
		{
			iz=0;
			iy++;
		}
		if(iy=nChar)
		{
			iy=0;
			ix++;
		}
	 } 
	 return n3;
}
int testAssign(char ysb[N][N],char alphaTable[],char ysbb[N][N])
{
	int i=0,nChar=0,n3=0,iyz=0,ixy=0,ix=0,iy=0,iz=0,ixz=0;
	char yz,xy,xz,xyz1,xyz2;
	nChar=strlen(alphaTable);
	n3=nChar*nChar*nChar;
	ix=0;iy=0;iz=0;
	printf("%4c%4c%4c%20s%20s%10s\n",'x','y','z',"x*(y+z)","(x*y)+(x*z)","���");
	for(i=0;i<n3;i++)
	{
		yz=ysbb[iy][iz];//y*z��Ӧ�������� 
		iyz=getIndex(alphaTable,yz);//Ѱ����ĸyz��Ӧ����� 
		xyz1=ysb[ix][iyz];//x*(y*z)�Ľ��
		
		xy=ysb[ix][iy];
		ixy=getIndex(alphaTable,xy);
		xz=ysb[ix][iz];
		ixz=getIndex(alphaTable,xz);
		xyz2=ysbb[ixy][ixz];
		
		printf("%4c%4c%4c%20c%20c%10c\n",alphaTable[ix],alphaTable[iy],alphaTable[iz],xyz1,xyz2,(xyz1==xyz2?'=':'!='));
		iz++;
		if(iz=nChar)
		{
			iz=0;
			iy++;
		}
		if(iy=nChar)
		{
			iy=0;
			ix++;
		}
	 } 
	 return n3;
}
int testStruct(char ysb[][N],char a[],char ysbb[][N],char b[],int fun[],int nFun)
{
	//ysb[][]�������
	int i=0,n2=0,ix,iy,ixy,ifx,ify,ifxy;
	char xyc,xycb,xy;
	n2=nFun*nFun;
	ix=0; iy=0;
	//*����1 +����2
	printf("%4c%4c%20s%20s%10s\n",'x','y',"f(y*z)","f(x)+f(y)","���");
	for(i=0;i<n2;i++)
	{
		xy=ysb[ix][iy];//1���� 
		ixy=getIndex(a,xy);//Ѱ����ĸxy��� 
		ifxy=fun[ixy];
		
		ifx=fun[ix];
		ify=fun[iy];
		xycb=ysbb[ifx][ify];
		
		printf("%4c%4c%20c%20c%10c\n",a[ix],a[iy],xyc,xycb,(xyc==xycb?'=':'!='));
		iy++;
		if(iy==nFun)
		{
			iy=0;
			ix++;
		}
	 }
	 return n2; 
}
int main()
{
	char a[N],b[N],ystable[N],ystableD2[N][N],ystableB[N],ystableBD2[N][N];
	int i=0,nLen1=0,nChoice=0,fun[N],nFun=0;
		/* �޸ĵ�2���Ż����� 
	bool flag1=false;
	
        */
	while(1)
	{
		/*
		if(!flag1)
		{
            printf("1...�������Ԫ��ֵ\n");
            flag1=true;
        }
        if(flag1)
        {
            printf("2...�ж�Ԫ�ر��Ƿ�ɽ��\n");
            printf("3...�ж϶���������Ƿ�ɷ���\n
            printf("4...�ж϶���ϵͳ�Ƿ�����ͬ\n");

        }
        printf("\n===========================\n");
        printf("����ѡ��(����0����)��\n");
        */
		printf("\n=====================\n");
		printf("1...�������Ԫ��ֵ\n");
		printf("2...�ж�Ԫ�ر��Ƿ�ɽ��\n");
		printf("3...�ж϶���������Ƿ�ɷ���\n");
		printf("4...�ж϶���ϵͳ�Ƿ�����ͬ\n");
		printf("=========================\n����ѡ��");
//        /* �޸ĵ�3���ж������Ƿ�Ϸ� */
//        while(scanf("%d",&nchoice))
//            if((nchoice>=0&&nchoice<=4)) break;
//            else printf("����������\n"); 
		scanf("%d",&nChoice);fflush(stdin);
		if(nChoice==0) break;
		switch(nChoice)
		{
			case 1:
				{
					printf("�����뼯��A");
					inputYsh(a);
					
					printf("�����������");
					inputYsh(ystable);
					
					printYsh(a);
					printYsh(ystable);
					
					string2matrix(ystable,ystableD2,strlen(a));
					printAlgTableYsh(ystableD2,strlen(a));
				}
				case 2:
					{
						testCombine(ystableD2,a);
						break;
					}
				case 3:
					{
						printf("�����뼯��A:");
						inputYsh(a);
						
						printf("�����������1��");
						inputYsh(ystable);
						printf("�����������2��");
						inputYsh(ystableB);
						
						printf("��ά��ʽ�������1*��\n");
						string2matrix(ystable,ystableD2,strlen(a));
						printAlgTableYsh(ystableD2,strlen(a));
						printf("��ά��ʽ�������2+��\n");
						string2matrix(ystableB,ystableBD2,strlen(a));
						printAlgTableYsh(ystableBD2,strlen(a));
						
						testAssign(ystableD2,a,ystableBD2);
						break;
						
					}
				case 4:
					{
						printf("�����뼯��A:");
						inputYsh(a);
						printf("�����뼯��B:");
						inputYsh(b);
						printf("ӳ���ϵ��");
						nFun=inputInt(fun);
						
						printf("�����������1��");
						inputYsh(ystable);
						printf("�����������2��");
						inputYsh(ystableB);
						
						printf("��ά��ʽ�������1*��\n");
						string2matrix(ystable,ystableD2,strlen(a));
						printAlgTableYsh(ystableD2,strlen(a));
						printf("��ά��ʽ�������2+��\n");
						string2matrix(ystableB,ystableBD2,strlen(a));
						printAlgTableYsh(ystableBD2,strlen(a));
						
						testStruct(ystableD2,a,ystableBD2,b,fun,nFun);
						break; 
					}

		 } 
	}
	return 0;
}
