#include <bits/stdc++.h>
using namespace std;
int getalpha(char a[],char b[])
{
    char tmpc=' ';
    int n=strlen(a),i=0,j=0,k=0;
    for(i=0;i<n;i++)
    {
    	 if((a[i]>='a'&&a[i]<='z')||(a[i]>='A'&&a[i]<='Z'))
        {
            for(k=0;k<j;k++){if (b[k]==a[i]) {break;}}
            if(k>=j){b[j]=a[i];j++;}
			}
	}
	for(i=0;i<j-1;i++){
		for(k=0;k<j-i-1;k++){
			if(b[k]>b[k+1]){
				tmpc=b[k]; b[k]=b[k+1]; b[k+1]=tmpc;
			}
		}
	}
	b[j]='\0';
	return j;
}

void fillvalue(char a[],char varchar[],int nvar,char valchar[],char resultchar[])
{
    int nLen=strlen(a),i=0,j=0,k=0;
    for(i=0;i<nLen;++i)
        resultchar[i]=a[i];
    resultchar[i]='\0';
    for(i=0;i<nLen;++i)
        for(j=0;j<nvar;++j)
            if(resultchar[i]==varchar[j])
            {
                resultchar[i]=valchar[j];
                break;
            }
}

/* 修改点3：重复代码编写成函数，减少代码量 
void eraser(int r,int &i,int &j,char a[],int w)
{
    if(r==1)
    {
        j++;
        while(a[j+w]!='\0')
        {
            a[j]=a[j+w];
            j++;
        }
        a[j]='\0';
    }
    else
        i++;
}*/

void negatecal(char a[])
{
    int _result=0,i=0,j=0;
    while(i<strlen(a))
    {
        j=i;
        _result=0;
        if(j+1<strlen(a)&&a[j]=='!'&&a[j+1]=='1')
        {
            a[j]='0';
            _result=1;
        }
        else if(j+1<strlen(a)&&a[j]=='!'&&a[j+1]=='0')
        {
            a[j]='1';
            _result=1;
        }
        if(_result==1)
    {
        j++;
        while(a[j+1]!='\0')
        {
            a[j]=a[j+1];
            j++;
        }
        a[j]='\0';
    }
    else
        i++;
    }
}

void bracket(char a[])
{
    int _result=0,i=0,j=0;
    while(i<strlen(a))
    {
        j=i;
        _result=0;
        if(j+2<strlen(a)&&a[j]=='('&&a[j+1]=='1'&&a[j+2]==')')
        {
            a[j]='1';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='('&&a[j+1]=='0'&&a[j+2]==')')
        {
            a[j]='0';
            _result=1;
        }
        if(_result==1)
    {
        j++;
        while(a[j+2]!='\0')
        {
            a[j]=a[j+2];
            j++;
        }
        a[j]='\0';
    }
    else
        i++;
    }
}

void con(char a[])
{
    int _result=0,i=0,j=0;
    while(i<strlen(a))
    {
        j=i;
        _result=0;
        if(j+2<strlen(a)&&a[j]=='0'&&a[j+1]=='*'&&a[j+2]=='0')
        {
            a[j]='0';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='0'&&a[j+1]=='*'&&a[j+2]=='1')
        {
            a[j]='0';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='1'&&a[j+1]=='*'&&a[j+2]=='0')
        {
            a[j]='0';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='1'&&a[j+1]=='*'&&a[j+2]=='1')
        {
            a[j]='1';
            _result=1;
        }
		if(_result==1)
    {
        j++;
        while(a[j+2]!='\0')
        {
            a[j]=a[j+2];
            j++;
        }
        a[j]='\0';
    }
    else
        i++;    
	}
}

void bicond(char a[])
{
    int _result=0,i=0,j=0;
    while(i<strlen(a))
    {
        j=i;
        _result=0;
        if(j+2<strlen(a)&&a[j]=='0'&&a[j+1]=='='&&a[j+2]=='0')
        {
            a[j]='1';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='0'&&a[j+1]=='='&&a[j+2]=='1')
        {
            a[j]='0';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='1'&&a[j+1]=='='&&a[j+2]=='0')
        {
            a[j]='0';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='1'&&a[j+1]=='='&&a[j+2]=='1')
        {
            a[j]='1';
            _result=1;
        }
		if(_result==1)
    {
        j++;
        while(a[j+2]!='\0')
        {
            a[j]=a[j+2];
            j++;
        }
        a[j]='\0';
    }
    else
        i++;  
  }
}

