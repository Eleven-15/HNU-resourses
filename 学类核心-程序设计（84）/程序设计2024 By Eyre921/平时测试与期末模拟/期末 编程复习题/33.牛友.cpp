#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll cal_ys(int n)
{
	ll ans = 0;
	for (ll i  = 1; i  < n; i++)
	{
		if (n % i == 0) ans += i;
	}
	return ans;
}

int main()
{
	int S;
	cin >> S;
	for (int i = S; i <= 18000; i++)
	{
		// n1 = 284
		// n2 = 206
		ll n1 = cal_ys(i);
		ll n2 = cal_ys(n1);
		if (n2== i)
		{
			cout << i <<" "<< n1;
			return 0;
		}
	}
}
