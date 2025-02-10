#include <iostream>
using namespace std;

class Date {
	public:
		Date() {
			year = 0;
			month = 0;
			day = 0;
		} //构造函数
		Date(int y, int m, int d): year(y), month(m), day(d) {}

		friend istream &operator >>(istream &input, Date &d); // 输入运算符重载
		friend ostream &operator <<(ostream &output, const Date &d); // 输出运算符重载
		friend bool operator ==(const Date &d1, const Date &d2); // 等于运算符重载

	private:
		int year;
		int month;
		int day;
};

istream &operator >>(istream &input, Date &d) { //输入运算符重载
	input >> d.year >> d.month >> d.day;
	return input;
}

ostream &operator <<(ostream &output, const Date &d) {
	// 使用 '/' 作为分隔符，并确保月份和日期以两位数显示
	output << d.year << '/'
	       << d.month << '/'
	       << d.day;
	return output;
}

bool operator ==(const Date &d1, const Date &d2) {
	return (d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day);
}



int main() {
	Date date1, date2;
	cin >> date1;
	cin >> date2;
	if (date1 == date2)
		cout << date1;
	else cout << "NotEqual";
	return 0;
}

/*
Date类运算符重载
【问题描述】请仔细阅读下面关于Date类的代码，完成片段编程。
【输入形式】输入2行，每行保证3个有效整数，保证合法的日期的年月日的取值
【输出形式】如果输入的两个日期相等则时间格式输出年月日，中间用/分隔；如果两个日期不相等则输出NotEqual
【样例输入1】

  1982 10 07

  1972 10 07

【样例输出2】

  NotEqual

【样例输入1】

  1982 10 07

  1982 10 07

【样例输出1】

  1982/10/07

【样例说明】

日期对象包含年月日三个数据成员

【评分标准】
 */
