#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

// StringWrapper 类定义
class StringWrapper {
	private:
		char *str;

	public:
		// 构造函数
		StringWrapper(const char *s = "") {
			if (s) {
				str = new char[strlen(s) + 1];
				strcpy(str, s);
			} else {
				str = new char[1];
				*str = '\0';
			}
		}

		// 拷贝构造函数
		StringWrapper(const StringWrapper &other) {
			str = new char[strlen(other.str) + 1];
			strcpy(str, other.str);
		}

		// 析构函数
		~StringWrapper() {
			delete[] str;
			cout << "ok" << endl;
		}


		// 赋值运算符重载
		StringWrapper& operator=(StringWrapper &other) {
			if (this != &other) {
				delete[] str;
				str = new char[strlen(other.str) + 1];
				strcpy(str, other.str);
			}
			return *this;
		}


		//*/
		// 获取字符串内容
		const char *getStr() const {
			return str;
		}
};

// 测试函数
void test() {
	StringWrapper sw1("Hello, World!");
	char str[81];
	cin.getline(str, 80);
	StringWrapper sw2(str);
	StringWrapper sw3 = sw1; // 使用拷贝构造函数
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
4. 赋值运算符重载
【问题描述】

请阅读代码并补充代码
【输入形式】

一行，一串字符(不超过80个字符)
【输出形式】

7行
【样例输入】

类与对象 b
【样例输出】

sw1: Hello, World!

sw2: 类与对象 b

sw3: Hello, World!

sw3 after assignment: 类与对象 b

ok

ok

ok

【样例说明】
【评分标准】
 */
