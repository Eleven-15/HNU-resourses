#include <iostream>
using namespace std;

int main() {
	string x, y;

	for (int i = 0; i < 6; i++) {
		cin >> x[i] >> y[i];
	}

	for (int i = 1; i < 6; i++) {
		if (x[i] == x[0] || y[i] == y[0]) {
			cout << "YES";
			return 0;
		}
	}
	cout << "NO";
}

