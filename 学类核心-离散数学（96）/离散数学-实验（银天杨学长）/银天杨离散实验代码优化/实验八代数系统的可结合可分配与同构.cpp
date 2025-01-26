#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100

/*
 * 修改点1：万能头文件
 * 修改点2：优化选项 
 * 修改点3：利用while判断输入是否合法 
 */
 /* 修改点1：万能头文件 
#include <bits/stdc++.h>
*/
/*
序偶形式的关系到关系矩阵 
a,b,c
a,b,c,b,c,a,c,a,b
a,b,c,b,b,b,c,b,c

同构测试数据
0,2,4
0 1 2 -1
0,2,4,2,4,0,4,0,2 

*/
//集合的基本交并差，对称差，直积
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
	//集合保存在一个字符串内，输入时用逗号隔开
	//形参a是一个数组，输入的是一个地址值，函数对该数组的修改会反映在主函数
	char nLen=0,i=0,j=0,k=0;
	char stmp[1024]; //最多1024个字符
	printf("集合元素只能是A-Za-z0-9,其它字符被当做分隔符而去掉:\n");
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
	 return j;//字符串长度 
}
int inputInt(int fun[])
{
	int i=0,n=0;
	printf("请输入多个整数，彼此间用空格分隔；");
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
	//将字符串按每行转换成二维数组
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
	//寻找字符yz在字母表alphaTable表中的序号
	int i=0,nLen=0;
	nLen=strlen(alphaTable);
	for(i=0;i<nLen;i++)
	if(alphaTable[i]==yz) break;
	return i;
}
int testCombine(char ysb[][N],char alphaTable[])
{
	//ysb[][]是运算表，运算表的真实行数与列数=字母表的alphaTable中的元数个数
	int i=0,nRow=0,nChar=0,n3=0,iyz=0,ixy=0,ix=0,iy=0,iz=0;
	char yz,xy,xyz1,xyz2;
	nChar=strlen(alphaTable);
	n3=nChar*nChar*nChar;
	ix=0;iy=0;iz=0;
	printf("%4c%4c%4c%20s%20s%10s\n",'x','y','z',"x*(y*z)","(x*y)*z","相等");
	for(i=0;i<n3;i++)
	{
		yz=ysb[iy][iz];//y*z对应的运算结果 
		iyz=getIndex(alphaTable,yz);//寻找字母yz对应的序号 
		xyz1=ysb[ix][iyz];//x*(y*z)的结果
		
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
	printf("%4c%4c%4c%20s%20s%10s\n",'x','y','z',"x*(y+z)","(x*y)+(x*z)","相等");
	for(i=0;i<n3;i++)
	{
		yz=ysbb[iy][iz];//y*z对应的运算结果 
		iyz=getIndex(alphaTable,yz);//寻找字母yz对应的序号 
		xyz1=ysb[ix][iyz];//x*(y*z)的结果
		
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
	//ysb[][]是运算表
	int i=0,n2=0,ix,iy,ixy,ifx,ify,ifxy;
	char xyc,xycb,xy;
	n2=nFun*nFun;
	ix=0; iy=0;
	//*运算1 +运算2
	printf("%4c%4c%20s%20s%10s\n",'x','y',"f(y*z)","f(x)+f(y)","相等");
	for(i=0;i<n2;i++)
	{
		xy=ysb[ix][iy];//1运算 
		ixy=getIndex(a,xy);//寻找字母xy序号 
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
		/* 修改点2：优化交互 
	bool flag1=false;
	
        */
	while(1)
	{
		/*
		if(!flag1)
		{
            printf("1...输入相关元素值\n");
            flag1=true;
        }
        if(flag1)
        {
            printf("2...判断元素表是否可结合\n");
            printf("3...判断二个运算表是否可分配\n
            printf("4...判断二个系统是否构造相同\n");

        }
        printf("\n===========================\n");
        printf("您的选择(输入0结束)：\n");
        */
		printf("\n=====================\n");
		printf("1...输入相关元素值\n");
		printf("2...判断元素表是否可结合\n");
		printf("3...判断二个运算表是否可分配\n");
		printf("4...判断二个系统是否构造相同\n");
		printf("=========================\n您的选择：");
//        /* 修改点3：判断输入是否合法 */
//        while(scanf("%d",&nchoice))
//            if((nchoice>=0&&nchoice<=4)) break;
//            else printf("请重新输入\n"); 
		scanf("%d",&nChoice);fflush(stdin);
		if(nChoice==0) break;
		switch(nChoice)
		{
			case 1:
				{
					printf("请输入集合A");
					inputYsh(a);
					
					printf("请输入运算表：");
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
						printf("请输入集合A:");
						inputYsh(a);
						
						printf("请输入运算表1：");
						inputYsh(ystable);
						printf("请输入运算表2：");
						inputYsh(ystableB);
						
						printf("二维形式的运算表1*：\n");
						string2matrix(ystable,ystableD2,strlen(a));
						printAlgTableYsh(ystableD2,strlen(a));
						printf("二维形式的运算表2+：\n");
						string2matrix(ystableB,ystableBD2,strlen(a));
						printAlgTableYsh(ystableBD2,strlen(a));
						
						testAssign(ystableD2,a,ystableBD2);
						break;
						
					}
				case 4:
					{
						printf("请输入集合A:");
						inputYsh(a);
						printf("请输入集合B:");
						inputYsh(b);
						printf("映射关系：");
						nFun=inputInt(fun);
						
						printf("请输入运算表1：");
						inputYsh(ystable);
						printf("请输入运算表2：");
						inputYsh(ystableB);
						
						printf("二维形式的运算表1*：\n");
						string2matrix(ystable,ystableD2,strlen(a));
						printAlgTableYsh(ystableD2,strlen(a));
						printf("二维形式的运算表2+：\n");
						string2matrix(ystableB,ystableBD2,strlen(a));
						printAlgTableYsh(ystableBD2,strlen(a));
						
						testStruct(ystableD2,a,ystableBD2,b,fun,nFun);
						break; 
					}

		 } 
	}
	return 0;
}
