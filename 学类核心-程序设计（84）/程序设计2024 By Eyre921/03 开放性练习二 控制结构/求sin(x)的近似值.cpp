#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

long double maclaurinSin(long double x) {
	const long double pi = 3.1415926535, tolerance = 0.5e-13;
	const long double twoPi = 2 * pi;

	while (x > twoPi) {
		x -= twoPi;
	}
	while (x < -twoPi) {
		x += twoPi;
	}

	long double term = x, sum = x;
	int n = 1;
	while (abs(term) >= tolerance) {
		term *= -x * x / ((2 * n) * (2 * n + 1));
		sum += term;
		n++;
	}

	return sum;
}

int main() {
	long double x;
	cin >> x;
	cout << fixed << setprecision(13) << maclaurinSin(x) << endl;
	return 0;
}
