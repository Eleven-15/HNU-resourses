#include <bits/stdc++.h>
using namespace std;

struct Word
{
	int all_appear;
	set<int> article_appear;
};

int main()
{
	int n, m, n_tmp;
	cin >> n >> m;
	// i 表示第几篇文章
	// j 表示这篇文章的第几个单词
	vector<Word> Words(m+1);
	for (int i = 0; i < n; i++)
	{
		cin >> n_tmp;
		for (int j = 0; j < n_tmp; j++)
		{
			int tmpw;
			cin >> tmpw;
			Words[tmpw].article_appear.insert(i);
			Words[tmpw].all_appear++;
		}
	}
	for (int i = 1; i <= m; i++)
	{
		cout << Words[i].article_appear.size() << " " << Words[i].all_appear << endl;

	}
}
