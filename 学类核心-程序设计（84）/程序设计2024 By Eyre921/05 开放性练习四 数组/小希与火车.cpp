#include <iostream>
using namespace std;

int main() {
	int T;
	cin >> T;

	for (int j = 0; j < T; j++) {
		int sum = 0, L, v, l, r;
		cin >> L >> v >> l >> r;

		// 从v开始，每次增加v，直到L为止，遍历所有灯笼位置
		for (int i = v; i <= L; i += v) {
			// 如果当前位置不在火车停留的区间内，则可以看到灯笼
			if (i < l || i > r) {
				sum++;
			}
		}

		// 输出能看到的灯笼数量
		cout << sum << endl;
	}

	return 0;
}
