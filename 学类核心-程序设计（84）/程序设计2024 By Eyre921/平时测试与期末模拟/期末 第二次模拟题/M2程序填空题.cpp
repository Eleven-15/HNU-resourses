#include <iostream>
using namespace std;
template <typename T> //////模板机制
T fmax(T a, T b, T c) {
	T tmp = a;
	if (b > a) tmp = b;
	if (c > a) tmp = c;
	return tmp;
}
int main() {
	int i1, i2, i3, i;
	char c1, c2, c3, c;
	cin >> i1 >> i2 >> i3;
	cin >> c1 >> c2 >> c3;
	i = fmax(i1, i2, i3); //////模板函数实例化
	c = fmax(c1, c2, c3); ///////模板函数实例化
	cout << i << endl;
	cout << c << endl;
	return 0;
}
