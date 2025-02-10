#include <bits/stdc++.h>
using namespace std;

// �ж��Ƿ�������
bool isLeapYear(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int main() {
	int n, year, month, day;
	char separator;

	cin >> n;

	// ����ÿ����������
	for (int i = 0; i < n; i++) {
		cin >> year >> separator >> month >> separator >> day;
		int daysCount = 0;  // �����ۼ�����
		int nextYear = year;

		// �����2��29��
		if (month == 2 && day == 29) {
			do {
				nextYear += 1;
				// �ж��Ƿ������꣬����ÿ�������
				if (isLeapYear(nextYear)) {
					daysCount += 366;
				} else {
					daysCount += 365;
				}
			}
			// �ҵ���һ���������������ܱ�7����
			while (!((daysCount % 7 == 0) && isLeapYear(nextYear)));
		}
		// �������2��29��
		else {
			// ����ǰ�·���2�»�֮ǰ
			if (month <= 2) {
				do {
					if (isLeapYear(nextYear)) {
						daysCount += 366;
					} else {
						daysCount += 365;
					}
					nextYear += 1;
				}
				// �ҵ��������ܱ�7���������
				while (!(daysCount % 7 == 0));
			}
			// ����ǰ�·���3�»�֮��
			else {
				do {
					nextYear += 1;
					if (isLeapYear(nextYear)) {
						daysCount += 366;
					} else {
						daysCount += 365;
					}
				}
				// �ҵ��������ܱ�7���������
				while (!(daysCount % 7 == 0));
			}
		}
		// ����ҵ������
		cout << nextYear << endl;
	}

	return 0;
}
