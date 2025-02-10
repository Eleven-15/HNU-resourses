#include <bits/stdc++.h>
using namespace std;



int main()
{
	int n, m;
	cin >> n >> m;
	set<string> w1, w2, union_w, intersection_w;
	string tmp;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		w1.insert(tmp);
	}
	for (int i = 0; i < m; i++)
	{
		cin >> tmp;
		transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		w2.insert(tmp);
	}
	set_intersection(w1.begin(),w1.end(),w2.begin(),w2.end(),inserter(intersection_w,intersection_w.begin()));
	set_union(w1.begin(),w1.end(),w2.begin(),w2.end(),inserter(union_w,union_w.begin()));
	cout << intersection_w.size() << endl << union_w.size();
}
