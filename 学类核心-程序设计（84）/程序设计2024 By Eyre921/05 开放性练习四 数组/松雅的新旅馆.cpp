#include <iostream>
#include <vector>
#include <algorithm> // 引入 STL 的 sort 库
using namespace std;

// 自定义比较函数，按建筑的起点进行升序排序
bool compare(const vector<int>& a, const vector<int>& b) {
	return a[0] < b[0]; // 如果 类与对象 的起点小于 b 的起点，则返回 true
}

int main() {
	int n, t;
	cin >> n >> t;

	// 使用 vector 存储已有建筑的信息
	vector<vector<int>> buildings(n, vector<int>(2));
	int result = 2 * n; // 初始值设为 2 倍建筑数

	// 输入每座建筑的中心点和横边长
	for (int i = 0; i < n; i++) {
		cin >> buildings[i][0] >> buildings[i][1];
	}

	// 使用自定义比较函数对建筑按起点排序
	sort(buildings.begin(), buildings.end(), compare);

	// 比较相邻建筑的间距与旅馆的横边长，找出可建位置
	for (int i = 1; i < n; i++) {
		double midDiff = (buildings[i][1] + buildings[i - 1][1]) / 2.0;

		// 判断是否可以在两座建筑之间建旅馆
		if (buildings[i][0] - buildings[i - 1][0] == midDiff + t) {
			result--;
		}
		if (buildings[i][0] - buildings[i - 1][0] < midDiff + t) {
			result -= 2;
		}
	}

	// 输出最终可以建旅馆的位置数
	cout << result << endl;

	return 0;
}
