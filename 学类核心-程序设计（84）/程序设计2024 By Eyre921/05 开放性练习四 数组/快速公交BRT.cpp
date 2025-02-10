#include <iostream>
#include <vector>
using namespace std;

int main() {
	// 输入交通灯数量及红绿灯时间周期
	int numIntersections, greenTime, redTime;
	cin >> numIntersections >> greenTime >> redTime;

	// 输入路段时间
	vector<int> segmentTimes(numIntersections + 1);
	for (int i = 0; i <= numIntersections; i++) {
		cin >> segmentTimes[i];
	}

	// 输入公交车数量及其出发时间
	int numBuses;
	cin >> numBuses;
	vector<int> departureTimes(numBuses);
	for (int i = 0; i < numBuses; i++) {
		cin >> departureTimes[i];
	}

	// 计算每辆公交车到达终点的时间
	for (int i = 0; i < numBuses; i++) {
		int currentTime = departureTimes[i]; // 当前时间

		// 遍历每一段路段
		for (int j = 0; j <= numIntersections; j++) {
			currentTime += segmentTimes[j]; // 到达下一个路口的时间

			// 如果还有路口需要通过，检查是否需要等待红灯
			if (j < numIntersections) {
				int cyclePosition = currentTime % (greenTime + redTime); // 当前处于红绿灯周期中的时间
				if (cyclePosition >= greenTime) { // 如果是红灯，需要等待
					currentTime += (greenTime + redTime - cyclePosition);
				}
			}
		}

		// 输出公交车的到达时间
		cout << currentTime << " ";
	}

	return 0;
}
