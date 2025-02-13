#include <iostream>
#include <cmath>
using namespace std;

// 计算一个数的所有约数（不包括自身）的和
int sum_D(int num) {
	int sum = 0;

	for (int i = 1; i <= sqrt(num); ++i) {
		if (num % i == 0) {
			sum += i;
			if (i != 1 && i != num / i) {
				sum += num / i;
			}
		}
	}
	return sum;
}

int main() {
	int S, s1 = 0;
	cin >> S;

	while (S != sum_D(s1)) {
		S++;
		s1 = sum_D(S);
	}

	cout << S << " " << sum_D(S);
	return 0;
}

