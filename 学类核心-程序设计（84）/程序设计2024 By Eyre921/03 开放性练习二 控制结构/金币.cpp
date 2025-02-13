#include <iostream>
using namespace std;

int main() {
	int day, coin = 0, i = 1;
	cin >> day;
	while (day > 0) {
		if (day >= i) {
			day -= i;
			coin += i * i;
			i++;
		} else {
			coin += i * day;
			day = 0;
		}
	}
	cout << coin << endl;
}
