#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	n--;
	vector<string> v;
	string ans;
	for (int i = 0; i < n; i++)
	{
		cin >> ans;
		v.emplace_back(ans);
	}
	cin >> ans;
	int res = 0;
	for (int i = 0; i < n; i++)
	{
	 for (int j = 0; j < n;j++){
	 	if (v[i]+v[j]==ans && i != j) res++;
	 }
	}
	cout << res;
}
/*
【问题描述】

给你一个数字字符串数组 nums 和一个数字字符串 target ，请你返回 nums[i] + nums[j] （两个字符串连接）结果等于 target 的下标 (i, j) （需满足 i != j）的数目。字符串数目不超过100

【输入格式】

输入格式：输入一个n，接着n行字符串，前（n-1）行字符串为nums的元素（即nums有n-1个字符串），第n行是目标字符串target

题目保证字符串不包含空格、制表符、换行符等特殊字符。


【输出格式】

符合条件的数量

【输入样例】

5
777
7
77
77
7777


【输出样例】

4
【样例说明】

解释：符合要求的下标对包括：

- (0, 1)："777" + "7"

- (1, 0)："7" + "777"

- (2, 3)："77" + "77"

- (3, 2)："77" + "77"
*/
