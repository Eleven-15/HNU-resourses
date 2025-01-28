#include <iostream>
#include <vector>

std::vector<long> a;

long comp(int n)
{
    if (a[n] > 0)
        return a[n];

    long ans = 1;
    for (int i = 1; i <= n / 2; i++)
    {
        ans += comp(i);
    }
    a[n] = ans;
    return ans;
}

int main()
{
    int n;
    while (std::cin >> n)
    {
        a.assign(n + 1, 0);
        a[1] = 1;
        std::cout << comp(n) << std::endl;
    }
    return 0;
}
