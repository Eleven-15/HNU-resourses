#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> v(n, vector<int>(m, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; j++) {
			cin >> v[i][j];
		}
	}
	for (int i = 0; i < n; ++i) {
		cout << *min_element(v[i].begin(), v[i].end()) << endl;
	}
}

