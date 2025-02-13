#include <iostream>
using namespace std;

int main() {
	int k, n, w, c = 0, borrow;
	cin >> k >> n >> w;
	for (int i = 1; i <= w; i++) {
		c += i * k;
	}
	borrow = c - n;
	if (borrow > 0)
		cout << borrow;
	else
		cout << "0";
}

