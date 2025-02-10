#include <bits/stdc++.h>
using namespace std;

// 判断是否是闰年
bool isLeapYear(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int main() {
	int n, year, month, day;
	char separator;

	cin >> n;

	// 处理每个测试用例
	for (int i = 0; i < n; i++) {
		cin >> year >> separator >> month >> separator >> day;
		int daysCount = 0;  // 用于累计天数
		int nextYear = year;

		// 如果是2月29日
		if (month == 2 && day == 29) {
			do {
				nextYear += 1;
				// 判断是否是闰年，计算每年的天数
				if (isLeapYear(nextYear)) {
					daysCount += 366;
				} else {
					daysCount += 365;
				}
			}
			// 找到下一个闰年且总天数能被7整除
			while (!((daysCount % 7 == 0) && isLeapYear(nextYear)));
		}
		// 如果不是2月29日
		else {
			// 若当前月份在2月或之前
			if (month <= 2) {
				do {
					if (isLeapYear(nextYear)) {
						daysCount += 366;
					} else {
						daysCount += 365;
					}
					nextYear += 1;
				}
				// 找到总天数能被7整除的年份
				while (!(daysCount % 7 == 0));
			}
			// 若当前月份是3月或之后
			else {
				do {
					nextYear += 1;
					if (isLeapYear(nextYear)) {
						daysCount += 366;
					} else {
						daysCount += 365;
					}
				}
				// 找到总天数能被7整除的年份
				while (!(daysCount % 7 == 0));
			}
		}
		// 输出找到的年份
		cout << nextYear << endl;
	}

	return 0;
}
