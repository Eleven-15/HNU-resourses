/*
 * ʵ����
 * ���ó��������Ȼ����
 * by ljkjk
 */

/* �޸ĵ�1������ͷ�ļ���������ͷ�ļ������� */
#include <bits/stdc++.h>
using namespace std;
struct tmd{
    char gs[120],gslast[120],reason[120];
    int nletter,nused,isletter,iscond;
};

void nonoop2(char aa[])
{

    int i=0,j=0;
    while(i<strlen(aa)-2)
    {
        if(i+1<strlen(aa)&&aa[i]=='!'&&aa[i+1]=='!')
        {
            j=i;
            while(j<strlen(aa)-2)
            {
                aa[j]=aa[j+2];
                j++;
            }
            aa[j]='\0';
            break;
        }
        else
           i++;
    }
}

void print(tmd tmrec[],int np)
{
    int i=0;
    for(i=0;i<np;++i)
    {
        if(tmrec[i].isletter==1)
            printf("(%d)\t%sΪ��\t\t\t%s---����\n",i+1,tmrec[i].gs,tmrec[i].reason);
        else if(tmrec[i].iscond==1)
            printf("(%d)\t%s-%sΪ��\t\t\t%s---����ʽ\n",i+1,tmrec[i].gs,tmrec[i].gslast,tmrec[i].reason);
        else
            printf("(%d)\t%sΪ��\t\t\t%s\n",i+1,tmrec[i].gs,tmrec[i].reason);
    }
}

int setreason(tmd tmrec[],int np,string r0,int j0,int j1,int nused0,int iscond0,int isletter0)
{
    char stmpj0[20],stmpj1[20];
    int nlen1=0,j=0,nlenj0=0,nlenj1=0;
    nlen1=r0.length();
    itoa(j0+1,stmpj0,10);
    nlenj0=strlen(stmpj0);
    itoa(j1+1,stmpj1,10);
    nlenj1=strlen(stmpj1);
    if(j0==-1)//�����ǰ��������
    {
        for(j=0;j<nlen1;++j)
            tmrec[np].reason[j]=r0[j];
        tmrec[np].reason[j]='\0';
    }
    else if(j1==-1)
    {
        tmrec[np].reason[0]='(';
        for(j=0;j<nlenj0;++j)
            tmrec[np].reason[j+1]=stmpj0[j];
        tmrec[np].reason[j+1]=')';

        for(j=0;j<nlen1;++j)
            tmrec[np].reason[j+2+nlenj0]=r0[j];
        tmrec[np].reason[j+2+nlenj0]='\0';
    }
    else
    {
        tmrec[np].reason[0]='(';
        for(j=0;j<nlenj0;++j)
            tmrec[np].reason[j+1]=stmpj0[j];
        tmrec[np].reason[j+1]=')';

        tmrec[np].reason[nlenj0+2]='(';
        for(j=0;j<nlenj1;++j)
            tmrec[np].reason[nlenj0+3+j]=stmpj1[j];
        tmrec[np].reason[nlenj0+3+j]=')';

        for(j=0;j<nlen1;++j)
            tmrec[np].reason[nlenj0+nlenj1+4+j]=r0[j];
        tmrec[np].reason[nlenj0+nlenj1+4+j]='\0';
    }
    tmrec[np].nused=nused0;
    tmrec[np].iscond=iscond0;
    tmrec[np].isletter=isletter0;
}

