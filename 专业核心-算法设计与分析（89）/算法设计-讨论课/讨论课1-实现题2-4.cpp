#include <bits/stdc++.h>

long *a;

long comp(int n)
{
    long ans = 1;
    if (a[n] > 0)
        return a[n];
    for (int i = 1; i <= n / 2; i++)
    {
        ans += comp(i);
        if ((i > 10) && (2 * (i / 10) <= (i % 10))) // x/10<=(x%10)/2
            ans -= a[i / 10];
    }
    a[n] = ans;
    return ans;
}
int main()
{
    int n;
    while (std::cin >> n)
    {
        a = (long *)new long[n];
        memset(a, 0, n * sizeof(long));
        a[1] = 1;
        std::cout << comp(n) << std::endl;
    }
    free(a);
    return 0;
}
