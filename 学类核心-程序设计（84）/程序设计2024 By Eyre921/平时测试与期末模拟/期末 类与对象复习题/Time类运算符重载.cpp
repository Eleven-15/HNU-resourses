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

// ǰ���������������
Time Time::operator++() {
	++sec; // ���1
	if (sec >= 60) {
		// ����������ڵ���60
		sec = 0;
		++minute; // ���Ӽ�1
		if (minute >= 60) {
			// ������Ӵ��ڵ���60
			minute = 0;
			++hour; // Сʱ��1
			if (hour >= 24) {
				// ���Сʱ���ڵ���24
				hour = 0; // ʱ�ӹ���
			}
		}
	}
	return *this; // ���ظ��º�Ķ���
}

// �����������������
Time Time::operator++(int) {
	Time temp = *this; // ���浱ǰ����ĸ���
	++(*this); // ����ǰ������
	return temp; // ���ظ���
}

ostream &operator<<(ostream &os, Time &t) {
	os << t.hour << ":" << t.minute << ":" << t.sec << endl; // ��ʽ�������û��ǰ����
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
5. Time�����������
������������

���Ķ����벢�������
��������ʽ��

һ�У������������������,b,c,��ֱ���0-23��0-59��0-59
�������ʽ��

4��
���������롿

1 2 3
�����������

1:2:3

1:2:4

1:2:4

1:2:5

������˵����
�����ֱ�׼��
 */
