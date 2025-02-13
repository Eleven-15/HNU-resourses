#include <bits/stdc++.h>
using namespace std;


int main()
{
	int n, m;
	cin >> n >> m;

	for (int i = 0 ; i < n; i++)
	{
		vector<int> v;
		for (int j = 0; j < m; j++)
		{
			int tmp;
			cin >> tmp;
			v.emplace_back(tmp);

		}
		sort(v.begin(), v.end());
		cout << v[0] << endl;
		v.clear();
	}

}
/*

【问题描述】有n行整数序列，每行包含m个整数，请找出每行最小值并打印。n和m的值不大于100。

【输入形式】第一行输入n，和m，接下里n行，每行输入m个整数，用空格隔开。

【输出形式】输出每行最小数的值。

【样例输入】

2  5
34 91 83 0 29
93 57 -12999 88 72
【样例输出】

0
-12999
【样例说明】

【评测用例规模与约定】n的取值范围为[1,100]。这n个整数各不相同。
*/
