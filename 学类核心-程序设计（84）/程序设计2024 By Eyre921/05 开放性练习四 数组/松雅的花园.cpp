#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T; // 测试用例数量
	cin >> T;

	while(T--){
		int n, k; // n: 苗圃数量, k: 水龙头数量
		cin >> n >> k;

		vector<int> taps(k); // 存储水龙头的位置
		for(int i = 0; i < k; i++) {
			cin >> taps[i];
		}

		vector<int> intervals(k + 1, 0); // 存储各个区间所需的时间

		// 第一个区间：起点到第一个水龙头的距离
		intervals[0] = taps[0];

		// 中间区间：相邻水龙头之间的距离
		for(int i = 1; i < k; i++){
			int distance = taps[i] - taps[i-1];
			if(distance == 1){
				intervals[i] = 1;
			}
			else if((distance - 1) % 2 == 0){
				intervals[i] = 1 + (distance - 1) / 2;
			}
			else{
				intervals[i] = 1 + distance / 2;
			}
		}

		// 最后一个区间：最后一个水龙头到终点的距离
		intervals[k] = n - taps[k-1] + 1;

		// 找到所有区间中的最大时间
		int maxTime = 0;
		for(auto time : intervals){
			if(time > maxTime){
				maxTime = time;
			}
		}

		cout << maxTime << "\n";
	}

	return 0;
}
