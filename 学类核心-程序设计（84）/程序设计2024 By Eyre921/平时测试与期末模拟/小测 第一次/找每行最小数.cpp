#include <iostream>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	int matrix[n][m];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> matrix[i][j];
		}
	}

	for (int i = 0; i < n; ++i) {
		int minVal = matrix[i][0];
		for (int j = 0; j < m; ++j) {
			if (matrix[i][j] < minVal) {
				minVal = matrix[i][j];
			}
		}
		cout << minVal << endl;
	}

	return 0;
}

