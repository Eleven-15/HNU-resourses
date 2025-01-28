#include<stdio.h>
int main()
{
    int i=0,j;
    scanf("%d",&j);
    while(j>0)
    {
        if(j%2==1){i=i+j;}
        scanf("%d",&j);
    }
    printf("%d",i);
    return 0;
}

