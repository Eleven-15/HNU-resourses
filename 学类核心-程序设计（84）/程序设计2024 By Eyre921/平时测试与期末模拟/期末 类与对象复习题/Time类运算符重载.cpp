#include <iostream>
using namespace std;

class Time {
	public:
		Time() {
			hour = 0;
			minute = 0;
			sec = 0;
		}

		Time(int h, int m, int s): hour(h), minute(m), sec(s) {}

		Time operator++();

		Time operator++(int);

		friend ostream &operator <<(ostream &, Time &);

	private:
		int hour;
		int minute;
		int sec;
};

// 前置自增运算符定义
Time Time::operator++() {
	++sec; // 秒加1
	if (sec >= 60) {
		// 如果秒数大于等于60
		sec = 0;
		++minute; // 分钟加1
		if (minute >= 60) {
			// 如果分钟大于等于60
			minute = 0;
			++hour; // 小时加1
			if (hour >= 24) {
				// 如果小时大于等于24
				hour = 0; // 时钟归零
			}
		}
	}
	return *this; // 返回更新后的对象
}

// 后置自增运算符定义
Time Time::operator++(int) {
	Time temp = *this; // 保存当前对象的副本
	++(*this); // 调用前置自增
	return temp; // 返回副本
}

ostream &operator<<(ostream &os, Time &t) {
	os << t.hour << ":" << t.minute << ":" << t.sec << endl; // 格式化输出，没有前导零
	return os;
}


int main() {
	int a, b, c;
	cin >> a >> b >> c;
	Time time1(a, b, c), time2;
	cout << time1;
	time2 = ++time1;
	cout << time2;
	time2 = time1++;
	cout << time2;
	cout << time1;
	return 0;
}
/*
5. Time类运算符重载
【问题描述】

请阅读代码并补充代码
【输入形式】

一行，三个整数，类与对象,b,c,其分别是0-23，0-59，0-59
【输出形式】

4行
【样例输入】

1 2 3
【样例输出】

1:2:3

1:2:4

1:2:4

1:2:5

【样例说明】
【评分标准】
 */