void cond(char a[])
{
    int _result=0,i=0,j=0;
    while(i<strlen(a))
    {
        j=i;
        _result=0;
        if(j+2<strlen(a)&&a[j]=='0'&&a[j+1]=='-'&&a[j+2]=='0')
        {
            a[j]='1';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='0'&&a[j+1]=='-'&&a[j+2]=='1')
        {
            a[j]='1';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='1'&&a[j+1]=='-'&&a[j+2]=='0')
        {
            a[j]='0';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='1'&&a[j+1]=='-'&&a[j+2]=='1')
        {
            a[j]='1';
            _result=1;
        }
        if(_result==1)
    {
        j++;
        while(a[j+2]!='\0')
        {
            a[j]=a[j+2];
            j++;
        }
        a[j]='\0';
    }
    else
        i++;
    }
}

void disconj(char a[])
{
    int _result=0,i=0,j=0;
    while(i<strlen(a))
    {
        j=i;
        _result=0;
        if(j+2<strlen(a)&&a[j]=='0'&&a[j+1]=='+'&&a[j+2]=='0')
        {
            a[j]='0';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='0'&&a[j+1]=='+'&&a[j+2]=='1')
        {
            a[j]='1';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='1'&&a[j+1]=='+'&&a[j+2]=='0')
        {
            a[j]='1';
            _result=1;
        }
        else if(j+2<strlen(a)&&a[j]=='1'&&a[j+1]=='+'&&a[j+2]=='1')
        {
            a[j]='1';
            _result=1;
        }
        if(_result==1)
    {
        j++;
        while(a[j+2]!='\0')
        {
            a[j]=a[j+2];
            j++;
        }
        a[j]='\0';
    }
    else
        i++;
    }
}

/* 修改点4：标准化输入，避免输入格式错误 
void getformula(char a[])
{
    char cc;
    int cnt=0;
    while((cc=getchar())!='\n')
        if((cc>='a'&&cc<='z')||(cc>='A'&&cc<='Z')||cc=='='||cc=='-'||
           cc=='+'||cc=='*'||cc=='!'||cc=='0'||cc=='1'||cc=='('||cc==')')
            a[cnt++]=cc;
}*/

