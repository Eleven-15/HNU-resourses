#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
	int A, B, N;
	cin >> A >> B >> N;

	// 计算整数部分
	long long integerPart = A / B;

	// 计算小数部分
	long long remainder = A % B;
	string decimalPart;

	for (int i = 0; i < N; ++i) {
		remainder *= 10;
		decimalPart += (remainder / B) + '0'; // 获取当前小数位并转为字符
		remainder %= B; // 更新余数
	}

	// 输出结果
	cout << integerPart << "." << decimalPart << endl;

	return 0;
}

