#include <iostream>
using namespace std;

bool HaveSeven(int num) {
	while (num != 0) {
		if (num % 10 == 7)
			return true;
		num /= 10;
	}
	return false;
}

int main() {
	int limit;
	cin >> limit;

	for (int i = 1; i <= limit; i++) {
		if (i % 7 == 0 || HaveSeven(i)) {
			cout << i << endl;
		}
	}
}

/*
【问题描述】输出指定范围内包含7的数字和7的倍数
【输入形式】一个int型正整数
【输出形式】从1到该输入整数范围以内所有包含7的数字和7的倍数，每个输出以换行隔开
【样例输入】
20
【样例输出】
14
17
【样例说明】1到20以内包含7的数字和7的倍数有7、14、17
【评分标准】正确输出
 */