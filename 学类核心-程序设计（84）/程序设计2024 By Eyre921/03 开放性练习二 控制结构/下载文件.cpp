#include <iostream>
using namespace std;
int money_comp(int N, int freetime);

int main() {
	int group_n, N, K;
	cin >> group_n;
	for (int i = 0; i < group_n; i++) {
		cin >> N >> K;
		cout << money_comp(N, K) << endl;
	}
	// 每组数据输入N K
	return 0;
}

int money_comp(int N, int freetime) {
	int data[N][2];
	int fee = 0;

	for (int j = 0; j < N; j++) {
		cin >> data[j][0] >> data[j][1];
		if (freetime >= data[j][0]) {
			freetime -= data[j][0];
		} else {
			fee += (data[j][0] - freetime) * data[j][1];
			freetime = 0;
		}
	}

	return fee;
}