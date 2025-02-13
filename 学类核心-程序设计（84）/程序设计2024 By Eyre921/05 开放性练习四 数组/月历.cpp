#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

// 计算指定年份和月份的第一天是星期几
int getFirstDay(int year, int month) {
    struct tm time_in = {0};
    time_in.tm_year = year - 1900; // 年份从 1900 年开始
    time_in.tm_mon = month - 1;    // 月份从 0 开始
    time_in.tm_mday = 1;           // 设置为该月的第一天

    mktime(&time_in);              // 通过 mktime 函数来计算 tm_wday
    return time_in.tm_wday;        // 返回星期几（0 是星期日，1 是星期一，依此类推）
}

// 计算指定年份和月份有多少天
int getDaysInMonth(int year, int month) {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else {
        // 判断二月是否为闰月
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            return 29;
        else
            return 28;
    }
}

// 打印指定月份的日历
void printCalendar(int year, int month, int firstDay, int days) {
    // 打印星期标题
    cout << setw(4) << "Sun" << setw(4) << "Mon" << setw(4) << "Tue"
         << setw(4) << "Wed" << setw(4) << "Thu" << setw(4) << "Fri"
         << setw(4) << "Sat" << endl;

    // 输出空格，直到该月的第一天
    for (int i = 0; i < firstDay; i++) {
        cout << setw(4) << " ";
    }

    // 输出该月的日期
    for (int day = 1; day <= days; day++) {
        cout << setw(4) << day;
        if ((day + firstDay) % 7 == 0) {
            cout << endl;
        }
    }
    cout << endl;  // 最后一行换行
}

int main() {
    int year, month;
    cin >> year >> month;

    // 获取该月的第一天是星期几
    int firstDay = getFirstDay(year, month);

    // 获取该月有多少天
    int days = getDaysInMonth(year, month);

    // 打印日历
    printCalendar(year, month, firstDay, days);

    return 0;
}
