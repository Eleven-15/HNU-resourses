//��������Ķ�����ʵ�֣����������
#include <iostream>
using namespace std;

//��Ķ���
class Rational {
	private:
		int fz;
		int fm;

	public:
		~Rational(); //����������ԭ������
		Rational(); //�޲ι��캯������
		Rational(int, int); //ȫ�ι��캯���������β��б�����ݳ�Ա�б���ȫ��ͬ
		Rational(const Rational &); //���ƹ��캯���������Ը����͵ĳ�����Ϊ�β�
		// �������������>>

		friend istream &operator>>(istream &is, Rational &r) {
			is >> r.fz >> r.fm;
			if (r.fm == 0) {
				// �����ĸΪ0�����÷�ĸΪ1
				cout << "Denominator cannot be zero. Setting denominator to 1." << endl;
				r.fm = 1;
			}
			return is;
		}


		// ������������<<

		friend ostream &operator<<(ostream &os, const Rational &r) {
			os << r.fz << "/" << r.fm;
			return os;
		}

		// ���س˷������ *

		Rational operator*(const Rational &r) const {
			int newFz = fz * r.fz; // �˷���ķ���
			int newFm = fm * r.fm; // �˷���ķ�ĸ
			return Rational(newFz, newFm); // �����µ�����������
		}
		Rational operator+(const Rational &r) {
			int newFz = fz * r.fm + fm * r.fz;
			int newFm = fm * r.fm;
			return Rational(newFz, newFm);
		}
		Rational operator-(const Rational &r) {
			int newFz = fm * r.fz - fz * r.fm ;
			int newFm = fm * r.fm;
			return Rational(newFz, newFm);
		}

};


Rational::~Rational() {
	//���ܣ��ͷ���Դ
	cout << "Destructor called. \n";
}

Rational::Rational() {
	//���ܣ���ʼ�����ݳ�Ա
	fz = 0;
	fm = 1;
}

Rational::Rational(int x, int y) {
	//���ܣ���ʼ�����ݳ�Ա
	fz = x;
	fm = y;
}

Rational::Rational(const Rational &r) {
	//���ܣ���ʼ�����ݳ�Ա
	fz = r.fz;
	fm = r.fm;
}

//�������󣬲��Թ���
int main() {
	Rational a; //�����޲ι��캯��
	cin >> a;
	cout << "������� = " << a << endl;

	Rational b(3, 5); //����ȫ�ι��캯��
	cout << "b = " << b << endl;
	Rational c(a); //���ø��ƹ��캯��
	cout << "c = " << c << endl;


	c = a * b; //�˷�����
	cout << "c = ������� * b = " << c << endl;

	return 0;
}

/*
3. �����������������
������������

���Ķ����룬�������
��������ʽ��

һ�У���������
�������ʽ��

8��
���������롿

3 4
�����������

������� = 3/4

b = 3/5

c = 3/4

Destructor called.

c = ������� * b = 9/20

Destructor called.

Destructor called.

Destructor called.

������˵����
�����ֱ�׼��
 */
