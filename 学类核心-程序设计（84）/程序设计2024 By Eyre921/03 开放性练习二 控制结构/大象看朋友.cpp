#include <iostream>
#include <vector>
using namespace std;

int min_steps(int x, int m) {
	int target = abs(x);  // Ŀ��λ�õľ���ֵ
	vector<int> steps;    // ���õ���������
	for (int i = 1; i <= 2 * m - 1; i += 2) {
		steps.push_back(i);  // �������в���
	}

	int step_count = 0;  // ��¼����
	int current_pos = 0; // ��ǰ����λ��

	// ����󲽳���ʼ��ʹ��̰�Ĳ��Խӽ�Ŀ��
	while (current_pos < target) {
		for (int i = steps.size() - 1; i >= 0; --i) {
			if (current_pos + steps[i] <= target) {
				current_pos += steps[i];  // ����ʹ�����Ĳ���
				step_count++;
				break;
			}
		}
	}

	return step_count;
}

int main() {
	int x, m;
	// ��ȡ����
	cin >> x >> m;
	// �����С����
	cout << min_steps(x, m) << endl;
	return 0;
}