/* �޸ĵ�2��������inputprimary������setreason������λ�ã�����˱�������� */
int inputprimary(tmd gs0[])
{
    tmd tmp;
    char pstate[120];
    /* �޸ĵ�3����string�滻�ַ����飬�����˾��� */
    string r0="ǰ������";
    string r1="ԭ������������";
    string r2="˫��������������ʽ";
    string r3="��ȡʽת��Ϊ����ʽ";

    int i=0,j=0,nlen=0,k=0;
    int i0=0;
    printf("����һ��ǰ�������밴�س�������ֱ�ӻس������\n��+,��-,��-,˫=,��!\nǰ����ֻ��Ϊ˫����������������ȡʽ��\n��Ϊ�����������ĺ�ȡ������������ǰ�ᣬ����������ǰ�����룺\n");
    while(1)
    {
        gets(pstate);
        nlen=strlen(pstate);
        if(nlen==0)
            break;
        if(nlen==1)
        {
            gs0[i].nletter=strlen(pstate);
            gs0[i].gs[0]=pstate[0];
            gs0[i].gs[1]='\0';
            gs0[i].gslast[0]='\0';
            setreason(gs0,i,r0,-1,-1,0,0,1);
        }
        else if(nlen==2&&pstate[0]=='!')
        {
            gs0[i].nletter=strlen(pstate);
            gs0[i].gs[0]=pstate[0];
            gs0[i].gs[1]=pstate[1];
            gs0[i].gs[2]='\0';
            gs0[i].gslast[0]='\0';
            setreason(gs0,i,r0,-1,-1,0,0,1);
        }
        else
        {
            for(j=0;j<nlen;++j)
            {
                if(pstate[j]=='-')
                {
                    gs0[i].nletter=strlen(pstate);
                    for(k=0;k<j;++k)
                        gs0[i].gs[k]=pstate[k];
                    gs0[i].gs[k]='\0';
                    for(k=j+1;k<nlen;++k)
                        gs0[i].gslast[k-j-1]=pstate[k];
                    gs0[i].gslast[k-j-1]='\0';
                    setreason(gs0,i,r0,-1,-1,0,1,0);
                    i++;
                    gs0[i].nletter=gs0[i-1].nletter;
                    gs0[i].gslast[0]='!';
                    for(k=0;k<j;++k)
                        gs0[i].gslast[k+1]=pstate[k];
                    gs0[i].gslast[k+1]='\0';
                    nonoop2(gs0[i].gslast);

                    gs0[i].gs[0]='!';
                    for(k=j+1;k<nlen;++k)
                        gs0[i].gs[k-j-1+1]=pstate[k];//>??????
                    gs0[i].gs[k-j-1+1]='\0';
                    nonoop2(gs0[i].gs);
                    setreason(gs0,i,r1,i-1,-1,0,1,0);
                    break;
                }
                else if(pstate[j]=='=')
                {
                    gs0[i].nletter=strlen(pstate);
                    for(k=0;k<strlen(pstate);++k)
                        gs0[i].gs[k]=pstate[k];
                    gs0[i].gs[k]='\0';
                    gs0[i].gslast[0]='\0';
                    setreason(gs0,i,r0,-1,-1,0,0,0);
                    i++;
                    gs0[i].nletter=strlen(pstate);
                    for(k=0;k<j;++k)
                        gs0[i].gslast[k-j-1]=pstate[k];
                    gs0[i].gslast[k-j-1]='\0';
                    setreason(gs0,i,r2,i-1,-1,0,1,0);
                    i++;
                    gs0[i].nletter=gs0[i-1].nletter;
                    for(k=0;k<j;++k)
                        gs0[i].gslast[k]=pstate[k];
                    gs0[i].gs[k-j-1]='\0';
                    setreason(gs0,i,r2,i-2,-1,0,1,0);
                    break;
                }
                else if(pstate[j]=='+')
                {
                    gs0[i].nletter=strlen(pstate);
                    for(k=0;k<strlen(pstate);++k)
                        gs0[i].gs[k]=pstate[k];
                    gs0[i].gs[k]='\0';
                    gs0[i].gslast[0]='\0';
                    setreason(gs0,i,r0,-1,-1,0,0,0);
                    i++;
                    gs0[i].nletter=strlen(pstate);
                    gs0[i].gs[0]='!';
                    for(k=0;k<j;++k)
                        gs0[i].gs[k+1]=pstate[k];
                    gs0[i].gs[k+1]='\0';
                    for(k=j+1;k<nlen;++k)
                        gs0[i].gslast[k-j-1]=pstate[k];
                    gs0[i].gslast[k-j-1]='\0';
                    setreason(gs0,i,r3,i-1,-1,0,1,0);
                    nonoop2(gs0[i].gs);
                    i++;
                    gs0[i].nletter=strlen(pstate);
                    for(k=0;k<j;++k)
                        gs0[i].gslast[k]=pstate[k];
                    gs0[i].gslast[k]='\0';
                    gs0[i].gs[0]='!';
                    for(k=j+1;k<nlen;++k)
                        gs0[i].gs[k-j-1+1]=pstate[k];
                    gs0[i].gs[k-j-1+1]='\0';
                    setreason(gs0,i,r3,i-2,-1,0,1,0);
                    nonoop2(gs0[i].gs);
                    break;
                }
            }
            if(j>=nlen)
            {
                gs0[i].nletter=strlen(pstate);
                for(k=0;k<nlen;++k)
                    gs0[i].gs[k]=pstate[k];
                gs0[i].gs[k]='\0';
                gs0[i].gslast[0]='\0';
                setreason(gs0,i,r0,-1,-1,0,0,0);
            }
        }
        i++;
    }
    nlen=i;
    for(i=0;i<nlen-1;++i)
    {
        k=i;
        /* �޸ĵ�4����nlen-1��Ϊnlen���������һ��Ԫ���޷����� */
        for(j=i+1;j<nlen;++j)
            if(gs0[k].nletter>gs0[j].nletter)
                k=j;
        /* �޸ĵ�5����swap����м�Ԫ������������ֵ��ʹ������ */
        if(k>i) swap(gs0[i],gs0[k]);
    }
    return nlen;
}


