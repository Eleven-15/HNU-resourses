#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, tmp;
	cin >> n;
	map<int, int, greater<int>> m;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		m[tmp]++;
	}
	for (auto& it :m) {
		cout << it.first << " " << it.second << endl;
	}
}
/*
【问题描述】已知全省有n个学生参加计算机等级考试，其成绩值均为0-100之间的整数值，且成绩中有很多值重复出现，统计各个分数值重复出现的次数。

【输入形式】

　　输入的第一行包含一个整数n。

　　第二行包含n个整数，用空格分隔，分别表示n个整数。

【输出形式】

　　输出多行数据，每行数据包含2个整数，分别表示分数和出现次数，以空格分开，按分数从高到底顺序输出。

【样例输入】

    10

    98 88 77 65 34 65 86 77 91 82
【样例输出】

    98 1

    91 1

    88 1    

    86 1

    82 1

    77 2

    65 2

    34 1
【样例说明】
*/
