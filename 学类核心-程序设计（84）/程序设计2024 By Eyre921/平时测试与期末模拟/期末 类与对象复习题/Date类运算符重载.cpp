#include <iostream>
using namespace std;

class Date {
	public:
		Date() {
			year = 0;
			month = 0;
			day = 0;
		} //���캯��
		Date(int y, int m, int d): year(y), month(m), day(d) {}

		friend istream &operator >>(istream &input, Date &d); // �������������
		friend ostream &operator <<(ostream &output, const Date &d); // ������������
		friend bool operator ==(const Date &d1, const Date &d2); // �������������

	private:
		int year;
		int month;
		int day;
};

istream &operator >>(istream &input, Date &d) { //�������������
	input >> d.year >> d.month >> d.day;
	return input;
}

ostream &operator <<(ostream &output, const Date &d) {
	// ʹ�� '/' ��Ϊ�ָ�������ȷ���·ݺ���������λ����ʾ
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
Date�����������
����������������ϸ�Ķ��������Date��Ĵ��룬���Ƭ�α�̡�
��������ʽ������2�У�ÿ�б�֤3����Ч��������֤�Ϸ������ڵ������յ�ȡֵ
�������ʽ�����������������������ʱ���ʽ��������գ��м���/�ָ�������������ڲ���������NotEqual
����������1��

  1982 10 07

  1972 10 07

���������2��

  NotEqual

����������1��

  1982 10 07

  1982 10 07

���������1��

  1982/10/07

������˵����

���ڶ�������������������ݳ�Ա

�����ֱ�׼��
 */
