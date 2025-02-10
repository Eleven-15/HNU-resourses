#include <iostream>
#include <limits>

using namespace std;

int main() {
	int n;
	cin >> n;

	int numbers[100];

	for (int i = 0; i < n; ++i) {
		cin >> numbers[i];
	}

	int minValue = numbers[0];

	for (int i = 0; i < n; ++i) {
		if (numbers[i] < minValue) {
			minValue = numbers[i];
		}
	}

	cout << minValue << endl;

	return 0;
}

