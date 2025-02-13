#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;
	long a, b, k;
	long long dis = 0;

	for (int i = 0; i < t; i++) {
		cin >> a >> b >> k;
		if (k % 2 != 0)
			dis = (a - b) * (k / 2) + a;
		else
			dis = (a - b) * (k / 2);
		cout << dis << endl;
	}
}

