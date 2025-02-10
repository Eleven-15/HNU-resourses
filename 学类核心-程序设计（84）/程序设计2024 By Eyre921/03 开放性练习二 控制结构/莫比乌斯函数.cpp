#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 计算莫比乌斯函数
int mobius(int n) {
	if (n == 1)
		return 1; // 基本情况

	int primeCount = 0; // 质因子的数量
	bool hasSquareFactor = false; // 是否有平方因子

	// 检查从2到sqrt(n)的所有数
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) { // 如果i是n的因子
			primeCount++; // 找到一个质因子
			// 检查是否有平方因子
			if (n % (i * i) == 0) {
				hasSquareFactor = true; // 有平方因子
				break;
			}
			// 除去所有i的因子
			while (n % i == 0) {
				n /= i;
			}
		}
	}
	// 如果n大于1，说明n本身是一个质数
	if (n > 1) {
		primeCount++;
	}

	// 根据条件返回结果
	if (hasSquareFactor)
		return 0; // 有平方因子
	return (primeCount % 2 == 0) ? 1 : -1; // 偶数质因子返回1，奇数返回-1
}

int main() {
	int n;
	cin >> n;
	cout << mobius(n) << endl;
	return 0;
}



