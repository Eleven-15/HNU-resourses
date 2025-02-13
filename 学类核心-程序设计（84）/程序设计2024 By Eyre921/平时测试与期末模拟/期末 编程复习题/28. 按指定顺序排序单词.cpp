#include <bits/stdc++.h>
using namespace std;


int main()
{
	map<int, string> m;
	string s;
	getline(cin, s);
	stringstream ss(s);
	while (ss)
	{
		string tmp;
		ss >> tmp;
		if (tmp.empty()) continue;
		int num = tmp.back();
		tmp.pop_back();
		m.insert({num, tmp});
	}
	for (auto it : m) cout << it.second << " ";
}
/*
【问题描述】

        一个 句子 指的是一个序列的单词用单个空格连接起来，且开头和结尾没有任何空格。每个单词都只包含小写或大写英文字母。

        我们可以给一个句子添加 从 1 开始的单词位置索引 ，并且将句子中所有单词 打乱顺序 。

        比方说，句子 "This is a sentence" 可以被打乱顺序得到 "sentence4 a3 is2 This1" 或者 "is2 sentence4 This1 a3" 。

        给你一个 打乱顺序 的句子 s ，它包含的单词不超过 9 个，请你重新构造并得到原本顺序的句子。



【输入形式】

        输入只有一行字符串 s， 其中：

        2 <= s的长度 <= 200

        s 只包含小写和大写英文字母、空格以及从 1 到 9 的数字。

        s 中单词数目为 1 到 9 个。

        s 中的单词由单个空格分隔。

        s 不包含任何前导或者后缀空格。


【输出形式】

        只有一行，原本的句子，不包括数字，不能有前导空格或后缀空格
【样例输入】

is2 sentence4 This1 a3
【样例输出】

This is a sentence
*/
