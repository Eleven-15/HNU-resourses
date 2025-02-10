#include <bits/stdc++.h>
using namespace std;

long long  gx(long long num)
{
	char s[20];
	int l = 0;
	while (num > 0)
	{
		s[l++] = (num % 10) + '0';
		num /= 10;
	}
	reverse(s, s + l);
	
	int digits_sum[20];
	digits_sum[0] = s[0] - '0';
	for (int i = 1; i < l; i++)
	{
		digits_sum[i] = digits_sum[i - 1] + s[i] - '0';
	}
	
	long long ans = LLONG_MAX;
    for (int i = 0; i < l; i++) {
        long long dx1 = 0, dx2 = 0;
        dx1 = digits_sum[i];
        dx2 = digits_sum[l-1] - digits_sum[i];
        ans = min(ans, abs(dx1 - dx2));
    }
	return ans;
}



int main()
{
	int n;
	cin >> n;
	long long left, right;

	for (int i = 0; i < n; i++)
	{
		long long ans = 0;
		cin >> left >> right;
		size_t width = right - left;
		for (size_t j = 0; j <= width; j++)
		{
			ans += gx(j + left);
		}
		cout << ans << endl;
	}
}
