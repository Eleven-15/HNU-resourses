#include <bits/stdc++.h>
using namespace std;

struct person
{
	string name;
	double money;
	int date;
	person(string n, double m, int d) : name(n), money(m), date(d) {}
};

bool cmp(person p1, person p2)
{
	if (p1.money != p2.money)
	{
		return p1.money > p2.money;
	}
	if (p1.date != p2.date)
	{
		return p1.date < p2.date;
	}
	return p1.name < p2.name;
}

int main()
{
	string name;
	double money;
	int date;
	vector<person> v;
	while (1)
	{
		cin >> name;
		if (name == "end") break;
		cin >> money >> date;
		v.emplace_back(name, money, date);
	}
	sort (v.begin(), v.end(), cmp);
	for (auto it : v) cout << it.name << endl;
}
/*
【问题描述】某银行年终举行答谢会，现读入若干客户信息，以"end"作为结束。请按客户余额从大到小给出邀请名单，客户余额相同时按开户日期先后排序，开户日期相同则按照客户姓名进行升序排列。

【输入形式】输入包括若干行，每行包括客户名、客户余额和开户日期(年月日)，以空格作为分隔，最后一行为"end"

【输出形式】输出包括若干行，每行只包含客户名称.

【样例输入】

Alice 5000.0 20220101
Bob 8000.0 20211215
Amy 7000.0 20220205
Charlie 6000.0 20220120
Tom 7000.0 20211130
end
【样例输出】

Bob
Tom
Amy
Charlie
Alice
【样例说明】

根据余额降序，则Bob排在第一位，Tom和Amy余额相同，则开户日期更前的Tom排在前面。

【数据规模】

客户人数大于等于1，小于等于100，客户余额可能包含小数，50%的测试用例数据没有重复，且保证每个测试中的客户姓名互不相同客户名中不包含空格符。

【提示】

正确设置开户日期的数据类型，方便直接比较。
*/
