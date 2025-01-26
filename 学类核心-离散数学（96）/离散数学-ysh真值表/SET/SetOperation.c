#include <stdio.h>
#include <string.h>
#define SIZE 32
#define LENGTH 20
#define LF printf("\n");
//#define DEBUG
#define FILEIO
char USET[SIZE][LENGTH];int NUSET;

void OutputSet(int CStr,char SET[][LENGTH]){
     int i=0;
     printf("{");
     while(CStr){
          if(CStr&1){printf("%s",SET[i]);if(CStr>1)printf(",");}
          CStr>>=1;
          i++;}
     printf("}");}

void OutputPowerSet(int CStr){
     char SET[SIZE][LENGTH];int i,n,t=CStr;
     i=n=0;
     while(t){
          if(t&1)strcpy(SET[n++],USET[i]);
          t>>=1;
          i++;}
     n=1<<n;
     printf("Subsets of set ");OutputSet(CStr,USET);printf(" are:\n");
     for(i=0;i<n;++i) 
         OutputSet(i,SET);
     LF }
     
void OutputProductSet(int Sa,int Sb){
     int i,j,m,n,t;
     printf("Product set of set ");OutputSet(Sa,USET);
     printf(" and set ");OutputSet(Sb,USET);printf("is:\n{");
     m=n=0;
     t=Sa;while(t){m++;t>>=1;}
     t=Sb;while(t){n++;t>>=1;}
     for(i=0;i<m;++i)
        if(Sa&(1<<i)){
           for(j=0;j<n;++j)
               if(Sb&(1<<j))
                  printf("(%s,%s)%c",USET[i],USET[j],i==m-1&&j==n-1?'}':',');
           LF}
     LF }

int FindElement(char s[LENGTH]){
    int i;
    for(i=0;i<NUSET;++i)
      if(!strcmp(s,USET[i]))return i;
    strcpy(USET[NUSET++],s);
    return NUSET-1;}

int SET_TO_INT(char *ss){
    int i,t,k;char s[LENGTH];
    i=k=0;
    while(sscanf(ss+i,"%s",s)!=EOF){
         t=FindElement(s);
         k|=1<<t;
         i+=strlen(s);}
    return k;}
    
int main(int argc,char **argv){
    int Sa,Sb,k,n;char s[1000];
#ifdef FILEIO
    freopen(argv[1],"r",stdin);
    freopen(argv[2],"w",stdout);
#endif
    while(1){
    NUSET=0;         
#ifdef DEBUG
    printf("Please input elements of set A in one line,seprated by blank(s),the length of each elements not exceed %d\n",LENGTH);
#endif
    if(gets(s)==NULL)break;
    Sa=SET_TO_INT(s);
#ifdef DEBUG
    printf("Please input elements of set B in one line,seprated by blank(s),the length of each elements not exceed %d\n",LENGTH);
#endif
    if(gets(s)==NULL)break;
    Sb=SET_TO_INT(s);
#ifdef DEBUG
    printf("Please input elements of universal set and not in A and not in B in one line,seprated by blank(s),the length of each elements not exceed %d\n",LENGTH);
#endif
    if(gets(s)==NULL)break;
    SET_TO_INT(s);
    n=NUSET;
    k=(1<<n)-1;
    printf("The Universal Set is ");OutputSet(k,USET);LF
    printf("The Union of A and B is ");OutputSet(Sa|Sb,USET);LF
    printf("The Intersection of A and B is ");OutputSet(Sa&Sb,USET);LF
    printf("The Complement of A is ");OutputSet(~Sa&k,USET);LF
    printf("The Complement of B is ");OutputSet(~Sb&k,USET);LF
    printf("The Difference of A - B is ");OutputSet(Sa&(~Sb),USET);LF
    printf("The Difference of B - A is ");OutputSet(Sb&(~Sa),USET);LF
    printf("The Symmetrical Difference of A and B is ");OutputSet(Sb^Sa,USET);LF
    OutputPowerSet(Sa);
    OutputPowerSet(Sb);    
    OutputPowerSet(k); 
    OutputProductSet(Sa,Sb);
    OutputProductSet(Sb,Sa);
         }
    return 0;}
              
           
