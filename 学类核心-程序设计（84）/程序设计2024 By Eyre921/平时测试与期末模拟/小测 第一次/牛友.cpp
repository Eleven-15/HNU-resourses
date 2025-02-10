#include <iostream>
using namespace std;

int getProperDivisorSum(int n) {
	int sum = 0;
	for (int i = 1; i <= n / 2; ++i) {
		if (n % i == 0) {
			sum += i;
		}
	}
	return sum;
}


pair<int, int> findFriendCows(int S) {
	for (int n = S; n <= 18000; ++n) {
		int friendCow = getProperDivisorSum(n);
		if (friendCow > n) {
			if (getProperDivisorSum(friendCow) == n) {
				return {n, friendCow};
			}
		}
	}
	return {-1, -1};
}

int main() {
	int S;
	cin >> S;
	pair<int, int> result = findFriendCows(S);
	cout << result.first << " " << result.second << endl;
	return 0;
}

