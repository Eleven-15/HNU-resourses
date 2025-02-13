#include <iostream>
#include <bitset>
using namespace std;

int main() {
	int num[2];
	string num_b[2];
	for (int i = 0; i < 2; i++) {
		cin >> num[i];
		bitset<32> binary(num[i]);
		num_b[i] = binary.to_string();
	}
	int counter = 0;
	for (int i = 0; i < 32; i++) {
		if (num_b[0][i] != num_b[1][i])
			counter++;
	}
	cout << counter;
	return 0;
}