int main()
{
        char pstate[120]={' '},pstate0[120]={' '},charlist[120]={' '},charval[120]={' '};
        char minitem[1024][52]={' '},maxitem[1024][52]={' '},truetable[1024]={' '};
        int i=0,nold=0,nnew=0,nvar=1,nrow=1,j=0,flagsum=1,iminitem=0,imaxitem=0;
        printf("请输入公式(析+,合*,条-,双=,否定!,01):\n");
        gets(pstate0);
        fflush(stdin);

        nold=strlen(pstate0)+1;
        nnew=strlen(pstate0);
        for(i=0;i<nnew;++i)
            pstate[i]=pstate0[i];
        pstate[i]='\0';
        nvar=getalpha(pstate,charlist);
        nrow=1;
        for(i=0;i<nvar;++i)
        {
            charval[i]='0';
            nrow=nrow*2;
        }
        charval[i]='\0';

        printf("\n");
        for(i=0;i<nvar;++i)
            printf("%4c",charlist[i]);
        printf("%15c%s\n",' ',pstate);
        for(i=0;i<nvar;++i)
            printf("%4c",'-');
        printf("|");
        for(i=0;i<60;++i)
            printf("%c",'-');
        printf("\n");

        for(i=0;i<nrow;i++)
        {
            for(j=0;j<nvar;j++)
                printf("%4c",charval[j]);
            pstate[0]='\0';
            fillvalue(pstate0,charlist,nvar,charval,pstate);
            nold=strlen(pstate0)+1;
            nnew=strlen(pstate);
            while(nnew<nold)
            {
                nold=strlen(pstate);
                negatecal(pstate);
                bracket(pstate);
                con(pstate);
                bicond(pstate);
                cond(pstate);
                disconj(pstate);
                nnew=strlen(pstate);
            }
            if(strlen(pstate)==1)
            {
                if(pstate[0]=='1')
                {
                    for(j=0;j<nvar;j++)
                        minitem[iminitem][j]=charval[j];
                    minitem[iminitem][j]='\0';
                    iminitem++;
                }
               /* else if(pstate[0]=='0')
                {
                    for(j=0;j<nvar;++j)
                        maxitem[imaxitem][j]=charval[j];
                    maxitem[imaxitem][j]='\0';
                    imaxitem++;
                }*/
                truetable[i]=pstate[0];
            }

            printf("%20c%s",' ',pstate);
            printf("\n");
            
            flagsum=1;
			for(j=nvar-1;j>=0;--j)
			{
				if(charval[j]=='1'){
					if(flagsum==1){
						charval[j]='0';flagsum=1;
					}
					else {break;
					}
				}
				else if(charval[j]=='0'){
					if(flagsum==1){
						charval[j]='1';flagsum=0;break;
					}
					else {break;
					}
				}
			 } 
			printf("主析取范式：\n");
        for(i=0;i<iminitem;i++)
            if(i==0)
                printf("m%s",minitem[i]);
            else
                printf("+m%s",minitem[i]);
        printf("\n");
        for(i=0;i<iminitem;++i)
            if(i==0)
            {
                printf("(");
                for(j=0;j<nvar;++j)
                {
                    if(j==0)
                        if(minitem[i][j]=='1')
                            printf("%c",charlist[j]);
                        else
                            printf("!%c",charlist[j]);
                    else
                        if(minitem[i][j]=='1')
                            printf("*%c",charlist[j]);
                        else
                            printf("*!%c",charlist[j]);
                }
                printf(")");
            }
            else
            {
                printf("+(");
                for(j=0;j<nvar;++j)
                {
                    if(j==0)
                        if(minitem[i][j]=='1')
                            printf("%c",charlist[j]);
                        else
                            printf("!%c",charlist[j]);
                    else
                        if(minitem[i][j]=='1')
                            printf("*%c",charlist[j]);
                        else
                            printf("*!%c",charlist[j]);
                }
                printf(")");
            }
        printf("\n");}
            
            /* 修改点7：优化为变元赋值的逻辑，优化了运行速度 
            int tmp=sum;
            for(int j=nvar-1;j>=0;--j)
            {
                charval[j]=(tmp%2+'0');
                tmp/=2;
            }
            sum++;
        }
        printf("\n");

        printf("主析取范式：\n");
        for(i=0;i<iminitem;++i)
            if(i==0)
                printf("m%s",minitem[i]);
            else
                printf("+m%s",minitem[i]);
        printf("\n");
        for(i=0;i<iminitem;++i)
            if(i==0)
            {
                printf("(");
                for(j=0;j<nvar;++j)
                {
                    if(j==0)
                        if(minitem[i][j]=='1')
                            printf("%c",charlist[j]);
                        else
                            printf("!%c",charlist[j]);
                    else
                        if(minitem[i][j]=='1')
                            printf("*%c",charlist[j]);
                        else
                            printf("*!%c",charlist[j]);
                }
                printf(")");
            }
            else
            {
                printf("+(");
                for(j=0;j<nvar;++j)
                {
                    if(j==0)
                        if(minitem[i][j]=='1')
                            printf("%c",charlist[j]);
                        else
                            printf("!%c",charlist[j]);
                    else
                        if(minitem[i][j]=='1')
                            printf("*%c",charlist[j]);
                        else
                            printf("*!%c",charlist[j]);
                }
                printf(")");
            }
        printf("\n\n");*/

        /* 修改点8：添加主合取范式的输出，丰富了功能 
        printf("主合取范式：\n");
        for(i=0;i<imaxitem;++i)
            if(i==0)
                printf("M%s",maxitem[i]);
            else
                printf("*M%s",maxitem[i]);
        printf("\n");
        for(i=0;i<imaxitem;++i)
            if(i==0)
            {
                printf("(");
                for(j=0;j<nvar;++j)
                {
                    if(j==0)
                        if(maxitem[i][j]=='0')
                            printf("%c",charlist[j]);
                        else
                            printf("!%c",charlist[j]);
                    else
                        if(maxitem[i][j]=='0')
                            printf("+%c",charlist[j]);
                        else
                            printf("+!%c",charlist[j]);
                }
                printf(")");
            }
            else
            {
                printf("*(");
                for(j=0;j<nvar;++j)
                {
                    if(j==0)
                        if(maxitem[i][j]=='0')
                            printf("%c",charlist[j]);
                        else
                            printf("!%c",charlist[j]);
                    else
                        if(maxitem[i][j]=='0')
                            printf("+%c",charlist[j]);
                        else
                            printf("+!%c",charlist[j]);
                }
                printf(")");
            }
        printf("\n\n");*/
	return 0;
}
