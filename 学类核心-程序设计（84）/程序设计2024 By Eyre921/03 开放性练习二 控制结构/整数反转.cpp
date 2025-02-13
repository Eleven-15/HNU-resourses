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
	string str = to_string(n);  // ����תΪ�ַ���
	bool isNegative = false;

	// ��鸺��
	if (str[0] == '-') {
		isNegative = true;
		str = str.substr(1);  // ȥ������
	}

	// ��ת�ַ���
	string reversedStr;
	for (int i = str.size() - 1; i >= 0; --i) {
		reversedStr += str[i];  // �Ӻ���ǰƴ���ַ�
	}

	long reversed = stol(reversedStr);

	// ���ݷ��ŵ������
	if (isNegative) {
		reversed = -reversed;  // ����Ǹ��������ϸ���
	}

	// ����Ƿ����32λ������Χ
	if (reversed > 2147483647 || reversed < -2147483648) {
		return 0;  // ������� 0
	}

	return reversed;  // ת���� int ���Ͳ�����
}