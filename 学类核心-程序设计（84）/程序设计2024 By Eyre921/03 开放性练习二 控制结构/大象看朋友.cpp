#include <iostream>
#include <vector>
using namespace std;

int min_steps(int x, int m) {
	int target = abs(x);  // 目标位置的绝对值
	vector<int> steps;    // 可用的奇数步长
	for (int i = 1; i <= 2 * m - 1; i += 2) {
		steps.push_back(i);  // 生成所有步长
	}

	int step_count = 0;  // 记录步数
	int current_pos = 0; // 当前所在位置

	// 从最大步长开始，使用贪心策略接近目标
	while (current_pos < target) {
		for (int i = steps.size() - 1; i >= 0; --i) {
			if (current_pos + steps[i] <= target) {
				current_pos += steps[i];  // 尽量使用最大的步长
				step_count++;
				break;
			}
		}
	}

	return step_count;
}

int main() {
	int x, m;
	// 读取输入
	cin >> x >> m;
	// 输出最小步数
	cout << min_steps(x, m) << endl;
	return 0;
}

