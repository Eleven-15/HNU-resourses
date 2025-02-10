#include <iostream>
#include <vector>
using namespace std;

int main() {
	int numRoutes, friendPos; // numRoutes：公交车线路数，friendPos：朋友家位置
	cin >> numRoutes >> friendPos;

	// 读取每条公交车的运行区间 [start, end]
	vector<pair<int, int>> routes(numRoutes);
	for(int i = 0; i < numRoutes; i++) {
		cin >> routes[i].first >> routes[i].second; // first：起点, second：终点
	}

	int iterations = 0; // 记录循环次数，防止无限循环

	// 执行最多 numRoutes 次循环，尝试将 m 逐步回退到 0 或更小
	do {
		for(int i = 0; i < numRoutes; i++) {
			// 如果当前 m 被该公交线路覆盖
			if(routes[i].first <= friendPos && routes[i].second >= friendPos) {
				friendPos = routes[i].first; // 将 m 更新为该线路的起点
			}
		}
		iterations++;
	} while(iterations < numRoutes); // 限制循环次数为公交线路数

	// 判断最终位置是否到达或超过 0 点
	if(friendPos <= 0) {
		cout << "Yes";
	}
	else {
		cout << "No";
	}

	return 0;
}
