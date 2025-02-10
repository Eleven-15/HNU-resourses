#include <bits/stdc++.h>
using namespace std;
bool is_h(string s)
{
	string s1 = s;
	reverse(s1.begin(), s1.end());
	if (s1 == s)
	{
		return true;
	}
	return false;
}

int main()
{
	string s;
	cin >> s;
	int maxlen = 0;
	for (int i = 0; i < (int)s.size(); i++)
	{
		for (int j = i; j < (int)s.size() ; j++)
		{
			if (is_h(s.substr(i, j - i + 1)))
			{
				maxlen = max(maxlen, j - i + 1);
			}
		}
	}
	cout << maxlen;

}
