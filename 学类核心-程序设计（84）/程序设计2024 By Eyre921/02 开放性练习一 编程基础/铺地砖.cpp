#include <iostream>
using namespace std;

int main() {
	int M, N, x;
	cin >> M >> N;
	x = M * N / 2;
	if ((M * N) % 2 != 0)
		x = x + 1;
	cout << x;
}

