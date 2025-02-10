#include <iostream>
#include <string>

using namespace std;
int reverse(int n);

int main() {
	int n;
	cin >> n;
	cout << reverse(n) << endl;
	return 0;
}

int reverse(int n) {
	string str = to_string(n);  // 整数转为字符串
	bool isNegative = false;

	// 检查负号
	if (str[0] == '-') {
		isNegative = true;
		str = str.substr(1);  // 去掉负号
	}

	// 反转字符串
	string reversedStr;
	for (int i = str.size() - 1; i >= 0; --i) {
		reversedStr += str[i];  // 从后向前拼接字符
	}

	long reversed = stol(reversedStr);

	// 根据符号调整结果
	if (isNegative) {
		reversed = -reversed;  // 如果是负数，加上负号
	}

	// 检查是否溢出32位整数范围
	if (reversed > 2147483647 || reversed < -2147483648) {
		return 0;  // 溢出返回 0
	}

	return reversed;  // 转换回 int 类型并返回
}