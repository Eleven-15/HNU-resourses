//有理数类的定义与实现，运算符重载
#include <iostream>
using namespace std;

//类的定义
class Rational {
	private:
		int fz;
		int fm;

	public:
		~Rational(); //析构函数的原型声明
		Rational(); //无参构造函数声明
		Rational(int, int); //全参构造函数声明，形参列表和数据成员列表完全相同
		Rational(const Rational &); //复制构造函数声明，以该类型的常引用为形参
		// 重载输入运算符>>

		friend istream &operator>>(istream &is, Rational &r) {
			is >> r.fz >> r.fm;
			if (r.fm == 0) {
				// 如果分母为0，设置分母为1
				cout << "Denominator cannot be zero. Setting denominator to 1." << endl;
				r.fm = 1;
			}
			return is;
		}


		// 重载输出运算符<<

		friend ostream &operator<<(ostream &os, const Rational &r) {
			os << r.fz << "/" << r.fm;
			return os;
		}

		// 重载乘法运算符 *

		Rational operator*(const Rational &r) const {
			int newFz = fz * r.fz; // 乘法后的分子
			int newFm = fm * r.fm; // 乘法后的分母
			return Rational(newFz, newFm); // 返回新的有理数对象
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
	//功能：释放资源
	cout << "Destructor called. \n";
}

Rational::Rational() {
	//功能：初始化数据成员
	fz = 0;
	fm = 1;
}

Rational::Rational(int x, int y) {
	//功能：初始化数据成员
	fz = x;
	fm = y;
}

Rational::Rational(const Rational &r) {
	//功能：初始化数据成员
	fz = r.fz;
	fm = r.fm;
}

//创建对象，测试功能
int main() {
	Rational a; //调用无参构造函数
	cin >> a;
	cout << "类与对象 = " << a << endl;

	Rational b(3, 5); //调用全参构造函数
	cout << "b = " << b << endl;
	Rational c(a); //调用复制构造函数
	cout << "c = " << c << endl;


	c = a * b; //乘法运算
	cout << "c = 类与对象 * b = " << c << endl;

	return 0;
}

/*
3. 有理数类运算符重载
【问题描述】

请阅读代码，补充代码
【输入形式】

一行，两个整数
【输出形式】

8行
【样例输入】

3 4
【样例输出】

类与对象 = 3/4

b = 3/5

c = 3/4

Destructor called.

c = 类与对象 * b = 9/20

Destructor called.

Destructor called.

Destructor called.

【样例说明】
【评分标准】
 */
