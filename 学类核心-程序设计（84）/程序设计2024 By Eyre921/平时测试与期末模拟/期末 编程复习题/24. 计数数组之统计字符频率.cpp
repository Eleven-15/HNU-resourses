#include <bits/stdc++.h>
using namespace std;
int dp[80];

int main()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	map<char, int, greater<char>> m;
	for (auto c : s) m[c]++;
	for (auto it: m ) cout << it.first << ":" << it.second << " ";
}
/*
24. 计数数组之统计字符频率
【问题描述】

    输入不超过60个字符，仅包含数字、标点符号和字母，不包含换行、空格、制表符和'\0'等特殊字符，

    请统计每个字符出现的频率，按字符在ASCII表中的顺序从大到小输出，以字符:频率的方式，相邻两对数据之间用单个空格间隔。

【输入形式】

    输入包含两行。

    第一行是正整数n（n<=60), 

    第二行输入n个字符，仅包含数字、标点符号和字母。

【输出形式】

    按字符在ASCII表中的顺序从大到小输出，以字符:频率的方式，相邻两对数据之间用单个空格间隔。
【样例输入】

12
Code1019.cpp
【样例输出】

p:2 o:1 e:1 d:1 c:1 C:1 9:1 1:2 0:1 .:1
【样例说明】

先统计每个字母出现的频率，再按ASCII码值，从大到小输出。
*/
