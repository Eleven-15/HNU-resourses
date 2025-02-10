#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
	int n, m, p, q;
	cin >> n >> m >> p >> q;
	vector<int> j1(m * n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> j1[i * m + j];
		}
	}
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < q; j++) {
			cout << j1[i * q + j] << " ";
		}
		cout << endl;
	}
}
