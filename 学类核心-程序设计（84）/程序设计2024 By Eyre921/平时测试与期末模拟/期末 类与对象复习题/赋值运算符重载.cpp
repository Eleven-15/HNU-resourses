#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

// StringWrapper �ඨ��
class StringWrapper {
	private:
		char *str;

	public:
		// ���캯��
		StringWrapper(const char *s = "") {
			if (s) {
				str = new char[strlen(s) + 1];
				strcpy(str, s);
			} else {
				str = new char[1];
				*str = '\0';
			}
		}

		// �������캯��
		StringWrapper(const StringWrapper &other) {
			str = new char[strlen(other.str) + 1];
			strcpy(str, other.str);
		}

		// ��������
		~StringWrapper() {
			delete[] str;
			cout << "ok" << endl;
		}


		// ��ֵ���������
		StringWrapper& operator=(StringWrapper &other) {
			if (this != &other) {
				delete[] str;
				str = new char[strlen(other.str) + 1];
				strcpy(str, other.str);
			}
			return *this;
		}


		//*/
		// ��ȡ�ַ�������
		const char *getStr() const {
			return str;
		}
};

// ���Ժ���
void test() {
	StringWrapper sw1("Hello, World!");
	char str[81];
	cin.getline(str, 80);
	StringWrapper sw2(str);
	StringWrapper sw3 = sw1; // ʹ�ÿ������캯��
	cout << "sw1: " << sw1.getStr() << endl;
	cout << "sw2: " << sw2.getStr() << endl;
	cout << "sw3: " << sw3.getStr() << endl;
	sw3 = sw2;
	cout << "sw3 after assignment: " << sw3.getStr() << endl;
}

int main() {
	test();
	return 0;
}
/*
4. ��ֵ���������
������������

���Ķ����벢�������
��������ʽ��

һ�У�һ���ַ�(������80���ַ�)
�������ʽ��

7��
���������롿

������� b
�����������

sw1: Hello, World!

sw2: ������� b

sw3: Hello, World!

sw3 after assignment: ������� b

ok

ok

ok

������˵����
�����ֱ�׼��
 */
