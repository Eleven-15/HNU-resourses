#include <bits/stdc++.h>
using namespace std;


int main()
{
	int n, tmp;
	cin >> n;
	vector<int> v;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		v.emplace_back(tmp);
	}
	sort(v.begin(), v.end(), greater<int>());
	for (auto it : v) cout << it << " ";

}
/*
【问题描述】

    输入不超过100个整数，范围在[0,999]之间，互不相同，请按从大到小排序后输出，每个空格隔开，最后一个不能有空格。

【输入形式】

    输入包含两行。

    第一行输入正整数n， n<=100。

    第二行输入n个整数，整数的范围在[0,999]之间，整数之间互不相同，用空格隔开。

【输出形式】

    输出从大到小排序后的整数数组，每两个元素之间用空格隔开。注意最后一个元素之后没有空格。
【样例输入】

3
5 6 7
【样例输出】

7 6 5
*/
