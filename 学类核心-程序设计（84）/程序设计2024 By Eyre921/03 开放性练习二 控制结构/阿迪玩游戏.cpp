#include <iostream>
using namespace std;

int main() {
	int N, M, pos = 1, fangxiang = 1, steps = 0;
	cin >> N >> M;
	int A[M];
	if (N == 1) {
		cout << "0";
		return 0;
	} else {
		for (int i = 0; i < M; i++) {
			cin >> A[i]; // 获取需要前进的步数
			steps += A[i];
		}
		for (int j = 0; j < steps; j++) { // 计算每一步
			pos += fangxiang;
			if (pos == N)
				fangxiang = -1;
			else if (pos == 1)
				fangxiang = 1;
		}
		cout << pos << endl;
	}
}


