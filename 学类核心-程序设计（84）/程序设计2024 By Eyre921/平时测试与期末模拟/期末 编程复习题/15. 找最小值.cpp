#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t ;
	cin >> t;
	int n;
	int minnum = INT_MAX;
	while (t--)
	{
		cin >> n;
		minnum = min(minnum,n);
	}
	cout << minnum;
}
/*
【问题描述】有一个包含任意n个整数的序列，请找出最小值并打印。

【输入形式】第一行输入n，第二行输入n个整数，用空格隔开。

【输出形式】输出最小数的值。

【样例输入】

10
34 91 83 0 29 93 57 -12999 88 72
【样例输出】

-12999
【样例说明】这10个整数中最小值为-12999。
*/
