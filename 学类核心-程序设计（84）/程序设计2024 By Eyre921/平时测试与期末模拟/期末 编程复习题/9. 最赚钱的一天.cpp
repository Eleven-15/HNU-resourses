#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	map<int, int> days;
	int cb, xs;
	for (int i = 1; i <= n; i++)
	{
		cin >> cb >> xs;
		days.insert({xs - cb, i});
	}
	auto it = days.rbegin();
	cout <<it->second;
}
