#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int x[4];
	cin >> x[0] >> x[1] >> x[2] >> x[3];

	sort(x, x + 4);

	int a = x[3] - x[2];
	int b = x[3] - x[1];
	int c = x[3] - x[0];

	cout << a << " " << b << " " << c << endl;

	return 0;
}