int main()
{
    /* �޸ĵ�6���������� */
    while(1)
    {
        tmd gs0[100];
	char result0[128];
	tmd tmrec[1024];
	char stmp[128];
	char lastreason[128]="";
	string r01="��������";
	int i=0,j=0,k=0;
	int np=1,np0=0,is0k=0;
	int i0=0,nposletter=0,nposcond=0;

	np0=inputprimary(gs0);
	printf("����Ҫ����Ľ��ۣ�����ֻ�������֣�\n��������ʽ����ȡʽ�����ֹ�ת��Ϊ��������ǰ����Ϊ����ǰ�᣺\n");
    gets(result0);
    fflush(stdin);

    for(i=0;i<np0;++i)
        tmrec[i]=gs0[i];

    np=i;
    nposletter=0;
    nposcond=0;
    is0k=0;
    i0=-1;
    while(1)
    {
        i=i0+1;
        while(i<np&&tmrec[i].isletter!=1)
            i++;
        if(i>=np)
            break;
        i0=i;
        nposletter=i;
        strcpy(stmp,tmrec[i].gs);
        np0=np-1;
        while(np>np0)
        {
            np0=np;
            for(i=0;i<np;++i)
                if(tmrec[i].iscond==1&&tmrec[i].nused==0)
                    break;
            if(i==np)
                break;
            while(i<np)
            {
                if(tmrec[i].iscond==1)
                    if((strcmp(lastreason,tmrec[i].reason)!=0)||
                       (strcmp(lastreason,tmrec[i].reason)==0&&tmrec[i].reason[0]!='('))
                        if(strcmp(tmrec[i].gs,stmp)==0)
                        {
                            strcpy(lastreason,tmrec[i].reason);
                            tmrec[nposletter].nused++;
                            tmrec[i].nused++;
                            strcpy(stmp,tmrec[i].gslast);
                            strcpy(tmrec[np].gs,stmp);
                            tmrec[np].gslast[0]='\0';
                            setreason(tmrec,np,r01,nposletter,i,0,0,1);
                            nposletter=np;
                            np++;
                            if(strcmp(result0,stmp)==0)
                            {
                                is0k=1;
                                break;
                            }
                        }
                i++;
            }
        }
        if(is0k==1)
            break;
    }
    if(is0k==1)
        printf("�������������������£�\n");
    else
        printf("���������������������:\n");
    print(tmrec,np);
    printf("\n\n");
    }

	return 0;
}
