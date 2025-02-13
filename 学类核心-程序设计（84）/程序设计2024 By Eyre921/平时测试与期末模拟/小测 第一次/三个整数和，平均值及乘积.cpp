#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int a, b, c;
	cin >> a >> b >> c;

	int sum = a + b + c;

	double average = sum / 3.0;

	int product = a * b * c;

	cout << a << "+" << b << "+" << c << "=" << sum << endl;
	cout << "平均值是" << fixed << setprecision(2) << average << endl;
	cout << a << "*" << b << "*" << c << "=" << product << endl;

	return 0;
}

