#include <iostream>
#include <string>
using namespace std;

int main() {
	int number;
	cin >> number;
	cout << to_string(number).length() << endl;
	return 0;
}

/*
【问题描述】求一个数的位数
【输入形式】一个int型的正整数
【输出形式】该输入正整数的位数或长度
【样例输入】
100
【样例输出】
3
【样例说明】100的位数是3
【评分标准】正确输出
 */