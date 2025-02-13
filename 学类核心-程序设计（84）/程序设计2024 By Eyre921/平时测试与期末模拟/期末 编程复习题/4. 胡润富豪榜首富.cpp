#include <bits/stdc++.h>
using namespace std;
struct Per
{
	string name;
	long long money;
};
bool compare(Per P1,Per P2){
	return P1.money > P2.money;
}
int main()
{
	int n;
	string name;
	long long money;
	cin >> n;
	vector<Per> P;
	for (int i = 0; i < n; i++)
	{
		cin >> name >> money;
		P.emplace_back(Per{name, money});
	}
	sort(P.begin(),P.end(),compare);
	cout << P[0].name << " " << P[0].money;
	
}
