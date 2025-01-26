#include <stdio.h>
void main()
{
    int a;
    int b;
    scanf("%d", &a);
    scanf("%d", &b);
    int c;
    for (c = 0; a > 0; c++)
    {
        a = a - b;
    }
    printf("%d\n", c);
    printf("%d\n", a);
}
