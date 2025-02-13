#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	int n, manok = 0, womanok = 0, tmp;
	cin >> n;
	for (int i = 0; i < n ; i++)
	{
		cin >> tmp;
		if (tmp >= 178 && tmp <= 180)
		{
			manok++;
		}
	}
	for (int i = 0; i < n ; i++)
	{
		cin >> tmp;
		if (tmp >= 168 && tmp <= 170)
		{
			womanok++;
		}
	}
	cout << manok << " " << womanok;
}
