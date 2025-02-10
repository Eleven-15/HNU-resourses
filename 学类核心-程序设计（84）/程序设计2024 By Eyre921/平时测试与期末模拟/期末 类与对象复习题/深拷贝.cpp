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

		StringWrapper(const StringWrapper &other) {
			// �������ڴ沢��������������ַ���
			str = new char[strlen(other.str) + 1];
			strcpy(str, other.str);
		}

		// ������ֵ�����
		StringWrapper &operator=(const StringWrapper &other) {
			if (this != &other) {
				// ��ֹ�Ը�ֵ
				// �ͷŵ�ǰ�ڴ�
				delete[] str;
				// �������ڴ沢�����ַ���
				str = new char[strlen(other.str) + 1];
				strcpy(str, other.str);
			}
			return *this;
		}


		// ��������
		~StringWrapper() {
			delete[] str;
		}


		// ��ȡ�ַ�������
		const char *getStr() const {
			return str;
		}
};

// ���Ժ���
void testDeepCopy() {
	StringWrapper sw1("Hello, World!");
	StringWrapper sw2 = sw1; // ʹ�ÿ������캯��

	char ch;
	cin >> ch;
	const char *temp = sw1.getStr();
	const_cast<char *>(temp)[7] = ch; // �޸� sw1 ���ַ������ݣ����Ƽ���������

	// ��ӡ���� StringWrapper ����������֤���
	cout << "sw1: " << sw1.getStr() << endl;
	cout << "sw2: " << sw2.getStr() << endl;

	// ��֤���� StringWrapper �Ƿ������Ӧ����� false����Ϊԭʼ�ַ������޸��ˣ�
	// ���������ǽ�������������� sw2 ������Ӧ�ñ��ֲ��䣩
}

int main() {
	testDeepCopy();
	return 0;
}


/*
*������������

���Ķ����룬�������
��������ʽ��

һ�У������ַ�
�������ʽ��

�����ַ���
���������롿

�������
�����������

sw1: Hello, aorld!

sw2: Hello, World!

������˵����
�����ֱ�׼��
 */
