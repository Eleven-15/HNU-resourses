#include <stdio.h>

int CountDigit( int number, int digit );

int main()
{
    int number, digit;

    scanf("%d %d", &number, &digit);
    printf(" %d\n" ,CountDigit(number, digit));

    return 0;
}

/* ��Ĵ��뽫��Ƕ������ */
int CountDigit( int number, int digit )
{
    int count=0;
    if(number<0){
        number=-number;
    }
    else if(number==0){
        if(number==digit){
            count++;
        }
    }
    while(number>0){
        if((number%10)==digit){
            count++;
        }
        number/=10;
    }
    return count;
}

