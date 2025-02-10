#include <iostream>
#include <vector>

using namespace std;

int main() {
	ios::sync_with_stdio(false); // 关闭同步，加速I/O
	cin.tie(NULL); // 解绑cin和cout

	int test_cases;
	cin >> test_cases; // 输入测试用例数量

	while (test_cases--) {
		int num_students;
		cin >> num_students; // 输入学生数量

		// 使用向量存储每个学生的到达时间和离开时间
		vector<pair<int, int>> students(num_students);
		for (int i = 0; i < num_students; ++i) {
			cin >> students[i].first >> students[i].second; // 读取 li 和 ri
		}

		// 向量存储每个学生取水的时间，初始化为0
		vector<int> water_times(num_students, 0);

		if (num_students > 0) {
			// 初始化当前时间为第一个学生的到达时间
			int current_time = students[0].first;
			water_times[0] = current_time; // 第一个学生开始取水的时间

			// 依次处理剩余的学生
			for (int i = 1; i < num_students; ++i) {
				// 如果当前时间小于学生的离开时间，学生可以取水
				if (current_time < students[i].second) {
					current_time += 1; // 取水需要1秒
					water_times[i] = current_time; // 记录取水完成的时间
				} else {
					// 学生无法取水，保持0
					water_times[i] = 0;
				}
			}
		}

		// 输出每个学生的取水时间
		for (int i = 0; i < num_students; ++i) {
			cout << water_times[i] << ' ';
		}
		cout << '\n'; // 每个测试用例后换行
	}

	return 0;
}
