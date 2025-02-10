#include <iostream>
using namespace std;

int main()
{
	int num = 1, num2;
	cin >> num2;

	while (true) {
		if (num2 / 10 != 0)
			cout << num2 << " ";
		while (num2 != 0) {
			if (num2 % 10 != 0)
				num *= num2 % 10;
			num2 /= 10;
		}
		if (num / 10 == 0) {
			cout << num;
			return 0;
		}
		num2 = num;
		num = 1;
	}
}

